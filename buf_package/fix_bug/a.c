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

#define  thread_num 4 
#define  pool_num   8
typedef struct
{
    void *  buf ;
    int     n;
    int     front;
    int     rear;

    sem_t   mutex;
    sem_t   slots;
    sem_t   items;
}buf_pool;


void *thread_function(void *arg);
void *master_thread_function(void *arg);

void p(sem_t *s)
{
	if(sem_wait(s) < 0)
		fprintf(stderr,"sem_wait error \n");
}

void v(sem_t *s)
{
	if(sem_post(s) < 0)
		fprintf(stderr,"sem_post error \n");
}


buf_pool *  buf_init( int num , size_t size)
{
	buf_pool *sp; //declare *sp  
    sp->buf =calloc(num,size);//apply num*size char
    sp->n = num; //num = slots+items
    sp->front = sp->rear = 0 ;
    sem_init(&sp->mutex,0,1);
    sem_init(&sp->slots,0,num);
    sem_init(&sp->items,0,0);
    return sp;
}
void look_up(buf_pool *sp)
{
    printf("sp->num:%d\n",sp->n);
    printf("sp->front:%d \n",sp->front);
    printf("sp->rear:%d \n",sp->rear);
}
buf_pool * add(buf_pool *sp ,void * value)
{
    p(&sp->slots);
    
    p(&sp->mutex);
    int i =  (sp->rear)%(sp->n);
    memcpy(&sp->buf[i],value,1); //memcpy value to buf 
    sp->rear++; 
    v(&sp->mutex);

    v(&sp->items);
return  sp; 
}

void release(buf_pool *sp)
{
	free(&sp->buf);
}
void * get(buf_pool *sp , void *value)
{
	p(&sp->items);
	
	p(&sp->mutex);
	int i  = (sp->front)%(sp->n);
	memcpy(value,&sp->buf[i],1); //buf to value  
	sp->front++;
	v(&sp->mutex);

	v(&sp->slots);
return value ;
}

typedef struct
{
	buf_pool *sp;
	void * contents;
}param;

int main()
{
    
	buf_pool *sp ;
	sp =	buf_init(pool_num,sizeof(int));
    
  
	int res ;
	pthread_t tid[thread_num] ;
	pthread_t master_tid[thread_num] ;
    int slots_contents[] = {11,12,13,14};
	int slots_contents_lens = sizeof(slots_contents)/sizeof(slots_contents[0]);	
	for(int i = 0  ; i <  slots_contents_lens ; i++)
	{

		res = pthread_create(&master_tid[i],NULL,master_thread_function,(void *)slots_contents[i]);
		if (res != 0)
		{
			fprintf(stderr,"pthread was create error \n");
			exit(EXIT_FAILURE);	
   		 }
	}
	for(int i = 0 ;i < thread_num ;i++)
   	{
		res  = pthread_join(master_tid[i],NULL);
 		if(res != 0)
		{
			fprintf(stderr,"thread join failed \n");
			exit(EXIT_FAILURE);	
		}
	}

	for(int i = 0 ;i < thread_num ;i++)
	{
		res = pthread_create(&tid[i],NULL,thread_function,(void *)i);
		if (res != 0)
		{
			fprintf(stderr,"pthread was create error \n");
			exit(EXIT_FAILURE);	
		}
	}
   
	for(int i = 0 ;i < thread_num ;i++)
   	{
		res  = pthread_join(tid[i],NULL);
 		if(res != 0)
		{
			fprintf(stderr,"thread join failed \n");
			exit(EXIT_FAILURE);	
		}	
	}
   
return 0;
}
void hello()
{
	printf("hello \n");
}
void *thread_function(void *arg)
{
	printf("Come from peer thread :%d \n",arg);

	int  i  ;
	get(&sp,&i);
	look_up(&sp);
	printf("--- i = %d \n",i);
    pthread_exit(NULL);
		hello();
}


void *master_thread_function(void *arg)
{
	add(&sp,&arg);	
	look_up(&sp);
	printf("form master thread \n");
	pthread_exit(NULL);
}
