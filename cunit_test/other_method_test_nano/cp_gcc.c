#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<sys/time.h>
#include<semaphore.h>

#define		SYNC			1
#define 	pthread_num 	2
//#define 	CAL_TIME		1
# define HP_TIMING_NOW(Var) \
 ({ unsigned long long _hi, _lo; \
  asm volatile ("rdtsc" : "=a" (_lo), "=d" (_hi)); \
  (Var) = _hi << 32 | _lo; })

int g_count = 0 ;
static sem_t mutex ;
pthread_spinlock_t lock;
pthread_mutex_t mutex_p = PTHREAD_MUTEX_INITIALIZER;
extern int cunit_test_main(int loop_time);
void do_something();
void p(sem_t *s);
void v(sem_t *s);

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


void * my_thread( void * arg )
{
	int loop_time =* ((int *)arg); 
	unsigned long start, end;
#ifdef CAL_TIME
	struct timeval t1 , t2 ;
	gettimeofday(&t1,NULL);
#else 
HP_TIMING_NOW(start);
//Interrupt_handler (int irq, void *data);   
#endif
	for (int i = 0 ;i < loop_time ;i++)
#if SYNC == 1
{
		 __sync_fetch_and_add (&g_count, 1);
}
#elif SYNC == 2  
	{
		pthread_mutex_lock(&mutex_p);
		g_count++;
		pthread_mutex_unlock(&mutex_p);
	}
#elif SYNC == 3  
{
	p(&mutex);
			g_count++;
	v(&mutex);

}
#elif SYNC == 4
{
	pthread_spin_lock(&lock);
	g_count++;
	pthread_spin_unlock(&lock);
}
#else
{
		g_count++;
}
#endif
#ifdef CAL_TIME
	gettimeofday(&t2,NULL);
	double t = (t2.tv_sec -t1.tv_sec)*1000000 +(t2.tv_usec - t1.tv_usec);
	printf("come from pthread g_count:%d , used: %f us \n",g_count , t);
#else
HP_TIMING_NOW(end);
printf("\n the cost cycles are %lf\n", (end - start)/3.6);
#endif
return NULL ;
}

int cunit_test_main(int loop_time)
{
	pthread_t pid[pthread_num];
	struct timeval t1 , t2 ;
#if SYNC == 3
	sem_init(&mutex,0,1);
#elif SYNC ==4
	pthread_spin_init(&lock,PTHREAD_PROCESS_PRIVATE);
#endif 
	gettimeofday(&t1,NULL);
	for(int i = 0 ; i< pthread_num ; i++)
		pthread_create(&pid[i],NULL,my_thread,&loop_time);
	for(int i = 0 ; i< pthread_num ; i++)
		pthread_join(pid[i],NULL);
	gettimeofday(&t2,NULL);
	double t = (t2.tv_sec -t1.tv_sec)*1000000 +(t2.tv_usec - t1.tv_usec);
	printf("g_count:%d , used: %f us \n",g_count , t);
#if SYNC == 3
	sem_destroy(&mutex);
#elif SYNC == 4
	pthread_spin_destroy(&lock);
#endif
return g_count ;
}

