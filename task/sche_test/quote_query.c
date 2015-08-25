/*
 ** File name    : quote_service.h 
 **
 ** Author       : He Wen Guan
 ** 
 ** Description  : Input (date , item ,rank) query contract content   
 **
 ** Copyright (c) 2007-2015 MY Capital Inc.
 ***/

#include "quote_service.h"
#include "schedule.h"

uint32_t 
calculate_item_key(char *array )
{
     uint32_t hash = 0,seed = 131; // 31 131 1313 13131 131313 etc..
     while (*array) {     
	    hash = hash * seed + (*array++);
     }  
return  (hash & 0x1ff); 
}

uint32_t 
Is_Leap_year(uint32_t year )
{
    uint32_t Leap = 0 ;
	if(((year%4 == 0)&&(year%100 != 0)) ||(year%400==0)) {    
		Leap = 1 ;
	}
return Leap ;
}

uint32_t 
calculate_year_key( uint32_t date )
{
	uint32_t  Leap_array[] = {0 ,1 ,1 ,1 ,2 ,2 ,2 ,2 ,3 ,3 ,3 ,3 ,4 ,4 ,4 ,4 ,5   ,5 ,5 ,5 ,6 ,6 ,6 ,6 ,7 ,7 ,7 ,7 ,8 ,8 ,8 ,8 ,9 ,9 ,9 ,9 ,10 ,10 ,10 ,10 };
    uint32_t  min_month_flag[] ={0,0,0,1,1,2,2,2,3,3,4,4}; //NOT ZERO mean stand   the total of min month from January,except February
    uint32_t  day ,month ,year ,Leap = 0 ,all_day ,year_day ;
  
    day     =   date %100		;
    month   =   (date%10000)/100;
    year    =   (date/10000)	;
    Leap =  Is_Leap_year(year)	;
  
    if ((month -1) >= 2) {
    	year_day = (month-2)*31 -min_month_flag[month-2] + day  + 28 + Leap ;       
        all_day = year_day + (year - 2012)*365 +Leap_array[year-2012] - Start_day  ;
    }else if (month == 2) {
       year_day = 31 + day ;
       all_day = year_day + (year -2012)*365 +Leap_array[year-2012] - Start_day;
    }else {
       all_day = day + (year - 2012)*365 +Leap_array[year-2012] - Start_day;
    }
return all_day;
}

void 
map_key(struct quote_map *map_val , uint32_t len )
{   
	 uint32_t year_key = 0,item_key = 0 ,rank_key = 0 ;
     for(int i =0 ;i < len ;i++) {

        year_key = calculate_year_key(map_val->origin_array[i].date );
        item_key = calculate_item_key(map_val->origin_array[i].item );
        item_key = map_val->hash[item_key];
		rank_key = map_val->origin_array[i].rank;
     	
		if (map_val->index_array[year_key][item_key][rank_key] == NULL) { 
			map_val->index_array[year_key][item_key][rank_key]=(uint32_t *) (map_val->origin_array + i);
		}else {
			struct qsvr *tmp =(struct qsvr *)(map_val->index_array[year_key][item_key][rank_key]);
			while(tmp->next != NULL) { 
				tmp = tmp->next ;	/*use the linklist of tail insert function   */
			}
			tmp->next =(struct qsvr *)(map_val->origin_array+i);

#if 0	 	/*test the confilt BestAndDeepQuote , MarchPriceQty ,RealTimePrice ,TenEntrust */ 
			tmp = tmp->next										;
			uint32_t test_hash = calculate_item_key(tmp->item)	;
			
			if( (tmp->date ==20150804) && (tmp->rank == 12) && (map_val->hash[test_hash] == 8)) {
				printf("%d ,%s---->%s,rank= %d ,%s\n",tmp->date,tmp->contract,tmp->quote_record,tmp->rank,tmp->item);
			}
#endif 
		}
     }
   
}


