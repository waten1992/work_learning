 #include "header.h"
 #include "utils.h"
 #include "comm.h"
 #include "coder.h"
 #include "../bridge.h"
/*
 * input from command line
 * int create_rq-receiver(char * src , int port ) 
 *	 1-src: bind IP address 
 *	 2-port : bind socket port number
 * Input example: ./main 192.168.1.55  9999
 *  
 *
 * */

#define EXCHANGE_NUM 1 

int main(int argc , char *agrv[])
{
	size_t exchange_num_tmp = EXCHANGE_NUM ;
	size_t loop_times = exchange_num_tmp<<1 ;
	if (argc < 3 || argc&1 != 0)
		set_error("error to pass param number\n");
	for(int i = 1 ; i <= loop_times  ; i++)
	{
		int res = create_rq_receiver(agrv[i],agrv[i+1]); //create bind server port
		if(res == -1)
			set_error("fail to  bind server ip and port \n ");
	}	

	while(true) //loop push to redis_queue
	{
		publish_rq();	
	}
return 0 ;
}

