	----------------------------------------

	第一周的问题：

	1-为什么用了uwsgi，还需要用Tornado?
	2-实时性处理的流程不是很清楚？

	----------------------------------------
	第三周的问题
	1-makefile 中的  order-only 
		4.3 Types of Prerequisites

		There are actually two different types of prerequisites understood by GNU make: normal prerequisites such as described in the previous section, and order-only prerequisites. A normal prerequisite makes two statements: first, it imposes an order in which recipes will be invoked: the recipes for all prerequisites of a target will be completed before the recipe for the target is run. Second, it imposes a dependency relationship: if any prerequisite is newer than the target, then the target is considered out-of-date and must be rebuilt.

		Normally, this is exactly what you want: if a target’s prerequisite is updated, then the target should also be updated.

		Occasionally, however, you have a situation where you want to impose a specific ordering on the rules to be invoked without forcing the target to be updated if one of those rules is executed. In that case, you want to define order-only prerequisites. Order-only prerequisites can be specified by placing a pipe symbol (|) in the prerequisites list: any prerequisites to the left of the pipe symbol are normal; any prerequisites to the right are order-only:

		targets : normal-prerequisites | order-only-prerequisites
		The normal prerequisites section may of course be empty. Also, you may still declare multiple lines of prerequisites for the same target: they are appended appropriately (normal prerequisites are appended to the list of normal prerequisites; order-only prerequisites are appended to the list of order-only prerequisites). Note that if you declare the same file to be both a normal and an order-only prerequisite, the normal prerequisite takes precedence (since they have a strict superset of the behavior of an order-only prerequisite).

		Consider an example where your targets are to be placed in a separate directory, and that directory might not exist before make is run. In this situation, you want the directory to be created before any targets are placed into it but, because the timestamps on directories change whenever a file is added, removed, or renamed, we certainly don’t want to rebuild all the targets whenever the directory’s timestamp changes. One way to manage this is with order-only prerequisites: make the directory an order-only prerequisite on all the targets:

		OBJDIR := objdir
		OBJS := $(addprefix $(OBJDIR)/,foo.o bar.o baz.o)

		$(OBJDIR)/%.o : %.c
		        $(COMPILE.c) $(OUTPUT_OPTION) $<

		all: $(OBJS)

		$(OBJS): | $(OBJDIR)

		$(OBJDIR):
		        mkdir $(OBJDIR)
		Now the rule to create the objdir directory will be run, if needed, before any ‘.o’ is built, but no ‘.o’ will be built because the objdir directory timestamp changed.


		2- x.h.gch 的产生；
			GCC为编译数度而产生的预编译头文件
			比如：一个头文件a.h 包含了#include<stdio.h> #include<stdio.h>  
				1- gcc a.h
					会产生a.h.gch
				2- 创建一个test.c 引用头文件a.h
					gcc  -o test test.c -H 
					就会输出：
							! a.h.gch
 							test.c
 			即：gcc 不用再去/usr/include 文件查找头文件了，而是直接在当前目录下调用a.h.gch文件;
 		VIM 中精确匹配一个单词  / \<good\> 
 			"\>" 表示只匹配单词末尾;
 			"\<" 只匹配单词的开头;

 		3-据说在信号处理程序中调用printf() 函数不安全
 			解释：像printf()和malloc()之类的标准库函数，它们会使用全局的数据（比如malloc()需要使用进程的堆数据结构）是不可重入的，即使加锁也无法解决，加锁可以使得库函数Tread-safe，但是无法解决可重入。

 		4-do_fork() 执行流程？
 			参考：http://bbs.chinaunix.net/thread-2011594-1-1.html
 		5-如何杀死僵尸进程？
 			pwd006@Debain:~/test/process$ ./defunct   //生成僵尸进程
			alarm application starting 
			waiting for alarm to go off 
			^Z
			[1]+  Stopped                 ./defunct   //挂起僵尸进程
			pwd006@Debain:~/test/process$ ps -ef | grep defunct   
			pwd006   10411  4333  0 14:55 pts/0    00:00:00 ./defunct
			pwd006   10412 10411  0 14:55 pts/0    00:00:00 [defunct] <defunct>
			pwd006   10417  4333  0 14:55 pts/0    00:00:00 grep defunct
			pwd006@Debain:~/test/process$ ps -A | grep defunct   //查看僵尸进程
			10411 pts/0    00:00:00 defunct
			10412 pts/0    00:00:00 defunct <defunct>
			pwd006@Debain:~/test/process$ kill -9 10412   //尝试杀死进程  
			pwd006@Debain:~/test/process$ ps -ef | grep defunct   //结果还是存在，没有被弄死
			pwd006   10411  4333  0 14:55 pts/0    00:00:00 ./defunct
			pwd006   10412 10411  0 14:55 pts/0    00:00:00 [defunct] <defunct>
			pwd006   10425  4333  0 14:56 pts/0    00:00:00 grep defunct
			pwd006@Debain:~/test/process$ jobs    //原来的进程仍然存在
			[1]+  Stopped                 ./defunct
			pwd006@Debain:~/test/process$ kill -9 10411   //kill 掉原来的进程 
			pwd006@Debain:~/test/process$ jobs
			[1]+  Killed                  ./defunct
			pwd006@Debain:~/test/process$ ps -ef | grep defunct //发现僵尸进程也被干掉了
			pwd006   10429  4333  0 14:57 pts/0    00:00:00 grep defunct
			pwd006@Debain:~/test/process$ 

		问题：
			1- 为什么主进程被干掉后，僵尸进程也被干掉了？
 				主进程也就是父进程，当父进程被干掉之后。子进程就变成了孤儿进程，被init收养最后通过wait回收；
 				当父进程没有使用wait回收子进程，且子进程退出了就会成为僵尸进程。
 				子进程是继承父进程的东西，属于同一个组。父亲被kill 子进程也被kill了
			2-不是说进程都是独立的地址空间，为什么通过kill pid 不行？
