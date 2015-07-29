#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
 *  * 1. how about the problem(s) with this routines and fix it(them) 
 *   * 2. replace block with non-block
 *    */


/* arguments : local_ip local_port remote_ip remote_port */
int main(int argc, char *argv[])
{
    /* demo with tcpv4, don't check the arguments */
    char *ip_l = argv[1];      /* local ip */
    char *port_l = argv[2];    /* local port */
    char *ip_r = argv[3];      /* server ip */
    char *port_r = argv[4];    /* server port */

    int fd;
    struct sockaddr_in laddr, raddr;

    char buffer[128] = "mycapital.socket.demo";

    if (-1 == (fd = socket(AF_INET, SOCK_STREAM, 0)))
        goto error;

    laddr.sin_family = AF_INET;
    laddr.sin_addr.s_addr = inet_addr(ip_l);
    laddr.sin_port = htons(atoi(port_l)); /* byte order */

    raddr.sin_family = AF_INET;
    raddr.sin_addr.s_addr = inet_addr(ip_r);
    raddr.sin_port = htons(atoi(port_r));

    if (-1 == bind(fd, (struct sockaddr *)&laddr, sizeof(struct sockaddr)))
        goto error;

    /* how to use connect with non-block mode */
    if (-1 == connect(fd, (struct sockaddr *)&raddr, sizeof(struct sockaddr)))
        goto error;

    if (-1 == send(fd, buffer, sizeof(buffer), 0))
        goto error;

    printf("%s\n", "press any key to exit");
    getchar();
    close(fd);
    return 0;
    
  error:
    
    printf("%s\n", strerror(errno));
    if (fd >= 0)        /* fork a new progress after close(0,1,2) */
		close(fd);
    
    /* just for show coredump */
    *(int *)0 = 0xdeaddead;

    return -1;
}

