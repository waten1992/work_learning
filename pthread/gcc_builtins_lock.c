#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<sys/time.h>
#include<semaphore.h>
//#define  PTHREAD_LOCK  1
#define pthread_num 	20
static int g_count = 0 ;
pthread_mutex_t mutex_p = PTHREAD_MUTEX_INITIALIZER;
static sem_t mutex ;
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
	for (int i = 0 ;i < loop_time ;i++)
//		 __sync_fetch_and_add (&g_count, 1);
#ifdef PTHREAD_LOCK
	{
		pthread_mutex_lock(&mutex_p);
		g_count++;
		pthread_mutex_unlock(&mutex_p);
	}
#else
	{
		p(&mutex);
			g_count++;
		v(&mutex);
	}
#endif
return NULL ;
}

int main()
{
	pthread_t pid[pthread_num];
	struct timeval t1 , t2 ;
	gettimeofday(&t1,NULL);
	sem_init(&mutex,0,1);	
 	int loop_time =	 1000000;
	for(int i = 0 ; i< pthread_num ; i++)
		pthread_create(&pid[i],NULL,my_thread,&loop_time);
	for(int i = 0 ; i< pthread_num ; i++)
		pthread_join(pid[i],NULL);
	gettimeofday(&t2,NULL);
	
	double t = (t2.tv_sec -t1.tv_sec)*1000 +(t2.tv_usec - t1.tv_usec)/1000;
	printf("g_count:%d , used: %f \n",g_count , t);

	sem_destroy(&mutex);

return 0 ;
}