-----------------------------------------------------------------------------

	周三的问题：
			1-编写一个shell ，杀掉所有的僵尸进程；在shell 里面 执行bash命令后输出的参数是什么形式的 字符串还是？
				代码如下：
				  1 #!/bin/sh
				  2 if [ 0 -ne ` ps -e -o stat,ppid,pid,cmd | grep -e '^[Zz]'| wc -l ` ]  #  ` ` 使用把输出的字变成数字
				  3 then
				  4 {
				  5         ps -e -o stat,ppid,pid,cmd | grep -e '^[Zz]' | awk '{print $2}' | xargs kill -9
				  6 }
				  7 else
				  8         echo "You system did't find zombie "
				  9 fi
				 10 
				 11 exit 0
			2-线程问题？为什么是3次？
				pwd006@Debain:~/work_learning/pthread$ ./3a 
				Input some text. Enter 'end' to finish
				hey !
				You input 5 characters
				FAST
				You input 1 characters
				You input 1 characters
				You input 1 characters
				end

				Waiting for thread to finish...
				Thread joined
				pwd006@Debain:~/work_learning/pthread$ 
				-------------------------------------------------
			解答：
			 while(strncmp("end", work_area, 3) != 0) {
	   32       if (strncmp(work_area, "FAST", 4) == 0) {
	   33         sem_post(&bin_sem);
	   34         strcpy(work_area, "hi");    FAST hi
	   35       } else {
	   36         fgets(work_area, WORK_SIZE, stdin);
	   37       }
	   38       sem_post(&bin_sem);
	   39     }

	   		在这个例子中主线程是优先的；
	   		  第一次 增加是fgets 中的FAST  38行增加
	   		  第二次 是FAST == 4 if 32行增加
	   		  第三次 也是 38 行 

	   		  为什么 hi 是2个字符却输出1个字符？ strcpy 、 strncmp 、fgets 是怎么实现？

	   		  	/* fgets: get at most n chars from iop */
				char *fgets(char *s, int n, FILE *iop)
				{
					register int c;
					register char *cs;
					cs = s;
					while (--n > 0 && (c = getc(iop)) != EOF)
						if ((*cs++ = c) == '\n')
							break;
					*cs = '\0'; //默认是在输入后添加 '\0'
					
					return (c == EOF && cs == s) ? NULL : s;
				}


				/* strcpy: copy t to s; pointer version 2 */
				void strcpy(char *s, char *t) 
				{
				while ((*s++ = *t++) != '\0')  
						;
				}
			
				fgets 默认是在'\n'后面添加  '\0';
				strcpy 是已经拷贝'\0' ;


				而同步线程的语句是：
				printf("You input %d characters\n", strlen(work_area) -1);
				strlen 遇到'\0' 就停下来，不包含'\0' 的长度；
				FAST\n\0    5-1 = 4
				hi\0ST\n\0  2-1 = 1

			3-线程是也是并发的？
				线程是并发的。
				并没有像按顺序的那样输出而是随意的输出。
				例子一：不能保证输出的是正确的参数！
				pwd006@Debain:~/work_learning/pthread$ gcc -D_REENTRANT Concurrency_pthread.c -g -o conc -lpthread
				pwd006@Debain:~/work_learning/pthread$ ./conc 
				hello from thread 2  
				hello from thread 3  
				hello from thread 3  
				hello from thread 0  
				pwd006@Debain:~/work_learning/pthread$ ./conc 
				hello from thread 3  
				hello from thread 3  
				hello from thread 2  
				hello from thread 0  
				pwd006@Debain:~/work_learning/pthread$ ./conc 
				hello from thread 3  
				hello from thread 3  
				hello from thread 2  
				hello from thread 0  
				pwd006@Debain:~/work_learning/pthread$ ./conc 
				hello from thread 2  
				hello from thread 0  
				hello from thread 0  
				hello from thread 0  
				pwd006@Debain:~/work_learning/pthread$ 

				例子二： 能保证每一个参数能准确的传递，但是不能线程的顺序！！！！
				pwd006@Debain:~/work_learning/pthread$ vi conc_correct.c 
				pwd006@Debain:~/work_learning/pthread$ gcc -D_REENTRANT conc_correct.c -g -o conc_correct -lpthread
				pwd006@Debain:~/work_learning/pthread$ ./conc_correct 
				hello from thread 2  
				hello from thread 1  
				hello from thread 0  
				hello from thread 3  
				pwd006@Debain:~/work_learning/pthread$ ./conc_correct 
				hello from thread 0  
				hello from thread 2  
				hello from thread 3  
				hello from thread 1  
				pwd006@Debain:~/work_learning/pthread$ ./conc_correct 
				hello from thread 0  
				hello from thread 3  
				hello from thread 1  
				hello from thread 2  
				pwd006@Debain:~/work_learning/pthread$ ./conc_correct 
				hello from thread 0  
				hello from thread 3  
				hello from thread 1  
				hello from thread 2  
				pwd006@Debain:~/work_learning/pthread$ ./conc_correct 

