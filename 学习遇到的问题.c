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

 		3-据说在信号处理程序中调用printf() 函数不安全
 			解释：像printf()和malloc()之类的标准库函数，它们会使用全局的数据（比如malloc()需要使用进程的堆数据结构）是不可重入的，即使加锁也无法解决，加锁可以使得库函数Tread-safe，但是无法解决可重入。

 		4-do_fork() 执行流程？

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
 
  			2- 在杀死子进程才能变成僵尸进程？在代码如下：

  				#include "a.h"
			  2 
			  3 
			  4 int  main(int argc , char *argv[])
			  5 {
			  6         pid_t pid ;
			  7         printf("alarm application starting \n");
			  8         pid = fork();
			  9 
			 10         switch(pid)
			 11         {
			 12                 case -1 :
			 13                         perror("fork failed ");
			 14                         exit(1);
			 15                 case 0 :
			 16                         sleep(10);
			 17                         exit(0);
			 18         }
			 19         printf("waiting for alarm to go off \n");
			 20 
			 21         pause();
			 22 exit(0) ;
			 23 }

			 	pwd006@Debain:~/test/process$ gcc -o defunct defunct_test.c 
				pwd006@Debain:~/test/process$ ./defunct
				alarm application starting 
				waiting for alarm to go off 
				^Z
				[2]+  Stopped                 ./defunct
				pwd006@Debain:~/test/process$ ps -ef | grep defunct
				pwd006   11203  4333  0 15:33 pts/0    00:00:00 ./defunct2
				pwd006   11204 11203  0 15:33 pts/0    00:00:00 [defunct2] <defunct>
				pwd006   11627  4333  0 15:45 pts/0    00:00:00 ./defunct
				pwd006   11628 11627  0 15:45 pts/0    00:00:00 ./defunct
				pwd006   11631  4333  0 15:45 pts/0    00:00:00 grep defunct
				pwd006@Debain:~/test/process$ jobs
				[1]-  Stopped                 ./defunct2
				[2]+  Stopped                 ./defunct
				pwd006@Debain:~/test/process$ top

				top - 15:46:10 up  7:45,  3 users,  load average: 0.13, 0.08, 0.05
				Tasks: 177 total,   1 running, 172 sleeping,   3 stopped,   1 zombie
				%Cpu(s):  0.2 us,  0.3 sy,  0.0 ni, 99.3 id,  0.1 wa,  0.0 hi,  0.0 si,  0.0 st
				KiB Mem:   5088472 total,  1670672 used,  3417800 free,   103160 buffers
				KiB Swap:        0 total,        0 used,        0 free.   634032 cached Mem

				  PID USER      PR  NI    VIRT    RES    SHR S  %CPU %MEM     TIME+ COMMAND           
				 4035 pwd006    20   0 2029632 451268  69960 S   2.0  8.9  13:40.38 gnome-shell       
				 3572 root      20   0  361760  90188  33492 S   0.7  1.8   4:11.39 Xorg              
				   10 root      rt   0       0      0      0 S   0.3  0.0   0:00.29 watchdog/0        
				 3125 root      20   0  170028   8124   7180 S   0.3  0.2   0:46.80 vmtoolsd          
				 3906 pwd006    20   0  368568   7880   6208 S   0.3  0.2   0:34.72 ibus-daemon       
				 3970 pwd006    20   0 1039756  36712  26504 S   0.3  0.7   0:02.78 gnome-settings-   
				11336 root      20   0       0      0      0 S   0.3  0.0   0:00.41 kworker/0:2       
				11633 pwd006    20   0   26368   2976   2456 R   0.3  0.1   0:00.03 top               
				    1 root      20   0  176124   5016   3088 S   0.0  0.1   0:02.44 systemd           
				    2 root      20   0       0      0      0 S   0.0  0.0   0:00.04 kthreadd          
				    3 root      20   0       0      0      0 S   0.0  0.0   0:01.06 ksoftirqd/0       
				    5 root       0 -20       0      0      0 S   0.0  0.0   0:00.00 kworker/0:0H      
				    7 root      20   0       0      0      0 S   0.0  0.0   0:04.24 rcu_sched         
				    8 root      20   0       0      0      0 S   0.0  0.0   0:00.00 rcu_bh            
				    9 root      rt   0       0      0      0 S   0.0  0.0   0:00.33 migration/0       
				   11 root      rt   0       0      0      0 S   0.0  0.0   0:00.33 watchdog/1        
				   12 root      rt   0       0      0      0 S   0.0  0.0   0:00.07 migration/1       
				   13 root      20   0       0      0      0 S   0.0  0.0   0:01.34 ksoftirqd/1       
				   15 root       0 -20       0      0      0 S   0.0  0.0   0:00.00 kworker/1:0H      
				   16 root      rt   0       0      0      0 S   0.0  0.0   0:00.25 watchdog/2        
				   17 root      rt   0       0      0      0 S   0.0  0.0   0:00.07 migration/2       
				   18 root      20   0       0      0      0 S   0.0  0.0   0:00.48 ksoftirqd/2       
				   20 root       0 -20       0      0      0 S   0.0  0.0   0:00.00 kworker/2:0H      
				   21 root      rt   0       0      0      0 S   0.0  0.0   0:00.26 watchdog/3        
				   22 root      rt   0       0      0      0 S   0.0  0.0   0:00.10 migration/3       
				   23 root      20   0       0      0      0 S   0.0  0.0   0:00.80 ksoftirqd/3       
				   24 root      20   0       0      0      0 S   0.0  0.0   0:04.83 kworker/3:0       
				   25 root       0 -20       0      0      0 S   0.0  0.0   0:00.00 kworker/3:0H      
				   26 root       0 -20       0      0      0 S   0.0  0.0   0:00.00 khelper           
				pwd006@Debain:~/test/process$ ps 
				  PID TTY          TIME CMD
				 4333 pts/0    00:00:02 bash
				11203 pts/0    00:00:00 defunct2
				11204 pts/0    00:00:00 defunct2 <defunct>
				11627 pts/0    00:00:00 defunct
				11628 pts/0    00:00:00 defunct
				11635 pts/0    00:00:00 ps
				pwd006@Debain:~/test/process$ kill -9 11628
				pwd006@Debain:~/test/process$ ps 
				  PID TTY          TIME CMD
				 4333 pts/0    00:00:02 bash
				11203 pts/0    00:00:00 defunct2
				11204 pts/0    00:00:00 defunct2 <defunct>
				11627 pts/0    00:00:00 defunct
				11628 pts/0    00:00:00 defunct <defunct>
				11637 pts/0    00:00:00 ps
				pwd006@Debain:~/test/process$ kill -9 11628
				pwd006@Debain:~/test/process$ ps 
				  PID TTY          TIME CMD
				 4333 pts/0    00:00:02 bash
				11203 pts/0    00:00:00 defunct2
				11204 pts/0    00:00:00 defunct2 <defunct>
				11627 pts/0    00:00:00 defunct
				11628 pts/0    00:00:00 defunct <defunct>
				11640 pts/0    00:00:00 ps
				pwd006@Debain:~/test/process$ kill -9 11627
				pwd006@Debain:~/test/process$ ps 
				  PID TTY          TIME CMD
				 4333 pts/0    00:00:02 bash
				11203 pts/0    00:00:00 defunct2
				11204 pts/0    00:00:00 defunct2 <defunct>
				11642 pts/0    00:00:00 ps
				[2]+  Killed                  ./defunct
				pwd006@Debain:~/test/process$ 



 
 