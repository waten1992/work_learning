/*生产者消费者模型*/
/*
	mutex---> 对正在生产或者消费的程序的互斥锁；
	items---> 针对消费者说的；
	slots---> 针对生产者所得；
	关系： items + slots = mutex ;

*/
#include "buf_package.h"

void sbuf_init(sbuf_t *sp, int n);
void sbuf_deinit(sbuf_t *sp);
void sbuf_insert(sbuf_t *sp, int item);
int sbuf_remove(sbuf_t *sp);
void Sem_init(sem_t *sem, int pshared, unsigned int value) ;
void P(sem_t *sem) ;
void V(sem_t *sem) ;
void *Calloc(size_t nmemb, size_t size) ;
void Free(void *ptr) ;

void look(sbuf_t *sp);


    sbuf_t buf ;
static sem_t mutex;


int main()
{
    int input_sizes ;
    char Input_type[10];
    memset(Input_type,0,10);
    printf("Welcome to buff_pool !!!\n");
    printf("Pool NUM of sizes --->");
    scanf("%d",&input_sizes);
    printf("Input_type --->");
    scanf("%s",&Input_type);
  
    printf("%s , %d  \n",Input_type,input_sizes);
  
    sbuf_init(&buf,input_sizes);
    look(&buf);

  return 0 ;
}

void unix_error(char *msg) /* Unix-style error */
{
	    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	        exit(0);
}
/* $end unixerror */

void look(sbuf_t *sp)
{
    printf("sp->n %d\n",sp->n);
}   

void sbuf_init(sbuf_t *sp, int n)
{
	 sp->buf = Calloc(n, sizeof(int));
	 sp->n = n; /* Buffer holds max of n items */
	 sp->front = sp->rear = 0; /* Empty buffer iff front == rear */
	 Sem_init(&sp->mutex, 0, 1); /* Binary semaphore for locking */
	 Sem_init(&sp->slots, 0, n); /* Initially, buf has n empty slots */
	 Sem_init(&sp->items, 0, 0); /* Initially, buf has zero data items */
 }

 /* Clean up buffer sp */
 void sbuf_deinit(sbuf_t *sp)
 {
 	Free(sp->buf);
 }

 /* Insert item onto the rear of shared buffer sp */
 void sbuf_insert(sbuf_t *sp, int item)
 {
	 P(&sp->slots); /* Wait for available slot */
	 P(&sp->mutex); /* Lock the buffer */
	 sp->buf[(++sp->rear)%(sp->n)] = item; /* Insert the item */
	 V(&sp->mutex); /* Unlock the buffer */
	 V(&sp->items); /* Announce available item */
 }

/* Remove and return the first item from buffer sp */
 int sbuf_remove(sbuf_t *sp)
 {
	 int item;
	 P(&sp->items); /* Wait for available item */
	 P(&sp->mutex); /* Lock the buffer */
	 item = sp->buf[(++sp->front)%(sp->n)]; /* Remove the item */
	 V(&sp->mutex); /* Unlock the buffer */
	 V(&sp->slots); /* Announce available slot */

	return item;
}

void Sem_init(sem_t *sem, int pshared, unsigned int value) 
{
	if (sem_init(sem, pshared, value) < 0)
		unix_error("Sem_init error");
}
		
void P(sem_t *sem) 
{
	if (sem_wait(sem) < 0)
		unix_error("P error");
}
		
void V(sem_t *sem) 
{
	if (sem_post(sem) < 0)
		unix_error("V error");
}

void *Calloc(size_t nmemb, size_t size) 
{
    void *p;

    if ((p = calloc(nmemb, size)) == NULL)
	unix_error("Calloc error");
    return p;
}

void Free(void *ptr) 
{
    free(ptr);
}
