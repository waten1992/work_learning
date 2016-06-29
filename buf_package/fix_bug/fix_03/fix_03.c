/*************************************************************************
	> File Name: buf_package.c
	> Author:waten 
	> Mail: waten1992@gmail.com
	> Created Time: Tuesday, June 23, 2015 PM07:34:35 HKT
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<semaphore.h>
#include<malloc.h>
#include<unistd.h>
#include<pthread.h>

#define  THREAD_NUM 2
#define PROD_NUM 26

typedef struct buf_pool
{
    void *  	buf ;
    size_t    	n;
    size_t 		front;
    size_t		rear;
	size_t		size; //the  struct of slots size  
    sem_t   mutex;  // 
    sem_t   slots; //available slots for producter
    sem_t   items; //available items for customer
}buf_pool_t;

typedef  struct test_ar
{	
	int int_type ;
	double double_type;
}test_ar_t;

void *thread_function(void *arg);
void *master_thread_function(void *arg);
void p(sem_t *s);
void v(sem_t *s);
buf_pool_t *  buf_init(int num , size_t size);
void  add(buf_pool_t *sp ,void * value);
void  *get(buf_pool_t *sp , void *value);
void  release(buf_pool_t *sp) ;


void 
p(sem_t *s)
{
	if(sem_wait(s) < 0)
		fprintf(stderr,"sem_wait error \n");
}

void 
v(sem_t *s)
{
	if(sem_post(s) < 0)
		fprintf(stderr,"sem_post error \n");
}

buf_pool_t *  
buf_init(int num , size_t size)
{
    buf_pool_t *sp ; //declare *sp 
	sp = (buf_pool_t *)malloc(sizeof(buf_pool_t));
    sp->buf =calloc(num,size);
    sp->n = num;
	sp->size = size ;
    sp->front = sp->rear = 0 ;
    sem_init(&sp->mutex,0,1);
    sem_init(&sp->slots,0,num);
    sem_init(&sp->items,0,0);
    return sp;
}

void
add(buf_pool_t *sp ,void * value)
{
    p(&sp->slots);
    
    p(&sp->mutex);
    	int i =  (sp->rear)%(sp->n);
    	sp->rear++; 
    v(&sp->mutex);
	
   	memcpy(((sp->buf)+(i*(sp->size))),value,sp->size);
	v(&sp->items);
}

void 
release(buf_pool_t *sp)
{
	free(sp->buf);
	free(sp);
}

void * 
get(buf_pool_t *sp , void *value)
{
	p(&sp->items);
	
	p(&sp->mutex);
		int i  = (sp->front)%(sp->n);
		sp->front++;
	v(&sp->mutex);

	memcpy(value,(sp->buf+(i*(sp->size))),sp->size);
	printf("----test of value address--->0x%x  \n",(sp->buf+(i*(sp->size))));
	
	v(&sp->slots);

return value ;
}

void fprintPt( pthread_t pt) {
  unsigned char *ptc = (unsigned char*)(void*)(&pt);
  size_t i = 0;
  for ( i=0; i< sizeof(pt); i++) {
    printf( "%02x ", (unsigned)(ptc[i]));
  }
  printf(" i= %d \n",i);
}

int
main()
{
    buf_pool_t *sp ;
    sp = buf_init(PROD_NUM,sizeof(test_ar_t));
	
	int res  ; 
	pthread_t tid[THREAD_NUM] ; //store to child pthread
	pthread_t master_tid ;
	fprintPt(pthread_self());
	
	res = pthread_create(&master_tid,NULL,master_thread_function,sp);
	if (res != 0)
	{
		fprintf(stderr,"pthread was create error \n");
		exit(EXIT_FAILURE);	
    }
    
	for(int i = 0 ;i < THREAD_NUM ;i++) //the child thread 
	{
		res = pthread_create(&tid[i],NULL,thread_function,sp);
		if (res != 0)
		{
			fprintf(stderr,"pthread was create error \n");
			exit(EXIT_FAILURE);	
		}
	}
	printf("master thread : %lu  \n ", pthread_self());
	sleep(20);
    release(sp); 
	
return 0;
}

void *
thread_function(void *arg)
{
	pthread_detach(pthread_self());
	buf_pool_t *tmp ;
	tmp = (buf_pool_t *)arg ; 
    void *result_tmp ;
	test_ar_t * res, result ;
	int i  = 0;
	sleep(1);
	while (i < PROD_NUM - 12) 
	{
		result_tmp  = get(tmp,&result);
	  	res = (test_ar_t *)result_tmp ;
	  	printf("the result -->%d , %f , thread id : %lu \n",
	  			res->int_type,
				res->double_type,
				pthread_self());
		i++;
	}
	printf("consumer thread : %lu exit \n ", pthread_self());
	pthread_exit(0);
}

void *
master_thread_function(void *arg)
{
	pthread_detach(pthread_self());
	
	buf_pool_t *sp_master;
	sp_master = (buf_pool_t *)arg;
	test_ar_t tmp;
	for(int i = 0 ;i < PROD_NUM  ; i++)
	{
		tmp.int_type = i;
		tmp.double_type = (100.0 + i);
		add(sp_master, &tmp); //call the add 
	}
	printf("producter thread : %lu exit \n ", pthread_self());
	pthread_exit(0);
}
