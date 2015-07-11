#include <rqb/bridge.h>
#include <pthread.h>
#include <semaphore.h>
#include <hiredis.h>
#include <malloc.h>
#define 	pool_num   			4
#define 	input_qoute_num 	4
#define 	format_array_len 	2
#define 	format_len 			112
#define 	char_num 			182
#define 	first_loop 			5
#define 	second_loop 		12
#define 	third_loop			12
#define 	fourth_loop			4
   
redisReply *reply; // global variables
redisContext *c;   // global variables
static int record ;
typedef struct
{
    void *  	buf ;
    size_t    	n;
    size_t 		front;
    size_t		rear;
	size_t		size; //the  struct of slots size  
    sem_t   mutex;  // 
    sem_t   slots; //available slots for producter
    sem_t   items; //available items for customer
}buf_pool;

buf_pool *sp ; // global variables
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

buf_pool *  buf_init(int num , size_t size)
{
	
    buf_pool *sp ; //declare *sp 
	sp = (buf_pool *)malloc(sizeof(buf_pool));
    sp->buf =calloc(num,size);
    sp->n = num;
	sp->size = size ;
    sp->front = sp->rear = 0 ;
    sem_init(&sp->mutex,0,1);
    sem_init(&sp->slots,0,num);
    sem_init(&sp->items,0,0);
    return sp;
}

