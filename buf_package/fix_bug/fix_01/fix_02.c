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

#define  thread_num 1 
#define  pool_num   8
typedef struct
{
    void *  	buf ;
    size_t    	n;
    size_t 		front;
    size_t		rear;
	size_t		size; //the  struct of slots size  
    sem_t   mutex;  // 
    sem_t   slots; //available slots for producter
    sem_t   items; //available items for customer
}buf_pool;

typedef struct 
{
	void * param ; //Array *
	buf_pool *master_sp; //sp *
	size_t num ; //array length
}master_thread_param;

void *thread_function(void *arg);
void *master_thread_function(void *arg);
void p(sem_t *s);
void v(sem_t *s);
buf_pool *  buf_init(int num , size_t size);
buf_pool *  add(buf_pool *sp ,void * value);
void 	 *  get(buf_pool *sp , void *value);
void		release(buf_pool *sp) ;


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


buf_pool *  buf_init(int num , size_t size)
{
	
    buf_pool *sp ; //declare *sp 
	sp = (buf_pool *)malloc(sizeof(buf_pool));
    sp->buf =calloc(num,size);
    sp->n = num;
	sp->size = size ;
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
    memcpy(&sp->buf[i],value,sp->size);
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
	memcpy(value,&sp->buf[i],sp->size);
	sp->front++;
	v(&sp->mutex);

	v(&sp->slots);

return value ;
}

int main()
{
    buf_pool *sp ;

    sp = buf_init(pool_num,sizeof(int));
   	#if 0  //for test
	int i = 4 ;
	sp = add(sp,&i);  
	look_up(sp);  
	#endif 
	int res  ; 
	pthread_t tid[thread_num] ; //store to child pthread
	pthread_t master_tid ;
	int test_arry[] = {10,11,12,13};
	master_thread_param *mtp;
	mtp = (master_thread_param *)malloc(sizeof(master_thread_param));//apply memery
	mtp->master_sp = sp ; //point to buf_pool
	mtp->param = test_arry; //address of a test_array
	mtp->num = sizeof(test_arry)/sizeof(test_arry[0]);//array length	

	res = pthread_create(&master_tid,NULL,master_thread_function,mtp);
	if (res != 0)
	{
		fprintf(stderr,"pthread was create error \n");
		exit(EXIT_FAILURE);	
    }
    pthread_join(master_tid,NULL); 
#if 1 //for test 
	look_up(sp);
#endif
	
	for(int i = 0 ;i < thread_num ;i++) //the child thread 
	{
		res = pthread_create(&tid[i],NULL,thread_function,sp);
		if (res != 0)
		{
			fprintf(stderr,"pthread was create error \n");
			exit(EXIT_FAILURE);	
		}
	}
   
	for(int i = 0 ;i < thread_num ;i++) //joinable thread 
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
void *thread_function(void *arg)
{
	printf("child thread , it is successfull \n");
	buf_pool *tmp ;
	tmp = (buf_pool *)arg ; 
	printf("before !,the front---->%d \n",tmp->front);
	int result = 0 ,res ;
	void *result_tmp ;
	result_tmp  = get(tmp,&result);
	res = *(int *)result_tmp;
	printf("the result---->%d ,after ,the front :%d \n",res,tmp->front);
	sleep(1);
	return NULL ;
}

void *master_thread_function(void *arg)
{
	master_thread_param *tmp ;
	tmp = (master_thread_param *)arg;
	for(int i = 0 ;i < tmp->num  ; i++)
	{
		void *index ; //temp variable
		int cast_int = (int)(tmp->master_sp->size); //cast the void to int
		int offset =i * cast_int;// count the offset  
		memcpy(index,(tmp->param+offset),tmp->master_sp->size);
		printf("%d \n",*(int *)index); 
	 	tmp->master_sp	= add(tmp->master_sp,index); //call the add 
	}
	printf("form master thread num=%d \n",tmp->master_sp->rear);

	return NULL;
}
