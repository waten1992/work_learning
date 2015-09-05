#include <stdio.h>
#include <malloc.h>

int main()
{
	int i = 9;
	int ***p = (int ***)malloc(sizeof(int *));
	printf("p = %x \n",p);	
	for (int i = 0 ; i < 4 ; i++ ) {
		p[i]  = (int **)malloc(sizeof(int *));
		printf("p[%d] = %x \n",i,p[i]);
	}
	
	p[0][0] = &i ;
	printf("%d \n",*p[0][0]);
	
	printf("0x%x \n",p[0]);
	free(p[0]);

return 0;
}
