#include <stdio.h>
#include <string.h>
int 
main()
{
	int a[] = {11,2,7,5,6,4,12,10};
	int b[24] ;
	
	int i = 0; 
	for (i = 0; i < 24 ; i++ ) {
		b[i] = -1;	
	}
	for (i = 0; i < sizeof(a)/sizeof(a[0]); i++) {	
		b[a[i]] = i;
	}
	for (i = 0; i < 24 ; i++ ) {
		printf("%d,",b[i]);
	}
	printf("\n");
return 0;
}
