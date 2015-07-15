#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<sys/time.h>
#define  PTHREAD_LOCK  1
#define pthread_num 2
int g_count = 0 ;
pthread_mutex_t mutex_p = PTHREAD_MUTEX_INITIALIZER;
extern int cunit_test_main(int loop_time);


void * my_thread( void * arg )
{
	int loop_time =* ((int *)arg); 
	for (int i = 0 ;i < loop_time ;i++)
//		 __sync_fetch_and_add (&g_count, 1);
#if 1 
	{
		pthread_mutex_lock(&mutex_p);
		g_count++;
		pthread_mutex_unlock(&mutex_p);
	}
#endif
return NULL ;
}

int cunit_test_main(int loop_time)
{
	pthread_t pid[pthread_num];
	struct timeval t1 , t2 ;
	gettimeofday(&t1,NULL);
	for(int i = 0 ; i< pthread_num ; i++)
		pthread_create(&pid[i],NULL,my_thread,&loop_time);
	for(int i = 0 ; i< pthread_num ; i++)
		pthread_join(pid[i],NULL);
	gettimeofday(&t2,NULL);
	
	double t = (t2.tv_sec -t1.tv_sec)*1000 +(t2.tv_usec - t1.tv_usec)/1000;

	printf("g_count:%d , used: %f ms \n",g_count , t);

return g_count ;
}
