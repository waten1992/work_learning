#include "quote_service.h"


struct qsvr  *data_array ;
uint32_t ***index_array; //index array[Days][86] 

typedef struct qsvr  input_data ;

union key_bit_value
{
	struct end_key_bit
	{
		uint32_t  rank :4 ;
		uint32_t  item :6 ;
		uint32_t  day  :5 ;
		uint32_t  month:4 ;
		uint32_t  year :7 ; 
	}end_key_bit_area;
	uint32_t value ;
};


uint32_t hash_key[512] = {0};
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


unsigned int  Is_Leap_year(unsigned int year )
{
	unsigned int Leap = 0 ;
	if( ((year%4 == 0)&&(year%100 != 0)) ||(year%400==0))
		Leap = 1 ;
return Leap ;
}

uint32_t calculate_year_key( uint32_t date )
{
	unsigned int Leap_array[] = {0 ,1 ,1 ,1 ,2 ,2 ,2 ,2 ,3 ,3 ,3 ,3 ,4 ,4 ,4 ,4 ,5 ,5 ,5 ,5 ,6 ,6 ,6 ,6 ,7 ,7 ,7 ,7 ,8 ,8 ,8 ,8 ,9 ,9 ,9 ,9 ,10 ,10 ,10 ,10 };

	unsigned int min_month_flag[] ={0,0,0,1,1,2,2,2,3,3,4,4}; //NOT ZERO mean stand the total of min month from January,except February
	unsigned int day , month , year, Leap = 0 ,all_day ,year_day ,Leap_times ,tmp =1;

	day 	= 	date %100;
	month 	= 	(date%10000)/100;
	year 	=	(date/10000);
	Leap =  Is_Leap_year(year);

	if ((month -1) >= 2)
	{
		year_day  = (month-2)*31 -min_month_flag[month-2] + day  + 28 + Leap ; 		
		all_day   = year_day + (year - 2012)*365 +Leap_array[year-2012] - Start_day;
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

void map_key(uint32_t ***index_array ,input_data data_array[] , uint32_t len )
{
	uint32_t year=0 ,month=0 ,day=0,year_key = 0,item_key = 0 ,rank_key = 0 ;
	for(int i =0 ;i < len ;i++)
	{
		year_key =  calculate_year_key(data_array[i].date );
		item_key  = calculate_item_key(data_array[i].item );
	    item_key	= hash_key[item_key] + data_array[i].rank;		

		index_array[year_key][item_key]=(int *) ( data_array + i);
	}
		
}
void * find_history_quote(uint32_t ***index_array ,uint32_t time ,char *item  ,uint32_t rank)
{
	uint32_t tmp_item = 0  ,year_key = 0 ,item_key = 0 , rank_key = 0 ;
	year_key = calculate_year_key(time);
	tmp_item = calculate_item_key(item);
	item_key = hash_key[tmp_item] + rank ;
	
return index_array[year_key][item_key];
}

void
qsvr_find(uint32_t date , char *item , uint32_t rank , struct qsvr *ret_val )
{
	
	uint32_t tmp_item = 0  ,year_key = 0 ,item_key = 0 , rank_key = 0 ;
	year_key = calculate_year_key(date);
	tmp_item = calculate_item_key(item);
	item_key = hash_key[tmp_item] + rank ;
	
	struct qsvr * val ;
	val  =(struct qsvr *) index_array[year_key][item_key];
	printf("contract: %s , address : %s\n",val->contract,val->address);
	memcpy(ret_val,val,8);
	memcpy(ret_val,val,128);
}




void
split_str(char* src_buf, char delimiter, int* cnt, char* ele_ar[])
{
	 int  i = 0, array_num = 0 ;
     char *front , *cur ;
     front = cur = src_buf ;
     while('\0'  != src_buf[i] && '\n' != src_buf[i] )
     {
        if( delimiter  !=  *cur)
            cur++;
        else
        {
           *cur = '\0';
           cur++;
           ele_ar[array_num++] = front ;
           front = cur ;
        }
              i++;
    }
   if ('\n'  == *cur )
   	 *cur = '\0';
   ele_ar[array_num] = front ;
}
void
qsvr_destroy(uint32_t ***des_val)
{
	printf("arrived qsvr_destroy \n");
	for(int i = 0 ; i < Days ; i++)
		for(int j = 0 ; j < Second_hash_index ; j++)
			if(des_val[i][j] != NULL)
			{	
				//call function del linklist	
				free(des_val[i][j]);
			}

	for(int i = 0 ; i < Days ; i++)
		if(des_val[i] != NULL)
			free(des_val[i]);
 
	free(des_val);
	free(data_array);  
	printf("qsvr_destroy success \n"); 
}

struct qsvr*	qsvr_init(const char *path )
{
	struct qsvr *ret_init_val ;
   	ret_init_val = (struct qsvr *) malloc(sizeof(struct qsvr ));	
    memset(ret_init_val,0,sizeof(struct qsvr));
	
	int index = 0 ;
	unsigned long start, end;
	uint32_t input_data_len = sizeof(struct qsvr )*History_len;
	uint32_t malloc_sec_hash_len = Second_hash_index * sizeof(uint32_t *);
	
	data_array = (struct qsvr *) malloc(input_data_len);
	index_array 	= (uint32_t ***)malloc(sizeof(uint32_t *));
	for(int i = 0 ; i < Days  ; i++)
		index_array[i] 	= (uint32_t **)malloc(malloc_sec_hash_len);
	
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
		int inner = 0 ;
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
	data_array[index].date = atoi(tmp_array[0]);
	sprintf(data_array[index].item,"%s",tmp_array[1]);
	sprintf(data_array[index].contract,"%s",tmp_array[2]);
	data_array[index].rank = atoi(tmp_array[3]);
	sprintf(data_array[index].address,"%s",tmp_array[4]);
	index++;
	};

#ifdef PRINT
	for(int i = 0 ;i < Test_len  ;i++)
		printf("%d , %s , %s , %d ,%s\n",data_array[i].date , data_array[i].item, data_array[i].contract,data_array[i].rank , data_array[i].address);
#endif

	fclose(stream);
#if 1 //init middle  map key
	stream  = fopen("../uniq.txt","r+");
	if (stream == NULL)
	{
		printf("can't open uniq.txt \n,%s",strerror(errno));
		return NULL;
	}
	index = 0 ; //reuse  index 
	while(fgets(buf,128,stream))
	{
		uint32_t middle_key ;
    	char tmp_buf[5];
		int i ;
		for(i = 0 ;buf[i] != '\n' ; i++)
		tmp_buf[i] = buf[i];
		tmp_buf[i] = '\0';
	
    	middle_key	= calculate_item_key(tmp_buf);	
		hash_key[middle_key]= index+1 ;
		index++;
	}
	fclose(stream);
	map_key(index_array,data_array , History_len);
	printf("map success \n");
#endif 
return ret_init_val; 
}

int main()
{
	const char *path = "../input_data.txt";
	struct qsvr *test_val ;
    test_val =	qsvr_init(path);

	printf("test find \n");
	uint32_t test_time = 20140825 , test_rank = 4;
	char *test_item ="shag";

	qsvr_find( test_time , test_item ,test_rank , &(*test_val) );
	if(test_val != NULL)
	{
		printf("contract: %s , address : %s\n",test_val->contract,test_val->address);	
	}
	else
	{
		printf("can't find \n");
		return -1 ;
	}

	//qsvr_destroy(index_array);
//while(1);

return 0 ;

}
