#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>

/*
 * 1. how about bugs or problems with this routines and fix them
 * 2. replace send/recv with sendmsg/recvmsg
 * 3. replace block with non-block
 * 4. udp insteads of tcp
 * 5. can send/recv be replaced by sendto/recvfrom
 */


/* arguments : local_ip local_port*/
int main(int argc, char *argv[])
{
    /* demo with tcpv4, don't check the arguments :-) */
    char *ip = argv[1];       /* local ip addr */
    char *port = argv[2];     /* local port */

    int fd_lst, fd_apt = -1;  /* listen fd and accept fd */
    struct sockaddr_in laddr, raddr;
    socklen_t rlen = sizeof(struct sockaddr);

    fd_set rfds;
    struct timeval tv;

    int max_fd = -1;
    
    laddr.sin_family = AF_INET;
    laddr.sin_addr.s_addr = inet_addr(ip);
    laddr.sin_port = htons(atoi(port));

    /* create listen socket, syscall(net/socket.c) : sock_create */
    if (-1 == (fd_lst = socket(AF_INET, SOCK_STREAM, 0))) /* /etc/protocols lists "protocol <-> number" */
        goto error;

    /* bind, syscall : bind */
    if (-1 == bind(fd_lst, (struct sockaddr *)&laddr, sizeof(struct sockaddr))) 
        goto error;

    /* listen as server, syscall : listen */
    if (-1 == listen(fd_lst, 5)) /* "man 2 listen" for detail information about argument 2 (backlog). in linux kernel 3.x, it doesn't care the backlog */
        goto error;
//while(1);
    while (1) {
        tv.tv_sec  = 5;
        tv.tv_usec = 0;

        FD_ZERO(&rfds);
        FD_SET(fd_lst, &rfds);
        (-1 != fd_apt) ? FD_SET(fd_apt, &rfds) : 0;
        max_fd = fd_apt > fd_lst ? fd_apt : fd_lst;

        /* syscall : select */
        switch (select(max_fd+1, &rfds, NULL, NULL, &tv)) { /* exceptfds, monitors abnormal file handles */
            case 0: /* timeout */
                printf("no data within 5 seconds\n");
                break;

            case -1: /* error */
                goto error;

            default: 
                if (FD_ISSET(fd_lst, &rfds)) { /* here comes a connection */
                    printf("client connect\n");
                    memset(&raddr, 0, sizeof(raddr));
                    
                    /* finish 3-hand-shake, syscall : accept */
                    if (-1 == (fd_apt = accept(fd_lst, (struct sockaddr *)&raddr, &rlen)))
                        goto error;
                }

                if (FD_ISSET(fd_apt, &rfds)) { /* data comes from client */
                    char buffer[4096] = {0};
                    /* recieve data, syscall : recv */
                    switch (recv(fd_apt, buffer, sizeof(buffer), 0)) {
                        case 0: /* peer shutdown */
                            printf("peer shutdown\n");
                            close(fd_apt);
                            fd_apt = -1;
                            break;

                        case -1: /* error */
                            goto error;

                        default:
                            printf("recieve data from client : %s\n", buffer);
                            break;
                    }
                }

                break;
        }
    }
    
    return 0;
    
  error:
    printf("%s\n", strerror(errno));

    fd_lst ? close(fd_lst) : 0;
    fd_apt ? close(fd_apt) : 0;
    
    return -1;
}

