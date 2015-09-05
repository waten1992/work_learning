#include "quote_service.h"

struct quote_map
{
	uint32_t 	***index_array ; //index_array[Days][86] 
	uint32_t 	*hash		   ;
	struct qsvr *origin_array  ;
	qsvr_data	qsvr_struct    ;
};
 
uint32_t calculate_item_key(char *array )				;
uint32_t  Is_Leap_year(uint32_t year )					;
uint32_t calculate_year_key( uint32_t date )			;
struct quote_map* qsvr_init(const char *path)			;
void map_key(struct quote_map *map_val , uint32_t len )	;
void qsvr_find(struct quote_map* qm, u32_int date , char *item , u32_int rank , struct qsvr *ret_val ) ;

uint32_t calculate_item_key(char *array )
{
     uint32_t seed = 131; // 31 131 1313 13131 131313 etc..
     uint32_t hash = 0 ;
      
     while (*array)
     {
          hash = hash * seed + (*array++);
     }
      
     return  (hash & 0x1ff); 
}

uint32_t  Is_Leap_year(uint32_t year )
{
     uint32_t Leap = 0 ;
     if( ((year%4 == 0)&&(year%100 != 0)) ||(year%400==0))
          Leap = 1 ;

return Leap ;
}

uint32_t calculate_year_key( uint32_t date )
{
	uint32_t  Leap_array[] = {0 ,1 ,1 ,1 ,2 ,2 ,2 ,2 ,3 ,3 ,3 ,3 ,4 ,4 ,4 ,4 ,5   ,5 ,5 ,5 ,6 ,6 ,6 ,6 ,7 ,7 ,7 ,7 ,8 ,8 ,8 ,8 ,9 ,9 ,9 ,9 ,10 ,10 ,10 ,10 };
  
    uint32_t  min_month_flag[] ={0,0,0,1,1,2,2,2,3,3,4,4}; //NOT ZERO mean stand   the total of min month from January,except February
    uint32_t  day ,month ,year ,Leap = 0 ,all_day ,year_day ;
  
    day     =   date %100;
    month   =   (date%10000)/100;
    year    =   (date/10000);
    Leap =  Is_Leap_year(year);
  
    if ((month -1) >= 2)
    {
    	year_day  = (month-2)*31 -min_month_flag[month-2] + day  + 28 + Leap ;       
        all_day   = year_day + (year - 2012)*365 +Leap_array[year-2012] - Start_day  ;
    }
    else if (month == 2)
    {
       year_day = 31 + day ;
       all_day  = year_day + (year -2012)*365 +Leap_array[year-2012] - Start_day;
    }
    else
    {
       all_day = day + (year - 2012)*365 +Leap_array[year-2012] - Start_day;
    }
return all_day;
}
void map_key(struct quote_map *map_val , uint32_t len )
{   
	 uint32_t year=0 ,month=0 ,day=0,year_key = 0,item_key = 0 ,rank_key = 0 ;
     for(int i =0 ;i < len ;i++)
     {
        year_key =  calculate_year_key(map_val->origin_array[i].date );
        item_key  = calculate_item_key(map_val->origin_array[i].item );
        item_key    = map_val->hash[item_key] + map_val->origin_array[i].rank +Item_hash_index;
        
		if(map_val->index_array[year_key][item_key] == NULL)
     		map_val->index_array[year_key][item_key]=(uint32_t *) (map_val->origin_array + i);
		else
		{	
			struct qsvr *tmp =(struct qsvr *)(map_val->index_array[year_key][item_key]);
			while(tmp->next != NULL) //use the linklist of tail insert function 
				tmp = tmp->next ;	
			tmp->next =(struct qsvr *)(map_val->origin_array+i);

#if 1	 //test the confilt BestAndDeepQuote , MarchPriceQty ,RealTimePrice ,TenEntrust 
	
			tmp = tmp->next ;
			uint32_t test_hash = calculate_item_key(tmp->item);
			
			if( (tmp->date ==20150804) && (tmp->rank == 12) && (map_val->hash[test_hash] == 7) )
				printf("%d ,%s---->%s,rank= %d ,%s\n",tmp->date,tmp->contract,tmp->quote_record,tmp->rank,tmp->item);
#endif 

		}
     }
   
}


