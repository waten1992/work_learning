#include <string.h>
#include <stdio.h>

int main()
{
	for(int i = 0  ;i < 150  ; i++) 
	{
		printf("%d : %s \n",i,strerror(i));
	}
return 0 ;
}
