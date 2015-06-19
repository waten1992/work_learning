/* buf_package.h 头文件*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>
#include<ctype.h>
typedef int  int_type ;
typedef struct 
{
	 int_type 	*buf; /* Buffer array */
	 int		 n; /* Maximum number of slots */
	 int 		front; /* buf[(front+1)%n] is first item */
	 int 		rear; /* buf[rear%n] is last item */
	 sem_t		mutex; /* Protects accesses to buf */
	 sem_t 		slots; /* Counts available slots */
	 sem_t 		items; /* Counts available items */
 } sbuf_t;

 
/* Our own error-handling functions */
void unix_error(char *msg);

/* POSIX semaphore wrappers */
void Sem_init(sem_t *sem, int pshared, unsigned int value);
void P(sem_t *sem);
void V(sem_t *sem);

/* Dynamic storage allocation wrappers */
void *Malloc(size_t size);
void *Realloc(void *ptr, size_t size);
void *Calloc(size_t nmemb, size_t size);
void Free(void *ptr);

