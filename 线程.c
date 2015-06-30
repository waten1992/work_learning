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

		int pthread_detach(pthread_t tid);
			Returns: 0 if OK, nonzero on error
		线程是可结合的(joinable)或者分离的(detached)
			可结合的:可以被其他的线程杀死和回收资源，但是在被其他线程回收之前，存储器（比如 ：栈）是没有被释放的；
			分离线程：不能被其他的线程杀死，存储器是自动被回收的；避免了内存泄漏
			和pthread_detach 配合使用来分离它们自己；

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
		int sem_wait(sem_t *s); /* P(s) */ //阻塞 
		int sem_post(sem_t *s); /* V(s) */
		int sem_destory(sem_t *s) ; //销毁信号量
			Returns: 0 if OK, −1 on error

		int sem_trywait(sem_t *s ) ; //非阻塞方式 
		---------------------------------------------------------------------
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
		包装函数，使用熟悉的P V 操作！ 
-----------------------------------------------------------------
	strncmp(s,t,n)		same as strcmp but only in first n characters

	线程的互斥：
	#include <pthread.h>
	int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);
	int pthread_mutex_lock(pthread_mutex_t *mutex));
	int pthread_mutex_unlock(pthread_mutex_t *mutex);
	int pthread_mutex_destroy(pthread_mutex_t *mutex);
	As usual, 0 is returned for success, and on failure an error code is returned, but errno is not set; you
	must use the return code.

	线程的属性：

	分离线程：不能被其他的线程杀死，存储器是自动被回收的；避免了内存泄漏分离线程：
	#include <pthread.h>
			int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);

			detachedstate: This attribute allows you to avoid the need for threads to rejoin. As with
			most of these _set functions, it takes a pointer to the attribute and a flag to determine the
			state required. The two possible flag values for pthread_attr_setdetachstate are
			PTHREAD_CREATE_JOINABLE and PTHREAD_CREATE_DETACHED. By default, the attribute will
			have the value PTHREAD_CREATE_JOINABLE so that you can allow the two threads to join. If
			the state is set to PTHREAD_CREATE_DETACHED, you cannot call pthread_join to recover the
			exit state of another thread.
			修改属性 : 可分离线程参见：pthread_detach

	调度线程：
			int pthread_attr_setschedpolicy(pthread_attr_t *attr, int policy);

			schedpolicy: This controls how threads are scheduled. The options are SCHED_OTHER,
			SCHED_RP, and SCHED_FIFO. By default, the attribute is SCHED_OTHER. The other two types of
			scheduling are available only to processes running with superuser permissions, because they
			both have real-time scheduling but with slightly different behavior. SCHED_RR uses a roundrobin
			scheduling scheme, and SCHED_FIFO uses a “first in, first out” policy. Discussion of these
			is beyond the scope of this book.
			SCHED_RP, and SCHED_FIFO	----- real-time scheduling，running with superuser permissions 
			SCHED_OTHER					----- default
			SCHED_RR					----- roundrobin

			int pthread_attr_setschedparam(pthread_attr_t *attr, const struct sched_param *param);

			schedparam: This is a partner to schedpolicy and allows control over the scheduling of
			threads running with schedule policy SCHED_OTHER. 



	线程安全问题：
		四类不安全的类：
			1-不保护共享变量的函数，即全局变量；
					解决方案： 对变量进行 P V 操作
						优点：调用的函数不用修改；
						缺点：同步操作减慢程序执行时间；
			2-保持跨越多个调用的状态函数：一个程序调用的结果依赖前次调用的结果；
					解决方案：对不安全的重新写过；不让它在调用任何的static数据；
					缺点： 如果工程有上千个函数，那么你就要哭了；
			3-返回指向静态变量的指针函数；
					解决方案：重新写过、加锁-拷贝技术，
						把不安全的结果拷贝到一个私有的存储器的地方，然后互斥加锁，尽可能的减少对调用者的修改；
					例子：
					 char *ctime_ts(const time_t *timep, char *privatep)
					 {
						 char *sharedp;
						
						 P(&mutex);
						 sharedp = ctime(timep);
						 strcpy(privatep, sharedp); /* Copy string from shared to private */
						 V(&mutex);
						 return privatep;
					 }
			4-调用其他不安全的函数：

