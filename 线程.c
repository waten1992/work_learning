	线程： 线程拥有自己的栈；
		   共享:全局变量、文件描述符、信号处理函数、当前目录状态

		可重入例程：就是可重入代码可多次调用仍然能正常工作，通常变量只使用局部变量。每一次都是获得他的唯一数据副本；
		可以通过_REENTRANT来告诉编译器我需要可重入功能，定义在所有的#include 之前；
			1-函数的名字会用添加 _r
			2-stdio.h 中原来宏实现的一些函数变成了安全可重入函数；
			3-errno.h定义的errno变成了一个函数调用，他能以一种多线程安全的方式来获取正真的error值；
	#include <pthread.h>
		typedef void *(func)(void *);
		int pthread_create(pthread_t *tid, pthread_attr_t *attr,func *f, void *arg);
						Returns: 0 if OK, nonzero on error 

		tid ---> pthread_t 类型对象地址，保存对等线程的ID 
		attr---> 线程默认的属性
		f    --> 将要调用的线程函数
		arg  --> 传递给线程的函数的参数，想要传递多个参数可以用结构体;


	#include <pthread.h>
		pthread_t pthread_self(void);
				Returns: thread ID of caller 
			获取调用线程的ID

	#include <pthread.h>
		int pthread_join(pthread_t tid, void **thread_return);
			Returns: 0 if OK, nonzero on error
		阻塞函数，直到tid线程被回收，才将线例程返回的（void *） 指向thread_return 的位置

	#include <pthread.h>
		void pthread_exit(void *thread_return);
			Returns: 0 if OK, nonzero on error
			作用：某个对等线程调用了exit(),该函数终止进程和进程说有的线程；
				  另一个对等线程通过当前线程ID作为参数调用pthread_cancle 来终止当前的线程
	终止线程方式：
		1-当顶层的线程返回时，线程会隐式的终止；
		2-通过调用pthread_exit 函数，线程显示终止。如果是主线程调用pthread_exit ，他会等待所有的对等线程终止后，在终止主线程和整个进程，返回值为thread_return

	#include <pthread.h>
		int pthread_cancel(pthread_t tid);
			Returns: 0 if OK, nonzero on error

	#include <semaphore.h>
		int sem_init(sem_t *sem, int pshared, unsigned int value); //pshared 为0 ，就是进程内部的信号量，否则可以在进程间共享信号量
		int sem_wait(sem_t *s); /* P(s) */
		int sem_post(sem_t *s); /* V(s) */
			Returns: 0 if OK, −1 on error

	