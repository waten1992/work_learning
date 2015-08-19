#include "buf.h"
#include "pre_thread.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<semaphore.h>
#include<malloc.h>
#include <syslog.h>
#include<unistd.h>

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

void error_handle(int num)
{
	if(num != 0)
	{
		syslog(LOG_ERR, "%s\n", strerror(errno));
		return NULL ;
	}
}

void init_pool( pool *sp ,size_t N)
{
	int ret ; 
	sp->buf = calloc(N,sizeof(int));
	sp->num	 = N ;
	sp->rear = sp->front	= 0 ;
    ret =	sem_init(&sp->slots,0,N);
	error_handle(ret);	
	ret = sem_init(&sp->items,0,0);
	error_handle(ret);
	sem_init(&sp->mutex,0,1);
}
void pool_insert(size_t  element , pool *sp )
{
	p(&sp->slots);
	p(&sp->mutex);
	sp->front++;
	sp->buf[(sp->front)%(sp->num)] =element ;
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
	v(&sp->mutex);
	v(&sp->slots);
return tmp_item ;
};

void pool_release(pool *sp)
{
	free(sp->buf);
}