struct quote_map*
qsvr_init(const char *origin_data_path ,const char *item_path)
{
	uint32_t *hash_key;
	struct quote_map* init_val;
	init_val = (struct quote_map *)malloc(sizeof(struct quote_map));
	if (NULL == init_val) {
		 printf("init_val allocate is error , errno is : %s \n",strerror(errno));
	}
	memset(init_val,0,sizeof(struct quote_map));
	
	hash_key = (uint32_t *)malloc(512 *sizeof(uint32_t));	
	memset(hash_key,0,512);

	int index = 0; 
    uint32_t input_data_len = sizeof(struct qsvr )*History_len;
    uint32_t malloc_sec_hash_len = Item_hash_index * sizeof(uint32_t *);
	uint32_t malloc_thi_hash_len = Rank_hash_index * sizeof(uint32_t *);

	struct qsvr * origin_array;
	origin_array = (struct qsvr *) malloc(input_data_len); 
	if (NULL == origin_array) {
		 printf("origin_array allocate is error , errno is : %s \n",strerror(errno));
	}
	
	uint32_t ****index_array;
	index_array     = (uint32_t ****)malloc(sizeof(uint32_t *) *Days); /* Days Index hash slots */
	if (NULL == index_array) {
		 printf("index_array allocate is error , errno is : %s \n",strerror(errno));
	}
    
	for (int i = 0 ; i < Days  ; i++) { 
        index_array[i]  = (uint32_t ***)malloc(malloc_sec_hash_len); /* Items Index hash slots */
		if (NULL == index_array[i]) {
			printf("index_array[%d] allocate is error , errno is : %s \n",i,strerror(errno));
		}
	}
	
	for (int i = 0; i < Days; i++) { 
		for (int j = 0; j < Item_hash_index; j++) {
	        index_array[i][j]  = (uint32_t **)malloc(malloc_thi_hash_len); /* Rank Index hash slots */
			if (NULL == index_array[i][j]) {
		 		printf("index_array[%d][%d] allocate is error , errno is : %s \n",i,j,strerror(errno));
			}		
		}
	}

	for (int i = 0; i < Days; i++) {
		for (int j = 0; j < Item_hash_index; j++) {
			for (int k = 0; k < Rank_hash_index; k++) {
	        	index_array[i][j][k]  = NULL;  
			}
		}
	}

	init_val->hash 			= hash_key 		;
	init_val->origin_array 	= origin_array  ;
	init_val->index_array 	= index_array   ;

	FILE *stream ;
  	char buf[128]={0} ,*tmp_array[Type_size];
	stream = fopen(origin_data_path,"r");

 	if (stream == NULL) {
     printf("can't open input_data.txt \n,%s",strerror(errno));
     return NULL ;
  	}

	while(fgets(buf,128,stream)) {
      char *cur = buf ,*front =buf ;
      int outer = 0;

      while (*cur != '\n' ) {   		
		if ( '|' == *cur ) {		
			*cur = '\0';
            tmp_array[outer] = front ;
            cur++;
            front = cur ;
            outer++;
		}else {
        	cur++;
		}
      }

      tmp_array[outer] = front										;

      origin_array[index].date = atoi(tmp_array[0])					;
      sprintf(origin_array[index].item,"%s",tmp_array[1])			;
      sprintf(origin_array[index].contract,"%s",tmp_array[2])		;
      origin_array[index].rank = atoi(tmp_array[3])					;
      sprintf(origin_array[index].quote_record,"%s",tmp_array[4])	;
      sprintf(origin_array[index].address,"%s",tmp_array[5])		;
	
	  origin_array[index].next = NULL 								;
      index++														;
   	};

	fclose(stream);

	/* map item to dictionary */
	stream  = fopen(item_path,"r"); 
    if (stream == NULL) {
         printf("can't open uniq.txt \n,%s",strerror(errno));
         return NULL;
    }

	index = 0 ; 
    while(fgets(buf,128,stream)) {
    	uint32_t middle_key 	;
        char tmp_buf[5]			;
        int i 					;

        for(i = 0 ;buf[i] != '\n' ; i++) {
			tmp_buf[i] = buf[i];
		}
		tmp_buf[i] = '\0';
  
        middle_key  = calculate_item_key(tmp_buf);
        hash_key[middle_key]= index;
        index++;
     }

     fclose(stream)									;
     map_key(init_val , History_len)				;

return init_val ;
}

void
qsvr_find(struct quote_map* qm, uint32_t date , char *item , uint32_t rank , struct qsvr *ret_val )
{
	uint32_t tmp_item = 0  ,year_key = 0 ,item_key = 0 , rank_key = 0 ; 
	
	year_key = calculate_year_key(date)	;
    tmp_item = calculate_item_key(item)	;
    item_key = qm->hash[tmp_item]	 	;
	rank_key = rank 					;
      
    struct qsvr * val 					;
 	if (NULL == qm->index_array[year_key][item_key][rank_key]) {
		;
	} else {
    	val  =(struct qsvr *) qm->index_array[year_key][item_key][rank_key];
   		memcpy(ret_val,val,sizeof(struct qsvr ));
	}
}

void
qsvr_destroy(struct quote_map* qm)
{
	free(qm->origin_array);
	for(int i = 0 ;i < Days  ; i++)  /* free third index hash : rank_key */
		for(int j = 0 ; j < Item_hash_index ; j++)
			free(qm->index_array[i][j][0]);

	for(int i = 0 ; i <Days ;i++) 	/* free second index hash : item_key */
		for(int j = 0 ; j < Item_hash_index ; j++)
			free(qm->index_array[i][j]);
	
	for(int i = 0 ; i <Days ;i++) /* free first index hash : item_key */
		free(qm->index_array[i]);

	free(qm->index_array); 		/* free head of the index  hash */
	free(qm->hash);				/* free hash dic */
	free(qm); 					/* free  the wrapper  of struct  quote_map *  */	
	
	printf("qsvr_destroy is clean \n");
}

void
quote_find_use_date_key(struct task_sched * ts,struct day_schedule *input )
{
	struct quote_map *qm ;
	qm = ts->query_index;
	uint32_t tmp_item = 0  ,year_key = 0 ,item_key = 0 , rank_key = 0 ; 
	year_key = input->date_key;	
    tmp_item = calculate_item_key(input->item);
    item_key = qm->hash[tmp_item];
	rank_key = input->rank;
      
    struct qsvr * val;
	if (NULL == qm->index_array[year_key][item_key][rank_key]) {
		; /*do nothing , or give response*/	
	}else { 
    	val  =(struct qsvr *) qm->index_array[year_key][item_key][rank_key]	;
		memcpy(input->contract,val->contract,CONTRACT_LEN);
	}
}

