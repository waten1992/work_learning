#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	int fd ,len ,i;
	int comma_num = 0 , total = 0; 
	char ch ;
	char test_array[] = {'"','{','[',':',']',',','}','"','\\'};
	len = sizeof(test_array)/sizeof(test_array[0]);
	
	fd = open("input.txt",O_RDONLY,0);
	while(read(fd,&ch,1) != 0)
	{	
		for(i = 0 ; i < len ; i++ )
		{
			if(ch == test_array[i] )
			{
				write(STDOUT_FILENO,&ch,1);
				if(ch == ',')
					comma_num++;
					total++;
					break;
			}
		}
	}
printf("\n comma_num: %d, total number : %d  \n",comma_num,total);
return 0 ;
}
