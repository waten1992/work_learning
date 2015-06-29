#生产者和消费者模型
	一个生产者线程和多个消费者；
	主体控制结构体：
	typedef struct
    {   
        void *      buf ;    //
        size_t      n;		//缓存池总的槽位 slots + items  = n 
        size_t      front;  //队列前部
        size_t      rear;   //队列的尾部  ((rear - front)+n) % n = items 可用的数量
        size_t      size; //the  struct of slots size  
        sem_t   mutex;  //  互斥量
        sem_t   slots; //available slots for producter
        sem_t   items; //available items for customer
    }buf_pool;


	pthread_create(&master_tid,NULL,master_thread_function,mtp);
		----生产者线程

	pthread_create(&tid[i],NULL,thread_function,sp); //缓存池的指针
		---消费者线程

	调用者通过结构体指针mtp传递参数给生产者
	typedef struct
    {   
        void * param ; //Array * 指向传递的数组
        buf_pool *master_sp; //sp * 指向缓存池指针
        size_t num ; //array length 数组的长度
    }master_thread_param;

    /*------------ 测试用例-----------------  */
    			  数量	  
    生产者P：		1		
    消费者C：		6		
    总的槽位：		8		

    传入是int 的数组；
    生产4个items，4个消费者; 
    		----结果：正常终止；
    生产4个items，6个消费者; 
    		----结果：消费者消费掉4个items后在等待；
    生产4个items，2个消费者;
    		----结果：消费两个items正常终止，还有2个items 可以用；

    传入double的数组：
    
    生产4个items，4个消费者; 
    		----结果：正常终止；
    		p->size=8 , i=0 ,i*sp->size = 0 
			address of ---> 22e70a0 ,sp->buf = 22e7010 
			sp->size=8 , i=1 ,i*sp->size = 8 
			address of ---> 22e70a8 ,sp->buf = 22e7010 
			sp->size=8 , i=2 ,i*sp->size = 10 
			address of ---> 22e70b0 ,sp->buf = 22e7010 
			sp->size=8 , i=3 ,i*sp->size = 18 
			address of ---> 22e70b8 ,sp->buf = 22e7010 
			form master thread num=4 
			sp->num:8
			sp->front:0 
			sp->rear:4 
			child thread , it is successfull 
			----test of value address--->22e70a0  
			child thread , it is successfull 
			----test of value address--->22e70a8  
			the result -->11.000000 
			the result -->10.000000 
			child thread , it is successfull 
			----test of value address--->22e70b0  
			the result -->12.000000 
			child thread , it is successfull 
			----test of value address--->22e70b8  
			the result -->13.000000 

    生产4个items，6个消费者; 
    		----结果：消费者消费掉4个items后在等待；
    		sp->size=8 , i=0 ,i*sp->size = 0 
			address of ---> 23570a0 ,sp->buf = 2357010 
			sp->size=8 , i=1 ,i*sp->size = 8 
			address of ---> 23570a8 ,sp->buf = 2357010 
			sp->size=8 , i=2 ,i*sp->size = 10 
			address of ---> 23570b0 ,sp->buf = 2357010 
			sp->size=8 , i=3 ,i*sp->size = 18 
			address of ---> 23570b8 ,sp->buf = 2357010 
			form master thread num=4 
			sp->num:8
			sp->front:0 
			sp->rear:4 
			child thread , it is successfull 
			----test of value address--->23570a0  
			the result -->10.000000 
			child thread , it is successfull 
			----test of value address--->23570a8  
			the result -->11.000000 
			child thread , it is successfull 
			----test of value address--->23570b0  
			the result -->12.000000 
			child thread , it is successfull 
			----test of value address--->23570b8  
			the result -->13.000000 
			child thread , it is successfull 
			child thread , it is successfull 
			^C



    生产4个items，2个消费者;
    		----结果：消费两个items正常终止，还有2个items 可以用；
    		sp->size=8 , i=0 ,i*sp->size = 0 
			address of ---> 1c200a0 ,sp->buf = 1c20010 
			sp->size=8 , i=1 ,i*sp->size = 8 
			address of ---> 1c200a8 ,sp->buf = 1c20010 
			sp->size=8 , i=2 ,i*sp->size = 10 
			address of ---> 1c200b0 ,sp->buf = 1c20010 
			sp->size=8 , i=3 ,i*sp->size = 18 
			address of ---> 1c200b8 ,sp->buf = 1c20010 
			form master thread num=4 
			sp->num:8
			sp->front:0 
			sp->rear:4 
			child thread , it is successfull 
			----test of value address--->1c200a0  
			the result -->10.000000 
			child thread , it is successfull 
			----test of value address--->1c200a8  
			the result -->11.000000 







