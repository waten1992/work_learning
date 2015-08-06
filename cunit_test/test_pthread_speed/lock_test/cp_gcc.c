#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<sys/time.h>
#include <bits/types.h>
#include <unistd.h>
#include<semaphore.h>
#define		SYNC			4
#define 	pthread_num 	2
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
	struct timespec   t1 , t2 ;
//	printf("------start----- \n");
	timespec_get(&t1, TIME_UTC);
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
{		g_count++;
}
#endif
	timespec_get(&t2, TIME_UTC);
	double t = (t2.tv_sec -t1.tv_sec)*1000000000 +(t2.tv_nsec - t1.tv_nsec);
	printf("come from pthread g_count:%d , used: %f ns \n",g_count , t);
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

