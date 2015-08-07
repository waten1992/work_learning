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
u32_int *index_array[1<<26]; //index array 
u32_int hash_key[1<<20] = {0};
u32_int calculate_middle_key(char *array )
{
		u32_int middle_key = 0 ;
	
		u32_int item_tmp = 0 ;
		for(int index = 0 ;array[index] != '\0'; index++)
		{
			item_tmp = 100*item_tmp + (tolower(array[index])-Start_value) ;	
		}	
//		printf("come form calculate_middle_key item_tmp: %d \n",item_tmp);
		u32_int part1,part2 ,part3 ,part4 ;
		part1 = item_tmp %100 ;
		part2 = (item_tmp % 10000)/100;
		part3 = (item_tmp %1000000)/10000;
		part4 = item_tmp /1000000; 
//		printf("%d , %d , %d ,%d \n",part1,part2,part3,part4);
	
		middle_key |= (part1);
		middle_key |= (part2 <<5);
		middle_key |= (part3 <<10);
		middle_key |= (part4 <<15);
//		printf("come from calculate middle_key: %d \n",middle_key);
return middle_key ;

}
u32_int calculate_end_key(u32_int time , u32_int item , u32_int rank )
{

	u32_int year=0 ,month=0 ,day=0,middle_key = 0, end_key = 0 ;
		day	 = time % 100 ;
		month 	 = (time %10000)/100  ;
		year 	 = (time %1000000)/10000  ;
	//	printf("%d,%d,%d \n ",year,month,day);
#if 0		
		end_key 	|=	rank ;
		end_key 	|=	(item << 4);
		end_key 	|=	(day << 10);
		end_key 	|= 	(month <<15);
		end_key 	|=	(year <<19);
//	printf("end_key : %d\n",end_key);
#endif 
	union key_bit_value end_key_value ;
	memset(&end_key_value,0,sizeof(u32_int));
	end_key_value.end_key_bit_area.rank = rank ;
	end_key_value.end_key_bit_area.item = item ; 
	end_key_value.end_key_bit_area.day = day;
	end_key_value.end_key_bit_area.month = month;
	end_key_value.end_key_bit_area.year = year;
		
end_key = end_key_value.value;
return end_key ;
}


void map_key(input_data data_array[] , u32_int len )
{
//	printf("arrive map_key \n");
	u32_int year=0 ,month=0 ,day=0,middle_key = 0, end_key = 0,item = 0,rank =0 ;
	for(int i =0 ;i < len ;i++)
	{
		middle_key = calculate_middle_key(data_array[i].item);
	    item	= hash_key[middle_key];
	
		rank = data_array[i].rank;
		/*connect time , item , rank  key*/
		end_key =  calculate_end_key(data_array[i].date ,item ,rank);
//		index_array[end_key] =(int *)&data_array[i];		
		index_array[end_key] =(int *) ( data_array + i);
	}
	
	
}
void * find_history_quote(u32_int time ,char *item  ,u32_int rank)
{
	u32_int tmp_item = 0 , end_key = 0 ;
	tmp_item = calculate_middle_key(item);
	tmp_item = hash_key[tmp_item];
	end_key =  calculate_end_key(time,tmp_item,rank);
//return &(*index_array[end_key]);
return index_array[end_key];
}

// 123,456,789
// 1,2,3,4,5,6,7,8

void
split_str(char* src_buf, char delimiter, int* cnt, char* ele_ar[]);

int main()
{
u32_int input_data_len = sizeof(input_data)*History_len;
input_data data_array[History_len] ;
int index = 0 ;
unsigned long start, end;

FILE *stream ;
char buf[128]={0} , tmp_array[Type_size][Tmp_array_len] ;

stream = fopen("input_data.txt","r+");
if (stream == NULL)
{
	printf("can't open input_data.txt \n,%s",strerror(errno));
	return -1 ;
}
while(index < Test_len)
{
	fgets(buf,128,stream);
	char *tmp = buf ;
	int outer = 0;
	while(*tmp != '\n' && *tmp != '\0' )
	{
		int inner = 0 ;
		while(*tmp != ' ' && *tmp !='\n')
		{
			tmp_array[outer][inner] = *tmp ; 
			tmp++;
			inner++;	
		}
	outer++;
	tmp++;	
	}
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
stream  = fopen("uniq.txt","r+");
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
	
    middle_key	= calculate_middle_key(tmp_buf);	
	hash_key[middle_key]= index+1 ;
//	printf("hash_key : %d \n",hash_key[middle_key]);
	index++;
}
fclose(stream);
map_key( data_array , History_len);

#endif 

#if 0
/* test find   */
printf("test find \n");
u32_int test_time = 20140825 , test_rank = 4;
char *test_item ="shag";
input_data *test_point;

HP_TIMING_NOW(start);

test_point =(input_data *) malloc(sizeof(input_data));
test_point = (input_data *) find_history_quote(test_time ,test_item,test_rank);
HP_TIMING_NOW(end);

printf("contract: %s , address : %s\n",test_point->contract,test_point->address);

printf("\n the cost cycles are %lf ns\n", (end - start)/3.6);

#endif

#if 1
 
printf("test find \n");
u32_int test_time = 20120601 , test_rank = 1;
char *test_item ="dla";
u32_int tmp_end_key = 0 , tmp_item = 0 ;

tmp_item = calculate_middle_key(test_item);
tmp_item = hash_key[tmp_item];

tmp_end_key =  calculate_end_key(test_time , tmp_item ,test_rank);
printf("%d\n",tmp_end_key);
#endif 
//printf ("1 <<26 ------%d \n",1<<26);
return 0 ;

}
