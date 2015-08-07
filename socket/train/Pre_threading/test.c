#include<stdio.h>
#include<stdlib.h>
#include <string.h>

	
union key {
	struct {		
		unsigned int a: 4;
		unsigned int b: 6;
		unsigned int c: 5;
		unsigned int d: 9;
		unsigned int e: 2;
		}bit;	
	unsigned int vaule ;
};

int main(void)
{
union key test ;
	memset(&test,0,8);
	test.bit.a = 1;
	test.bit.b = 1;
	test.bit.c = 1;
	test.bit.d = 1;
	test.bit.e = 1;


return 0;
}
