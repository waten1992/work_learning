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
#include "quote_schedule.h"

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

ret_date_t * 
calculate_the_month(uint32_t days , uint32_t year)
{
    uint32_t  sum = 0 , i = 0;
    uint32_t tmp[12];
    uint32_t month_array[] = {1,0,1,0,1,0,1,1,0,1,0,1};
    ret_date_t *ret_date = (ret_date_t *)malloc(sizeof(ret_date_t));
    for (i = 0;i < 12; i++) {
        if (month_array[i]) {
            sum += 31; 
        } else {
            sum += 30;  
        }
        tmp[i] = sum ;
        if (i ==1) {
            if (Is_Leap_year(year)) {
                sum -= 1;
                tmp[i] = sum;
            } else {
                sum -= 2;
                tmp[i] = sum;   
            }   
        }   
    }

    for (i = 0; i < 12 ; i++) {
        if ((i != 11)&& (days > tmp[i]) && (days < tmp[i+1])) {
            ret_date->month = i + 2;
            break;
        }
        if (11 == i) {
            ret_date->month = 12 ;   
        }   
    }   
    ret_date->day = days - tmp[i];
        
return ret_date ;
}

uint32_t
rev_calculate_date( uint32_t date )
{
	uint32_t  Leap_array[] = {0 ,1 ,1 ,1 ,2 ,2 ,2 ,2 ,3 ,3 ,3 ,3 ,4 ,4 ,4 ,4 ,5 ,5 ,5 ,5 ,6 ,6 ,6 ,6 ,7 ,7 ,7 ,7 ,8 ,8 ,8 ,8 ,9 ,9 ,9 ,9 ,10 ,10 ,10 ,10 };
    uint32_t  year ,tmp_year ,year_day ,change_date;
  	struct ret_date *ret ;

	tmp_year =  (date/365);
	year = tmp_year + START_YEAR;
    year_day = (date - (tmp_year)*365 - Leap_array[tmp_year] + START_DAY);
	printf("tmp_year %d ,year_day :%d \n",tmp_year,year_day);
	ret = calculate_the_month(year_day ,year );
	printf("year = %d ,month =%d , day = %d\n",year,ret->month,ret->day);	
	change_date = year*10000 + ret->month*100 + ret->day;
return change_date;
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
        all_day = year_day + (year - START_YEAR)*365 +Leap_array[year-START_YEAR] - START_DAY  ;
    }else if (month == 2) {
       year_day = 31 + day ;
       all_day = year_day + (year -START_YEAR)*365 +Leap_array[year-START_YEAR] - START_DAY;
    }else {
       all_day = day + (year - START_YEAR)*365 +Leap_array[year-START_YEAR] - START_DAY;
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
    uint32_t input_data_len = sizeof(struct qsvr )*HISTORY_LEN;
    uint32_t malloc_sec_hash_len = ITEM_HASH_INDEX * sizeof(uint32_t *);
	uint32_t malloc_thi_hash_len = RANK_HASH_INDEX * sizeof(uint32_t *);

	struct qsvr * origin_array;
	origin_array = (struct qsvr *) malloc(input_data_len); 
	if (NULL == origin_array) {
		 printf("origin_array allocate is error , errno is : %s \n",strerror(errno));
	}
	
	uint32_t ****index_array;
	index_array     = (uint32_t ****)malloc(sizeof(uint32_t *) *DAYS); /* DAYS Index hash slots */
	if (NULL == index_array) {
		 printf("index_array allocate is error , errno is : %s \n",strerror(errno));
	}
    
	for (int i = 0 ; i < DAYS  ; i++) { 
        index_array[i]  = (uint32_t ***)malloc(malloc_sec_hash_len); /* Items Index hash slots */
		if (NULL == index_array[i]) {
			printf("index_array[%d] allocate is error , errno is : %s \n",i,strerror(errno));
		}
	}
	
	for (int i = 0; i < DAYS; i++) { 
		for (int j = 0; j < ITEM_HASH_INDEX; j++) {
	        index_array[i][j]  = (uint32_t **)malloc(malloc_thi_hash_len); /* Rank Index hash slots */
			if (NULL == index_array[i][j]) {
		 		printf("index_array[%d][%d] allocate is error , errno is : %s \n",i,j,strerror(errno));
			}		
		}
	}

	for (int i = 0; i < DAYS; i++) {
		for (int j = 0; j < ITEM_HASH_INDEX; j++) {
			for (int k = 0; k < RANK_HASH_INDEX; k++) {
	        	index_array[i][j][k]  = NULL;  
			}
		}
	}

	init_val->hash 			= hash_key 		;
	init_val->origin_array 	= origin_array  ;
	init_val->index_array 	= index_array   ;

	FILE *stream , *stream_item;
  	char buf[1024]={0} ,*tmp_array[TYPE_SIZE];
	stream = fopen(origin_data_path,"r");

 	if (stream == NULL) {
     printf("can't open input_data.txt \n,%s",strerror(errno));
     return NULL ;
  	}

	while(fgets(buf,1024,stream)) {
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

      tmp_array[outer] = front;

      origin_array[index].date = atoi(tmp_array[3]);
      snprintf(origin_array[index].item,ITEM_LEN,"%s",tmp_array[4]);
      snprintf(origin_array[index].contract,CONTRACT_LEN,"%s",tmp_array[5]);
      origin_array[index].rank = atoi(tmp_array[6]);
      snprintf(origin_array[index].quote_record,RECORD_LEN,"%s",tmp_array[8]);
      snprintf(origin_array[index].address,ADDRESS_LEN,"%s",tmp_array[10]);
	
	  origin_array[index].next = NULL;
      index++;
   	};

	fclose(stream);

	/* map item to dictionary */
	stream_item  = fopen(item_path,"r"); 
    if (stream_item == NULL) {
         printf("can't open uniq.txt \n,%s",strerror(errno));
         return NULL;
    }

	index = 0 ; 
    while(fgets(buf,128,stream_item)) {
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

     fclose(stream_item);
     map_key(init_val , HISTORY_LEN);

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
	/* free third index hash : rank_key */
	for(int i = 0; i < DAYS; i++) {
		for(int j = 0; j < ITEM_HASH_INDEX; j++) {
			free(qm->index_array[i][j][0]);
		}
	}
	/* free second index hash : item_key */
	for(int i = 0; i <DAYS; i++) { 	
		for(int j = 0; j < ITEM_HASH_INDEX; j++) {
			free(qm->index_array[i][j]);
		}
	}
	/* free first index hash : item_key */
	for(int i = 0 ; i <DAYS ;i++) {
		free(qm->index_array[i]);
	}

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

