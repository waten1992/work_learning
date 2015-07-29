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

typedef struct 
{
    int max_fd ; //max of in read_set 
    fd_set read_set ; // all of ative fd 
    fd_set tmp_read_set ; //every reading  fd 
    int nready ; //number of ready fd form select 
    int max_index ; // max index of read fd array
    int client_fd[FD_SETSIZE] ;//Set of active fd 
}pool;

void init(int listenfd , pool *p)
{
   
    p->max_index =  -1 ;
    for (int i = 0 ; i < FD_SETSIZE; i++)
        p->client_fd[i] = -1 ;
    
    p->max_fd = listenfd ;

    FD_ZERO(&p->read_set);
    FD_SET(listenfd, &p->read_set);
}

void handle_request(int acceptfd , pool *p)
{
    int i  ;
    p->nready--;
    for( i = 0 ; i < FD_SETSIZE ; i++)
    {
        if (p->client_fd[i] < 0)
        {
            p->client_fd[i] = acceptfd ;
            FD_SET(acceptfd , &p->read_set);

            if(acceptfd > p->max_fd)
                p->max_fd = acceptfd ;
            if(i > p->max_index)
                p->max_index = i ;
            break ;
        }
    }
    if ( i == FD_SETSIZE)
        printf("Too many clients \n");
}

void check_clients(pool *p)
{
    for(int i = 0 ; (i <= p->max_index) && (p->nready > 0) ; i++)
    {
        int tmp_fd  =  p->client_fd[i];

        if ((tmp_fd > 0) && (FD_ISSET(tmp_fd,&p->tmp_read_set)))
        {
            p->nready--;
    	    char buff[4096] ;
            memset(buff,0,4096);
            if(recv(tmp_fd, buff, sizeof(buff), 0))
            	printf("recieve data from client : %s\n", buff);
            else
            {
            	 close(tmp_fd);
            	 FD_CLR(tmp_fd , &p->read_set);
           	 p->client_fd[i]  = -1 ;
		 printf("googbye client ~~~ \n");
       	    }
        }
    }
}

int main(int argc, char *argv[])
{
    /* demo with tcpv4, don't check the arguments :-) */
    char *ip = argv[1];       /* local ip addr */
    char *port = argv[2];     /* local port */

    static pool  pool ;
    int listenfd, acceptfd ,fd , optval = 1;  /* listen fd and accept fd */
    struct sockaddr_in laddr, raddr;
    socklen_t rlen = sizeof(struct sockaddr);

    
    laddr.sin_family = AF_INET;
    laddr.sin_addr.s_addr = inet_addr(ip);
    laddr.sin_port = htons(atoi(port));

    /* create listen socket, syscall(net/socket.c) : sock_create */
    if (-1 == (listenfd = socket(AF_INET, SOCK_STREAM, 0))) /* /etc/protocols lists "protocol <-> number" */
        {
		printf("socket function is error , errno is : %d \n",errno);
		return -1 ;
	}
#if 1    
    /*eliminates "address already in use " error form bind */
    if(-1==setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,(const void *)&optval ,sizeof(int)))
        {
		printf("setsockopt function is error , errno is : %d \n",errno);
		return -1 ;
	}
#endif 
    /* bind, syscall : bind */
    if (-1 == bind(listenfd, (struct sockaddr *)&laddr, sizeof(struct sockaddr))) 
        {
		printf("bind function is error , errno is : %d \n",errno);
		return -1 ;
	}
    /* listen as server, syscall : listen */
    if (-1 == listen(listenfd, 5)) /* "man 2 listen" for detail information about argument 2 (backlog). in linux kernel 3.x, it doesn't care the backlog */
        {
		printf("listen function is error , errno is : %d \n",errno);
		return -1 ;
	}

    init(listenfd,&pool);
    
    while (1) 
    {
        pool.tmp_read_set = pool.read_set ;
        pool.nready = select(pool.max_fd+1, &pool.tmp_read_set, NULL, NULL, NULL);
        
        if (FD_ISSET(listenfd, &pool.tmp_read_set)) 
        { /* here comes a connection */
            printf("client connect\n");
                    /* finish 3-hand-shake, syscall : accept */
            if (-1 == (acceptfd = accept(listenfd, (struct sockaddr *)&raddr, &rlen)))
            {
		printf("accept function is error , errno is : %d \n",errno);
		return -1 ;
	    }
            handle_request(acceptfd,&pool);
        }
        check_clients(&pool);

    }

    return 0;
}

