#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

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

    int fd , optval = 1 ;
    fd_set r_set , w_set ;
    struct timeval t_val ;
    struct sockaddr_in laddr, raddr;

    char buffer[2048] = "mycapital.socket.demo";

    if (-1 == (fd = socket(AF_INET, SOCK_STREAM, 0)))
    {
		printf("socket is error  \n");
	}

    laddr.sin_family = AF_INET;
    laddr.sin_addr.s_addr = inet_addr(ip_l);
    laddr.sin_port = htons(atoi(port_l)); /* byte order */

    raddr.sin_family = AF_INET;
    raddr.sin_addr.s_addr = inet_addr(ip_r);
    raddr.sin_port = htons(atoi(port_r));
#if 0    
    /*eliminates "address already in use " error form bind */
    if(-1==setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,(const void *)&optval ,sizeof(int)))
        {
                printf("setsockopt function is error , errno is : %d \n",errno);
                return -1 ;
        }

    if (-1 == bind(fd, (struct sockaddr *)&laddr, sizeof(struct sockaddr)))
   	{
		printf("bind is  error, errno is %d  \n",errno);
		return -1 ;
	}
#endif 
    FD_ZERO(&r_set);
    FD_ZERO(&w_set);

    int val ,con_result,send_re_len ;
    if ((val = fcntl(fd , F_GETFL , 0)) == -1 )
    {
        printf("fcntl is failed \n");
        return -1;
    }
    if (fcntl(fd , F_SETFL , val|O_NONBLOCK) == -1 )
    {
         printf("fcntl is failed \n");
         return -1;
    }

    /* how to use connect with non-block mode */
    if ((con_result = connect(fd, (struct sockaddr *)&raddr, sizeof(struct sockaddr))) < 0 )
    {
        if(errno != EINPROGRESS)
        {
            printf("non-block connect is error \n");
            return -1 ;
        } 
#ifdef DEBUG // for debug
		else
		{
			printf("connect return is %d , errno is %d \n",con_result , errno);
		}            
#endif  
    
	}
	else 
    	goto connect_success ;
 
    FD_SET(fd, &r_set); /* select for reading and writing */
    FD_SET(fd, &w_set);
    t_val.tv_sec = 1 ;
    t_val.tv_usec = 0 ;
    if ( 0 == select(fd+1, &r_set ,&w_set,NULL,&t_val))
    {
        close(fd);
        errno = ETIMEDOUT ;
		printf("can't not find readfd \n");
        return -1 ;
    }
#ifdef   DEBUG
	else
            printf("select is happend , error is : %d \n", errno);
	
#endif 
    
	if(FD_ISSET(fd,&r_set) || FD_ISSET(fd,&w_set))
    {
        int len = sizeof(int) ;
        if (getsockopt(fd,SOL_SOCKET ,SO_ERROR,&optval,&len) == -1 )
        {
            printf("getsockopt error , error is : %d \n", errno);
            return -1 ;
        }
		else
		{
		//	printf("getsockopt return val : %d \n",optval);
			goto connect_success;
		}
    
    }
    else
        printf("can't find data from select \n");  

printf("something is error \n");    
close(fd);
return -1 ;

connect_success:
	
        printf("connect is success \n");
		if (( send_re_len = send(fd, buffer, sizeof(buffer), MSG_DONTWAIT)) < 0)
      	{
			printf("SEND O_NONBLOCK mode IS ERROR, errno number: %d\n",errno);
			if (errno == EWOULDBLOCK)
				goto connect_success;
		}
        printf( "press any key to exit \n");
        getchar();
        close(fd);
        return 0;
}

