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
    buf_pool sp ;
    buf_init(&sp,2,sizeof(double));
    printf("The 1 look_up  :\n");
    look_up(&sp);
    double i = 9.0;
    add(&sp,&i);
    printf("The 2 look_up  :\n");
    look_up(&sp);
void * h  = 	get(&sp,&i);
double  he;
he  = *(double *)h;   
 printf("The 3 look_up ,%f :\n",he);
	look_up(&sp);
//	release(&sp);
    printf("The 4  look_up  :\n");
	look_up(&sp);
    return 0;
}