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
			1-编写一个shell ，杀掉说有的僵尸进程；在shell 里面 执行bash命令后输出的参数是什么形式的 字符串还是？

 
 