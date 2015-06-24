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

typedef struct 
{
	size_t n ; //	
};

buf_pool sp ;
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


buf_pool *  buf_init(buf_pool *sp , int num , size_t size)
{
    sp->buf =calloc(num,size);
    sp->n = num;
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
    memcpy(&sp->buf[i],value,1);
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
	memcpy(value,&sp->buf[i],1);
	sp->front++;
	v(&sp->mutex);

	v(&sp->slots);
return value ;
}

int main()
{
    buf_init(&sp,pool_num,sizeof(int));
    
/* //for test 
    printf("The 1 look_up  :\n");
    look_up(&sp);
    int i = 9;
    add(&sp,&i);
    printf("The 2 look_up  :\n");
    look_up(&sp);
	void * h  = 	get(&sp,&i);
	int  he;
	he  = *(int *)h;   
 	printf("The 3 look_up ,%d :\n",he);
	look_up(&sp);
//	release(&sp);
    printf("The 4  look_up  :\n");
	look_up(&sp);
*/
    
   // char my_struct[] = "hey !" ;
	int res , input_slots = 1 ;
	pthread_t tid[thread_num] ;
	pthread_t master_tid ;
	
	res = pthread_create(&master_tid,NULL,master_thread_function,(void *)input_slots);
	if (res != 0)
	{
		fprintf(stderr,"pthread was create error \n");
		exit(EXIT_FAILURE);	
    }
    pthread_join(master_tid,NULL);
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
	hello();
	int i = 0 ;
	get(&sp,&i);
	look_up(&sp);
	printf("--- i = %d \n",i);
    pthread_exit(NULL);
}

void *master_thread_function(void *arg)
{

    add(&sp,&arg);	
	look_up(&sp);
	printf("form master thread \n");
}
