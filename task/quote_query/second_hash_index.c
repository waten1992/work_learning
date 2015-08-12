#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<malloc.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define LEN 8
#define History_len	425212
#define Type_size	5
#define Tmp_array_len 	64
#define Test_len 	History_len
#define Start_value	96
//Start_value = ( (int)'a'-1 )
#define Mask	0xff
#define Item_num	43

//#define PRINT 		1
#define days 	7320 //7320 = 20*366   equal 20 year *  366 days
#define Start_day 	153
# define HP_TIMING_NOW(Var) \
 ({ unsigned long long _hi, _lo; \
  asm volatile ("rdtsc" : "=a" (_lo), "=d" (_hi)); \
  (Var) = _hi << 32 | _lo; })

typedef unsigned int  u32_int ;
typedef struct
{
	u32_int 		date ;
	char 			item[LEN] ;
	char 			contract[LEN];
	u32_int 	 	rank;
	char 			address[2<<LEN];
}input_data;

/**/
union key_bit_value
{
	struct end_key_bit
	{
		u32_int  rank :4 ;
		u32_int  item :6 ;
		u32_int  day  :5 ;
		u32_int  month:4 ;
		u32_int  year :7 ; 
	}end_key_bit_area;
	u32_int value ;
};

void map_key(input_data data_array[] , u32_int len );
u32_int *index_array[days][86]; //index array 

u32_int hash_key[512] = {0};
u32_int calculate_item_key(char *array )
{
    u32_int seed = 131; // 31 131 1313 13131 131313 etc..
    u32_int hash = 0 ;

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

u32_int calculate_year_key( u32_int date )
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

void map_key(input_data data_array[] , u32_int len )
{
	u32_int year=0 ,month=0 ,day=0,year_key = 0,item_key = 0 ,rank_key = 0 ;
	for(int i =0 ;i < len ;i++)
	{
		year_key =  calculate_year_key(data_array[i].date );
		item_key  = calculate_item_key(data_array[i].item );
	    item_key	= hash_key[item_key] + data_array[i].rank;		

		index_array[year_key][item_key]=(int *) ( data_array + i);
	}
		
}
void * find_history_quote(u32_int time ,char *item  ,u32_int rank)
{
	u32_int tmp_item = 0  ,year_key = 0 ,item_key = 0 , rank_key = 0 ;
	year_key = calculate_year_key(time);
	tmp_item = calculate_item_key(item);
	item_key = hash_key[tmp_item] + rank ;
	
return index_array[year_key][item_key];
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
int main()
{
u32_int input_data_len = sizeof(input_data)*History_len;
input_data data_array[History_len] ;
int index = 0 ;
unsigned long start, end;

FILE *stream ;
char buf[128]={0} ,*tmp_array[Type_size] ;

stream = fopen("../input_data.txt","r+");
if (stream == NULL)
{
	printf("can't open input_data.txt \n,%s",strerror(errno));
	return -1 ;
}
while(index < Test_len)
{
	fgets(buf,128,stream);
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
	return -1 ;
}
index = 0 ; //reuse  index 
while(index < Item_num)
{
	u32_int middle_key ;
	fgets(buf,128,stream); //reuse buf
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
map_key( data_array , History_len);

#endif 

#if 1
/* test find   */
printf("test find \n");
u32_int test_time = 20140825 , test_rank = 4;
char *test_item ="shag";
input_data *test_point = NULL;

HP_TIMING_NOW(start);


test_point = (input_data *) find_history_quote(test_time ,test_item,test_rank);
HP_TIMING_NOW(end);
if(test_point != NULL)
	printf("contract: %s , address : %s\n",test_point->contract,test_point->address);
else
{
	printf("can't find \n");
	return -1 ;
}
printf("\n the cost cycles are %lf ns\n", (end - start)/3.6);

#endif

#if 0
 
printf("test find \n");
u32_int test_time = 20120601 , test_rank = 1;
char *test_item ="dla";
u32_int tmp_end_key = 0 , tmp_item = 0 ;

tmp_item = calculate_middle_key(test_item);
tmp_item = hash_key[tmp_item];

tmp_end_key =  calculate_end_key(test_time , tmp_item ,test_rank);
printf("%d\n",tmp_end_key);
#endif 

while(1);

return 0 ;

}
