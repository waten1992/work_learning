#include <stdio.h>

typedef void (*type)(int a, int b);




static void 
test(int a, int b )
{
	int c = a + b;
	printf("c = %d\n",c);	
}

static void 
test1(int a , int b)
{
	printf("c1=%d\n",a+b);
}

type t_ar[2] ={test,test1};

int 
main()
{
	t_ar[0](1,2);
	t_ar[1](3,4);	
return 0;
}