int on_recv_quote(int quote_type, void *data, size_t data_size)
{
	p(&sp->slots);

	printf("get quote %d, size=%ld\n", quote_type, data_size);
	struct rq_raw_quote_t *quote = (struct rq_raw_quote_t *)data;
	printf("ep=%ld\n", quote->epoch_us);
	printf("trading quote=%s\n",quote->l1_depth_data.TradingDay);
	printf("LastPrice =%.2f,\n", quote->l1_depth_data.LastPrice);
	printf("record----------> %d  \n",record++);

#if 0  //test of format string 	
	char *tmp_array[input_qoute_num];
	for(int i = 0 ;i < input_qoute_num ; i++)
		tmp_array[i] =(char *)malloc(sizeof(char)*10);
	
	for(int i = 0 ;i < input_qoute_num ; i++)
		memset(tmp_array[i],0,sizeof(char)*10);

	
	reply = (redisReply *)redisCommand(c,"PING");
	printf("PING: %s\n", reply->str);
	freeReplyObject(reply);
	snprintf(tmp_array[0],sizeof(char)*10,"%s",quote->l1_depth_data.TradingDay);
	snprintf(tmp_array[1],sizeof(char)*10,"%d",quote->epoch_us);
	snprintf(tmp_array[2],sizeof(char)*10,"%f",quote->l1_depth_data.LastPrice);
	snprintf(tmp_array[3],sizeof(char)*10,"%f",quote->l1_depth_data.LowestPrice);

 //  	if(quote_type)
	for(int i = 0 ;i < input_qoute_num ; i++)
	{
		 reply =(redisReply *) redisCommand(c,"LPUSH mylist element-%s", tmp_array[i]);
    	freeReplyObject(reply);
	}
#endif 

#if 1 //test quote data 
	const	char *content[] =
    {
             "src","hwguan_test",
             "type","trading_msg",
             "data","column",
            "contract","item","exchange","last_price","volume","amount","price_change","open_interest","open_interest_change","open","low","high",
             "data",
             "STATE","OK",
            "type","trading_msg"
    };
	const	char *str ="{\"\":\"\",\"\":\"\",\"\":{\"\":[\"\",\"\",\"\",\"\",\"\",\"\",\"\",\"\",\"\",\"\",\"\",\"\"],\"\":[\"\",\"\",\"\",\"\",\"\",\"\",\"\",\"\",\"\",\"\",\"\",\"\"],\"\":\"\",\"\":\"\"}}";
	char *quote_array , *quote_rear ;	
	char *format_array[format_len]; //store format char 
	quote_array = (char *)malloc(sizeof(struct rq_raw_quote_t)+format_len);
	size_t offset = 0 ,content_index = 0, content_tmp_len = 0, format_tmp_index =0;
	quote_rear = quote_array ;
	size_t content_len = sizeof(content)/sizeof(content[0]);
	printf("const_Len %d , sp = %d\n",content_len,strlen(content[1]));	
//	printf("---%d \n",sizeof(struct rq_raw_quote_t));
	for(int i = 0 ; i <format_len ;i++) //apply 2 char
		format_array[i]=(char *)malloc(2);	

	for(int i = 0 ; i< format_len ; i++)
		memset(format_array[0],0,2);

	for(int i = 0 ;i < format_len  ;i++) //format char to string 
	{
		snprintf(format_array[i],format_array_len,"%c",str[i]);
	//	printf("tmp_index = %d $$$str[%d] =%c$$$$%s \n" ,i,i,str[i],format_array[i]); 
		
	}
/*start  */
	/*2 char  p1*/
	for(int i = 0 ;i < 2  ; i++)
	{
		snprintf(quote_rear,format_array_len,"%s",format_array[format_tmp_index++]);
		quote_rear += format_array_len-1;
	}
/*part1 first loop */
	for(int i = 0 ;i < first_loop ;i++)
	{
    	/*content loop 0*/
		content_tmp_len = strlen(content[content_index]);
		snprintf(quote_rear,content_tmp_len+1,"%s",content[content_index++]);	
		quote_rear += content_tmp_len ;

		/*3 char  loop 1*/
		for(int i = 0 ;i < 3  ; i++)
		{
			snprintf(quote_rear,format_array_len,"%s",format_array[format_tmp_index++]);
			quote_rear += format_array_len-1;
		}
	}
/* middle  */	
	/*1 char p3*/
	snprintf(quote_rear,format_array_len,"%s",format_array[format_tmp_index++]);
	quote_rear += format_array_len-1;
    
	/*content tmp 0*/
	content_tmp_len = strlen(content[content_index]);
	snprintf(quote_rear,content_tmp_len+1,"%s",content[content_index++]);	
	quote_rear += content_tmp_len ;

	/*4 char  tmp */
	for(int i = 0 ;i < 4  ; i++)
	{
		snprintf(quote_rear,format_array_len,"%s",format_array[format_tmp_index++]);
		quote_rear += format_array_len-1;
	}
/*part 2 second loop  add the quote data title */	

	/*first loop */
	for(int i = 0 ;i < second_loop ;i++)
	{
    	/*content loop 1*/
		content_tmp_len = strlen(content[content_index]);
		snprintf(quote_rear,content_tmp_len+1,"%s",content[content_index++]);	
		quote_rear += content_tmp_len ;

		/*3 char loop 2*/
		for(int i = 0 ;i < 3  ; i++)
		{
			snprintf(quote_rear,format_array_len,"%s",format_array[format_tmp_index++]);
			quote_rear += format_array_len-1;
		}
   }
/*middle part2 and part3 */
	/*1 char */
	snprintf(quote_rear,format_array_len,"%s",format_array[format_tmp_index++]);
	quote_rear += format_array_len-1;
	
	/*content tmp 1*/
	content_tmp_len = strlen(content[content_index]);
	snprintf(quote_rear,content_tmp_len+1,"%s",content[content_index++]);	
	quote_rear += content_tmp_len ;
	
	/*4 char tmp */
	
	for(int i = 0 ;i < 4  ; i++)
	{
		snprintf(quote_rear,format_array_len,"%s",format_array[format_tmp_index++]);
		quote_rear += format_array_len-1;
	}
/*part 3 third loop add real quote data */
	/*add  contract */
	printf("TradingDay size--%d\n",sizeof(quote->l1_depth_data.InstrumentID));
	printf("TradingDay len--%d\n",strlen(quote->l1_depth_data.InstrumentID));
	offset = snprintf(quote_rear,strlen(quote->l1_depth_data.InstrumentID)+1,"%s",quote->l1_depth_data.InstrumentID);
	printf("offset--%d\n",offset);
	quote_rear += offset ; 
	
	/*3-1: 3 char */
	for(int i = 0 ;i < 3  ; i++)
	{
		snprintf(quote_rear,format_array_len,"%s",format_array[format_tmp_index++]);
		quote_rear += format_array_len-1;
	}

	/*add item  */	
	offset = snprintf(quote_rear,strlen("item_cu")+1,"%s","item_cu");
	printf("offset--%d\n",offset);
	quote_rear += offset ; 
	
	/*3-2: 3 char */
	for(int i = 0 ;i < 3  ; i++)
	{
		snprintf(quote_rear,format_array_len,"%s",format_array[format_tmp_index++]);
		quote_rear += format_array_len-1;
	}

	/*add exchange */
	offset = snprintf(quote_rear,strlen("exchange")+1,"%s","exchange");
	//printf("offset--%d\n",offset);
	quote_rear += offset ; 
	
	/*3-3: 3 char  */
	for(int i = 0 ;i < 3  ; i++)
	{
		snprintf(quote_rear,format_array_len,"%s",format_array[format_tmp_index++]);
		quote_rear += format_array_len-1;
	}
	/*add last_price*/
	
	snprintf(quote_rear,sizeof(double),"%lf",quote->l1_depth_data.LastPrice);
	//printf("offset--%d\n",offset);
	quote_rear += sizeof(double)-1 ; 

	/*3-4: 3 char  */
	for(int i = 0 ;i < 3  ; i++)
	{
		snprintf(quote_rear,format_array_len,"%s",format_array[format_tmp_index++]);
		quote_rear += format_array_len-1;
	}
	/*add volume : the type is int */
	int int_len =1 ,tmp_int = quote->l1_depth_data.Volume;
	while(tmp_int >= 10 ) //count the int value length
	{
		tmp_int /= 10 ;
		int_len++; 
	}
	snprintf(quote_rear,int_len+1,"%d",quote->l1_depth_data.Volume);
	quote_rear += int_len ; 

	/*3-5: 3 char  */
	for(int i = 0 ;i < 3  ; i++)
	{
		snprintf(quote_rear,format_array_len,"%s",format_array[format_tmp_index++]);
		quote_rear += format_array_len-1;
	}
	/*add amount */
	offset = snprintf(quote_rear,strlen("amount")+1,"%s","amount");
	quote_rear += offset ; 
	
	/*3-6: 3 char  */
	for(int i = 0 ;i < 3  ; i++)
	{
		snprintf(quote_rear,format_array_len,"%s",format_array[format_tmp_index++]);
		quote_rear += format_array_len-1;
	}
	/*add price_change*/
	offset = snprintf(quote_rear,strlen("price_change")+1,"%s","price_change");
	quote_rear += offset ; 
	
	/*3-7: 3 char  */
	for(int i = 0 ;i < 3  ; i++)
	{
		snprintf(quote_rear,format_array_len,"%s",format_array[format_tmp_index++]);
		quote_rear += format_array_len-1;
	}
	
	/*add  OpenInterest*/
	snprintf(quote_rear,sizeof(double),"%lf",quote->l1_depth_data.OpenInterest);
	//printf("offset--%d\n",offset);
	quote_rear += sizeof(double)-1 ; 

	/*3-8: 3 char  */
	for(int i = 0 ;i < 3  ; i++)
	{
		snprintf(quote_rear,format_array_len,"%s",format_array[format_tmp_index++]);
		quote_rear += format_array_len-1;
	}

	/*add open_interest_change*/
	snprintf(quote_rear,sizeof(double),"%lf",quote->l1_depth_data.PreOpenInterest);
	//printf("offset--%d\n",offset);
	quote_rear += sizeof(double)-1 ; 

	/*3-9: 3 char  */
	for(int i = 0 ;i < 3  ; i++)
	{
		snprintf(quote_rear,format_array_len,"%s",format_array[format_tmp_index++]);
		quote_rear += format_array_len-1;
	}

	/*add OpenPrice*/
	snprintf(quote_rear,sizeof(double),"%lf",quote->l1_depth_data.OpenPrice);
	//printf("offset--%d\n",offset);
	quote_rear += sizeof(double)-1 ; 

	/*3-10: 3 char  */
	for(int i = 0 ;i < 3  ; i++)
	{
		snprintf(quote_rear,format_array_len,"%s",format_array[format_tmp_index++]);
		quote_rear += format_array_len-1;
	}

	/*add LowestPrice*/
	snprintf(quote_rear,sizeof(double),"%lf",quote->l1_depth_data.LowestPrice);
	//printf("offset--%d\n",offset);
	quote_rear += sizeof(double)-1 ; 

	/*3-11: 3 char  */
	for(int i = 0 ;i < 3  ; i++)
	{
		snprintf(quote_rear,format_array_len,"%s",format_array[format_tmp_index++]);
		quote_rear += format_array_len-1;
	}

	/*add HighestPrice*/
	snprintf(quote_rear,sizeof(double),"%lf",quote->l1_depth_data.HighestPrice);
	//printf("offset--%d\n",offset);
	quote_rear += sizeof(double)-1 ; 

	/*3-12: 3 char  */
	for(int i = 0 ;i < 3  ; i++)
	{
		snprintf(quote_rear,format_array_len,"%s",format_array[format_tmp_index++]);
		quote_rear += format_array_len-1;
	}

/*middle of part3 and part4   */
	/*1 char */
	snprintf(quote_rear,format_array_len,"%s",format_array[format_tmp_index++]);
	quote_rear += format_array_len-1;

/*part 4 add status */
	/*fourth loop*/
	for(int i = 0 ;i < fourth_loop ;i++)
	{
    	/*content loop 4*/
		content_tmp_len = strlen(content[content_index]);
		snprintf(quote_rear,content_tmp_len+1,"%s",content[content_index++]);	
		quote_rear += content_tmp_len ;

		/*3 char loop 4*/
		for(int i = 0 ;i < 3  ; i++)
		{
			snprintf(quote_rear,format_array_len,"%s",format_array[format_tmp_index++]);
			quote_rear += format_array_len-1;
		}
	}
//	printf("LastPrice size--%d\n",sizeof(quote->l1_depth_data.LastPrice));
//  snprintf(quote_rear,sizeof(double),"%lf",quote->l1_depth_data.LastPrice);
	printf("quote_array--> %s\n ",quote_array );
#endif


#if 1 //test  
	
		 reply =(redisReply *) redisCommand(c,"LPUSH mylist %s",quote_array);
    	freeReplyObject(reply);
#endif




	v(&sp->items);	
	


return 0;
/*
	printf("ep=%ld ", quote->epoch_us);
	printf("trading quote=%s, ",quote->l1_depth_data.TradingDay);
	printf("LastPrice =%.2f,", quote->l1_depth_data.LastPrice);
	printf("pre set price=%.2f,",quote->l1_depth_data.PreSettlementPrice);
	printf("pre close price=%.2f,",	quote->l1_depth_data.PreClosePrice);
	printf("pre open interset=%.2f,",quote->l1_depth_data.PreOpenInterest);
	printf("open price=%.2f \n", quote->l1_depth_data.OpenPrice);
	
	printf("high low price=%.2f-%.2f",quote->l1_depth_data.HighestPrice,
		quote->l1_depth_data.LowestPrice);
	printf("vol = %d, turnover=%.2f, open interest=%.2f,"
		"close price=%.2f, Set price=%.2f,"
		"up lmt price=%.2f, l lmt price=%.2f"
		, quote->l1_depth_data.Volume,
		quote->l1_depth_data.Turnover,
		quote->l1_depth_data.OpenInterest,
		quote->l1_depth_data.ClosePrice,
		quote->l1_depth_data.SettlementPrice,
		quote->l1_depth_data.UpperLimitPrice,
		quote->l1_depth_data.LowerLimitPrice);
	return 0;
*/
}

void *thread_function(void *arg)
{ 
	buf_pool * tmp ;
	tmp = (buf_pool *)arg;
	while(1)
	{ 	
	p(&tmp->items);
	printf("come from pthread \n");

  	v(&tmp->slots);
	}	
}

int main(int argc , char **argv)
{
	int ret;
	sem_t sem_num;
	char bind_addr[]="eth0";
	char bind_addr_ip[]="192.168.52.136";
	ret= create_rq_receiver(bind_addr,10000);
	if(ret<0) {
		printf("error ot create rq receiver\n");
		return -1;
	}
	

    sp = buf_init(pool_num,sizeof(rq_raw_quote_t));
    unsigned int j;
    const char *hostname = (argc > 1) ? argv[1] : "127.0.0.1";
    int port = (argc > 2) ? atoi(argv[2]) : 6379;

    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
    c = redisConnectWithTimeout(hostname, port, timeout);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }
	
	printf("start to pull quote\n");
	pthread_t tid;
	ret = pthread_create(&tid,NULL,thread_function,sp);
	if(ret != 0)	
	{
		printf("error to create thread \n");
		return -1 ;
	}
	recv_rq_poll(on_recv_quote);
	printf("test come from server \n");
	return 0;
}