struct quote_map*
qsvr_init(const char *path)
{
	uint32_t hash_key[512] = {0};
	struct quote_map* init_val;
	init_val = (struct quote_map *)malloc(sizeof(struct quote_map));
	memset(init_val,0,sizeof(struct quote_map));
	
	int index = 0 ; 
    uint32_t input_data_len = sizeof(struct qsvr )*History_len;
    uint32_t malloc_sec_hash_len = Second_hash_index * sizeof(uint32_t *);
	
	struct qsvr * origin_array ;
	origin_array = (struct qsvr *) malloc(input_data_len); 
	
	uint32_t ***index_array ;
	index_array     = (uint32_t ***)malloc(sizeof(uint32_t *)*Days);
    
	for(int i = 0 ; i < Days  ; i++) 
        index_array[i]  = (uint32_t **)malloc(malloc_sec_hash_len);
	
	for(int i = 0 ; i < Days  ; i++) 
		for(int j = 0 ; j < Second_hash_index ; j++)
			index_array[i][j] = NULL;

	init_val->hash 			= hash_key 		;
	init_val->origin_array 	= origin_array  ;
	init_val->index_array 	= index_array   ;



	FILE *stream ;
  	char buf[128]={0} ,*tmp_array[Type_size] ;
	stream = fopen(path,"r+");
 	if (stream == NULL)
  	{
      printf("can't open input_data.txt \n,%s",strerror(errno));
      return NULL ;
  	}
	while(fgets(buf,128,stream))
  	{
      char *cur = buf ,*front =buf ;
      int outer = 0;
      while(*cur != '\n' )
      {   
        if( ' ' == *cur )
        {
              *cur = '\0';
              tmp_array[outer] = front ;
              cur++;
              front = cur ;
              outer++;
          }
          else
              cur++;
      }
      tmp_array[outer] = front;
      origin_array[index].date = atoi(tmp_array[0]);
      sprintf(origin_array[index].item,"%s",tmp_array[1]);
      sprintf(origin_array[index].contract,"%s",tmp_array[2]);
      origin_array[index].rank = atoi(tmp_array[3]);
      sprintf(origin_array[index].quote_record,"%s",tmp_array[4]);
      sprintf(origin_array[index].address,"%s",tmp_array[5]);
	  origin_array[index].next = NULL ;
      index++;
   	};
	fclose(stream);
//map item to dictionary
	stream  = fopen("../uniq.txt","r+"); //reuse stream 
    if (stream == NULL)
    {
         printf("can't open uniq.txt \n,%s",strerror(errno));
         return NULL;
    }
	index = 0 ; //reuse  index 
    while(fgets(buf,128,stream)) //reuse buf
    {
          uint32_t middle_key ;
          char tmp_buf[5];
          int i ;
          for(i = 0 ;buf[i] != '\n' ; i++)
          tmp_buf[i] = buf[i];
          tmp_buf[i] = '\0';
  
          middle_key  = calculate_item_key(tmp_buf);
          hash_key[middle_key]= index ;
          index++;
     }
     fclose(stream);
     map_key(init_val , History_len);
     printf("map success \n");
return init_val ;
}

void
qsvr_find(struct quote_map* qm, u32_int date , char *item , u32_int rank , struct qsvr *ret_val )
{
	 uint32_t tmp_item = 0  ,year_key = 0 ,item_key = 0  ; 
     year_key = calculate_year_key(date);
     tmp_item = calculate_item_key(item);
     item_key = qm->hash[tmp_item] + rank +Item_hash_index ;
      
     struct qsvr * val ;
     val  =(struct qsvr *) qm->index_array[year_key][item_key];
     memcpy(ret_val,val,sizeof(struct qsvr ));
}

void
qsvr_destroy(struct quote_map* qm)
{
	free(qm->origin_array);

	for(int i = 0 ;i < Days  ; i++)  //free second index hash
			free(qm->index_array[i][0]);

	for(int i = 0 ; i <Days ;i++) // free first index hash 
		free(qm->index_array[i]);
	
	free(qm->index_array); //free head of the index  hash

	free(qm);	
	
#if 0 // test  if free(qm->origin_array) , continue will segmentation fault
	printf("qm->origin[0] 0x%d \n",qm->origin_array[0]);
#endif

#if 0 //test if free(qm->index_array[i][0]) ,and  free(qm->index_array[i]) , continue will segmentation fault
	printf("qm->index_array 0x%x \n",qm->index_array);
	printf("qm->index_array[0] 0x%x \n",qm->index_array[0]);
	printf("qm->index_array[0][0] 0x%x \n",qm->index_array[0][0]);
#endif	

	printf("qsvr_destroy is clean \n");
}

int main()
{
	const char *path = "../input_data.txt";
    unsigned long start, end;
	struct quote_map *test_map ;
	struct qsvr *test_val ;
	test_val = (struct qsvr *)malloc(sizeof(struct qsvr));
	memset(test_val,0,sizeof(struct qsvr));

	printf("start ! \n");
	test_map =  qsvr_init(path);

// construct test case 
	uint32_t test_time = 20150804 , test_rank = 1;
    char *test_item ="dlj";
	printf("test find \n");
	
	int ii = calculate_item_key(test_item);

	HP_TIMING_NOW(start);
	qsvr_find(test_map,test_time,test_item,test_rank,test_val);
	HP_TIMING_NOW(end);

	if(test_val != NULL)
      {
          printf("date :%d,item :%s,contract: %s , address : %s\n",test_val->date,test_val->item,test_val->contract,test_val->address  );
      }
      else
      {
          printf("can't find \n");
          return -1 ;
      }
	printf("\n the cost cycles are %lf ns\n", (end - start)/3.6);
	free(test_val);
	qsvr_destroy(test_map);	
	while(1);
return 0 ;
}
