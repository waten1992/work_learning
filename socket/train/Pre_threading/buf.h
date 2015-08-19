#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<semaphore.h>
#include<malloc.h>
#include <syslog.h>
#include<unistd.h>

typedef struct 
{
	size_t  *buf ;
	size_t  num ;
    size_t  front ;
    size_t  rear ;
    sem_t   slots;
    sem_t  items ;
	sem_t  mutex ;
}pool ;


void p(sem_t *s);
void v(sem_t *s);
void error_handle(int num);
void init_pool(pool *sp, size_t N);
void pool_insert(size_t element , pool *sp);
size_t pool_remove(pool *sp );
void release(pool *sp);
