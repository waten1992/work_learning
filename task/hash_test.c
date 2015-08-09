#include<stdio.h>
#include<string.h>
#include <stdlib.h>
# define HP_TIMING_NOW(Var) \
 ({ unsigned long long _hi, _lo; \
  asm volatile ("rdtsc" : "=a" (_lo), "=d" (_hi)); \
  (Var) = _hi << 32 | _lo; })

//#define Hash 1 //if Hash equal 1  SDBMHash , equal 2 BKDRHash , equal 3 RSHash


unsigned int SDBMHash(char *str)
{
    unsigned int hash = 0;

    while (*str)
    {
        // equivalent to: hash = 65599*hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }
        
    return (hash & 0x1FF);
}
unsigned int RSHash(char *str)
{
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;

    while (*str)
    {
        hash = hash * a + (*str++);
        a *= b;
    }

    return (hash & 0x1FF);
}

unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    while (*str)
    {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x1ff);
}


int main(int argc , char *argv[])
{
	unsigned  long start, end;
	HP_TIMING_NOW(start);
	FILE *stream ;
	stream = fopen("uniq.txt","r");
	char buf[8];
	memset(buf,0,8);
	if(argc < 2)
	{
		printf("argc > 2 \n");
		return -1;
	}
	int 	Hash =atoi(argv[1]);


	while(fgets(buf,8,stream))
	{
		char *p = buf ;
		while(*p != '\n')
			p++;
		*p = '\0';
if( Hash == 1)		
		printf("%d \n",SDBMHash(buf));
else if (Hash == 2)
		printf(" %d \n",BKDRHash(buf));
else	
		printf("%d \n",RSHash(buf));

	}
	fclose(stream);
HP_TIMING_NOW(end);

//printf("\n the cost cycles are %lf ns\n", (end - start)/3.6);
return 0 ;
}
        
