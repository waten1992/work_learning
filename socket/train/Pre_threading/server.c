#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<semaphore.h>
#include<malloc.h>
#include<syslog.h>
#include<unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 
#define  Num_Thread  2 
#define  Num_slots 40
void p(sem_t *s);
void v(sem_t *s);
typedef struct 
{
    int  *buf ;
    size_t  num ;
    size_t  front ;
    size_t  rear ;
    sem_t   slots;
    sem_t  items ;
    sem_t  mutex ;
}pool ;

  void p(sem_t *s )
  {   
      if(sem_wait(s)  == -1 )
          fprintf(stderr,"sem_wait error \n");
  }
  
  void v(sem_t *s )
  {   
      if(sem_post(s) == -1  )
          fprintf(stderr,"sem_post error \n");
  }
  
pool sp ;
void *my_thread(void *message);
  void init_pool( pool *sp ,size_t N)
  {
      int ret ; 
      sp->buf = (int *)calloc(N,sizeof(int));
      sp->num  = N ; 
      sp->rear = sp->front    = 0 ; 
      ret =   sem_init(&sp->slots,0,N);
      ret = sem_init(&sp->items,0,0);
      sem_init(&sp->mutex,0,1);
  }
  void pool_insert(size_t  element , pool *sp )
  {
      p(&sp->slots);
      p(&sp->mutex);
      sp->front++;
      sp->buf[(sp->front)%(sp->num)] =element ;
      printf("insert :  %d \n",element);
	  v(&sp->mutex);
      v(&sp->items);
  }
  size_t pool_remove (pool *sp )
  {
      size_t tmp_item ;
      p(&sp->items);
      p(&sp->mutex);
      sp->rear++ ;
      tmp_item = sp->buf[(sp->rear)%(sp->num)];
   	  printf("remove tmp_item :%d\n",tmp_item);
	  v(&sp->mutex);
      v(&sp->slots);
  return tmp_item ;
  };
  
  void pool_release(pool *sp)
  {
      free(sp->buf);
  }



void *my_thread(void *message)
{
	printf("tid : %u \n",pthread_self());
	pthread_detach(pthread_self());
	while(1)
	{
		size_t fd = pool_remove(&sp);
		int recv_len = 0;	
		char buff[4096] ;
        memset(buff,0,4096);
    while(1)
	  {
		  if((recv_len = recv(fd, buff, sizeof(buff), 0)) > 0) {
		    printf("recieve data from client : %s\n", buff);
		  }
      else if(recv_len == -1) {
            if (errno == EWOULDBLOCK || errno == EAGAIN)
            	printf("under O_NONBLOCK mode data didn't prepare \n");
      }
      else {
        printf("googbye client ~~~ \n");
				close(fd);
				break;
      }
	 }

	}	
}

int main(int argc , char *argv[])
{
	char *ip = argv[1];       /* local ip addr */
    char *port = argv[2];     /* local port */

	int sockfd , listenfd , accepfd , optval=1 ;
	struct sockaddr_in laddr, raddr;
    socklen_t rlen = sizeof(struct sockaddr);
	
	laddr.sin_family = AF_INET;
    laddr.sin_addr.s_addr = inet_addr(ip);
    laddr.sin_port = htons(atoi(port));

	pthread_t tid ;
	if(argc < 2)
	{
		printf("argc < 2 \n");
		return -1 ;
	}
	if (-1 == (listenfd = socket(AF_INET, SOCK_STREAM, 0))) /* /etc/protocol  s lists "protocol <-> number" */
    {
        printf("sockfd function is failed ,errno is :%s",strerror(errno));  
		return -1 ;
    }
  #if 1    
      /*eliminates "address already in use " error form bind */
    if(-1==setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,(const void *)&optval   ,sizeof(int)))
    {
          printf("setsockopt function is error , errno is : %s \n",strerror(errno));
          return -1 ;
    }
  #endif  
  
      /* bind, syscall : bind */
    if (-1 == bind(listenfd, (struct sockaddr *)&laddr, sizeof(struct sockaddr)))   
    {
          printf("bind function is error , errno is : %s \n",strerror(errno));
          return -1 ;
    }
	if (-1  ==  listen(listenfd, 5)) /* "man 2 listen" for detail information   about argument 2 (backlog). in linux kernel 3.x, it doesn't care the backlog   */
    {
          printf("listen function is error , errno is : %d \n",errno);
          return -1 ;
    }
#if 1
	int val ;
    if ((val = fcntl(listenfd , F_GETFL , 0)) == -1 )
    {
          printf("fcntl is failed ,errno %d\n",errno);
          return -1;
    }
 
    if (fcntl(listenfd , F_SETFL , val|O_NONBLOCK) == -1 )
    {
           printf("fcntl1 is failed \n");
           return -1;
    }
#endif 

	init_pool(&sp,Num_slots);
    for(int i = 0 ;i < Num_Thread  ; i++)	
		pthread_create(&tid,NULL,my_thread,NULL);
	while(1)
	{
		if(-1  == (accepfd = accept(listenfd,(struct sockaddr *)&raddr,&rlen)) )
		{
			if(errno != EWOULDBLOCK ||  errno != EAGAIN)
    	    {
        		printf("accept function is error , errno is : %d \n",errno);
           		 return -1 ;
       		 }
		}
		else
		{
			printf("arrive \n");
			pool_insert(accepfd , &sp);
		}
	}
	
return 0 ;
}