-----------------------------------------------------------------------
2015-6-18
			1-线程的获取锁是怎么实现的？线程是轮询信号量，还是事件驱动？

			2-改变调度策略？ 仍然不能实现先运行？

---------------------------------------------------------------------------
2015-6-19

		1-在编译的时候出现了
				/tmp/ccEZ69P1.o: In function `Pthread_create':
				csapp.c:(.text+0x1019): undefined reference to `pthread_create'
				/tmp/ccEZ69P1.o: In function `Pthread_cancel':
				csapp.c:(.text+0x104b): undefined reference to `pthread_cancel'
				/tmp/ccEZ69P1.o: In function `Pthread_join':
				csapp.c:(.text+0x1088): undefined reference to `pthread_join'
				/tmp/ccEZ69P1.o: In function `Pthread_detach':
				csapp.c:(.text+0x10ba): undefined reference to `pthread_detach'
				/tmp/ccEZ69P1.o: In function `Pthread_once':
				csapp.c:(.text+0x111a): undefined reference to `pthread_once'
				/tmp/ccEZ69P1.o: In function `Sem_init':
				csapp.c:(.text+0x1142): undefined reference to `sem_init'
				/tmp/ccEZ69P1.o: In function `P':
				csapp.c:(.text+0x116a): undefined reference to `sem_wait'
				/tmp/ccEZ69P1.o: In function `V':
				csapp.c:(.text+0x1192): undefined reference to `sem_post'
				collect2: error: ld returned 1 exit status

			原因是没有加入 -lpthread 的参数 ，找不到定义的头文件；

  		2-生产者和消费者模型
  				全局变量：
  						1- 互斥信号量    static sem_t mutex;  
  						2- 槽位信号量    sbuf_t buf ;

  				mutex---> 对正在生产或者消费的程序的互斥锁；
				items---> 针对消费者说的；
				slots---> 针对生产者所得；
				关系： items + slots = mutex ;

				找不到sem_t 结构的值，gdb 查看是这样的 
				(gdb) p sp->slots
				$2 = {__size = "\a\000\000\000\200", '\000' <repeats 26 times>, 
				 __align = 549755813895}
					？

		不会的问题：
		如何获取 system 函数的返回值？
			The system() library function uses fork(2) to create a child process that exe‐cutes the shell command 
			specified in command using execl(3) as follows:
           		execl("/bin/sh", "sh", "-c", command, (char *) 0);

       		system() returns after the command has been completed.
       		During execution of the command, SIGCHLD  will  be  blocked,  and  SIGINT  and
      		SIGQUIT  will  be  ignored,  in the process that calls system() (these signals
       		will be handled according to their defaults inside the child process that exe‐
       		cutes command).

       		If  command is NULL, then system() returns a status indicating whether a shell
       		is available on the system

       	RETURN VALUE
	       The return value of system() is one of the following:

	       *  If command is NULL, then a nonzero value if a shell is available, or  0  if
	          no shell is available.

	       *  If  a  child  process  could  not  be  created,  or its status could not be
	          retrieved, the return value is -1.

	       *  If a shell could not be executed in the  child  process,  then  the  return
	          value  is as though the child shell terminated by calling _exit(2) with the
	          status 127.

	       *  If all system calls succeed, then the return value is the termination  sta‐
	          tus of the child shell used to execute command.  (The termination status of
	          a shell is the termination status of the last command it executes.)

	       In the last two cases, the return value is a "wait status" that can  be  exam‐
	       ined  using  the macros described in waitpid(2).  (i.e., WIFEXITED() WEXITSTA‐
	       TUS() and so on).

	       system() does not affect the wait status of any other children.

	       WEXITSTATUS(status)可以得到调用程序的返回值

	    envp[] 的数据如何更改？
			set 显示所有本地定义的Shell变量
			env 显示当前用户的环境变量
			export 设置新的环境变量

			使用export 修改exec()中的envp[] 变量；
			pwd006@Debain:~$ set | grep USERNAME
			USERNAME=waten
			pwd006@Debain:~$ export USERNAME="pwd006"
			pwd006@Debain:~$ set | grep USERNAME
			USERNAME=pwd006
			_=USERNAME
			pwd006@Debain:~$ 

			如何获取环境变量？

 ----------------------------------------------------------

 2015-6-23

 		1-忙等待，互斥锁，自旋锁；
 			对于互斥锁，如果资源已经被占用，资源申请者只能进入睡眠状态。
 			但是自旋锁不会引起调用者睡眠，如果自旋锁已经被别的执行单元保持，
 				调用者就一直循环在那里看是否该自旋锁的保持者已经释放了锁，"自旋"一词就是因此而得名。


-----------------------------------------------------------------
2015-6-29

		1-build_in 编译 gcc原子操作
			https://gcc.gnu.org/onlinedocs/gcc-4.1.1/gcc/Atomic-Builtins.html
			http://coolshell.cn/articles/8239.html