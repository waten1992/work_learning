#include<stdio.h>
#include<malloc.h>

int main()
{
	int ***p ;
	int ii = 8 ,jj = 9 , kk = 10;
	int *tmp ;
	p =(int ***) malloc(sizeof(int *)); 

	for(int i = 0 ; i < 2  ; i++ )
		p[i] = (int **)malloc(sizeof(int *));

	p[0][0] = &ii ;
	p[0][1] = &jj ;
	p[0][2] = &kk ;
    tmp = p[0][0] ;
	printf("hello world ,%d ,%d,%d\n",*p[0][0],*p[0][1],*p[0][2]);
	
	for(int i = 0 ; i < 2  ; i++ )
		free(p[i]);
	*tmp = 11;
	printf("%d ,0x%x \n",*tmp ,tmp);	
return 0;
}
