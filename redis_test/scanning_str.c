#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

#define content_num 35
int main()
{
	int fd ;
	int comma_num = 0 , record = 0, index = 0; 
	char ch ;
	char *format_str[content_num];
	char start[32];
	for(int i = 0 ;i < 32 ;i++)
		memset(start,0,32);
	for(int i = 0 ; i<content_num  ;i++)
	{
		format_str[i] = (char *)malloc(32);
	}	

	for(int i = 0 ; i<content_num  ;i++)
		memset(format_str[i],0,32);
	fd = open("output.txt",O_RDONLY,0);
	while(read(fd,&ch,1) != 0)
	{	
			if(ch == ':' )
			{
					sprintf( format_str[record++], "%s", start );
					index=0 ;
				memset(start,0,32);
			}
			else if(ch == ' ')
				;	
			else 
			{
					start[index++] = ch ;
			}
	}
					sprintf( format_str[record], "%s", start );
for(int i = 0 ;i < content_num  ;i++)
{
	printf("---%s\n",format_str[i]);
}

return 0 ;
}
