#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define LEN 8
#define History_len	425212
#define Type_size	5
#define Tmp_array_len 	64
#define Test_len 	16
typedef struct
{
	unsigned int	date ;
	char 			item[LEN] ;
	char 			contract[LEN];
	unsigned int  	rank;
	char 			address[2<<LEN];
}input_data;

int main()
{
size_t input_data_len = sizeof(input_data)*History_len;
input_data data_array[History_len] ;
int index = 0 ;


FILE *stream ;
char buf[128]={0} , tmp_array[Type_size][Tmp_array_len] ;

stream = fopen("input_data.txt","r+");
while(index < Test_len)
{
	fgets(buf,128,stream);
	char *tmp = buf ;
	int outer = 0;
	while(*tmp != '\n' && *tmp != '\0' )
	{
		int inner = 0 ;
#if 1 
		while(*tmp != ' ' && *tmp !='\n')
		{
			tmp_array[outer][inner] = *tmp ; 
//			printf("%c ",*tmp);		
			tmp++;
			inner++;	
		}
#endif 	
	outer++;
		tmp++;	
	}
	data_array[index].date = atoi(tmp_array[0]);

	sprintf(data_array[index].item,"%s",tmp_array[1]);
	sprintf(data_array[index].contract,"%s",tmp_array[2]);
	data_array[index].rank = atoi(tmp_array[3]);
	sprintf(data_array[index].address,"%s",tmp_array[4]);
	
	printf("%s \n",buf);
	index++;
};
for(int i = 0 ;i < Test_len  ;i++)
	printf("%d , %s , %s , %d ,%s\n",data_array[i].date , data_array[i].item, data_array[i].contract,data_array[i].rank , data_array[i].address);
fclose(stream);
return 0 ;
}
