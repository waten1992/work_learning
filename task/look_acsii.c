#include<stdio.h>

int main(int argc , char *argv[])
{
	char *p ;
	for(int i = 0 ;  argv[1][i] != '\0' ;i++)
		printf("%d \t",argv[1][i]-96);
return 0 ;
}
