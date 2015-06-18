#include "a.h"

void *thread_function(void * arg);
char message[] = "Hello this !";

int main()
{
	int res ;
	pthread_t a_thread ;
	void *pthread_result;
	res = pthread_create(&a_thread , NULL , thread_function , (void *)message);
	if(res != 0)
	{
		perror("Thread creation failed ");
		exit(EXIT_FAILURE);	
	}
	printf("Waiting for thread to fininsh -----\n");
	res = pthread_join(a_thread,&pthread_result);
	if(res != 0)
	{
		perror("Thread joined failed \n");
			
		exit(EXIT_FAILURE);	
	}
	printf("Thread joined ,it returned %s \n",(char *)pthread_result);
	printf("Message is now %s \n",message);
exit(EXIT_SUCCESS);
}

void *thread_function(void *arg)
{
	printf("thread_function is running ,Argument was %s \n",(char *)arg);
	sleep(3);
	strcpy(message,"bye !");
	pthread_exit("Thank  you for the cpu time \n ");	
	printf("could be reach !!!!!\n");
}
