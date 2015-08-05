#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define LEN 8
#define History_len	425212
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
int *data_array ;
data_array = malloc(sizeof(input_data)*History_len);
memset(data_array,0,sizeof(input_data)*History_len);
int openfd;
char buf[128];
memset(buf , 0 , 128);
openfd = open("input_data.txt",O_RDONLY,0);
read(openfd,buf,128);
printf("%s \n",buf);


printf("hello world  \n");
return 0 ;
}
