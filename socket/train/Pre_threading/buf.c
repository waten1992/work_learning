#include "buf.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
typedef struct 
{
	void 	*buf ;
	size_t  num ;
	size_t 	front ;
	size_t  rear ;
	size_t  slots;
	size_t  items ;
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
void error_handle(int num)
{
	if(num != 0)
	{
		syslog(LOG_ERR, "%s\n", strerror(errno));
		return -1 ;
	}
}
pool * init_pool( size_t N ,size_t element_size)
{
	pool *sp;
	int ret ; 
	sp = (struct  pool *) malloc(sizeof(struct pool));
	sp->num	 = N ;
	sp->rear = sp->front	= 0 ;
    ret =	sem_init(&sp->slots,0,N);
	error_handle(ret);	
	ret = sem_init(&sp->items,0,0);
	error_handle(ret);

	sp->buf = (void *)calloc(N*element_size);
return sp;
}

pool *add(pool *sp  , void  element )
{
	p(&sp->slots);
	pthread_mutex_lock(&mutex);
		
	pthread_mutex_unlock(&mutex);
	v(&sp->items);
}
