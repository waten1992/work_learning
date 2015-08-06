#include <stdio.h>
#include <string.h>
# define HP_TIMING_NOW(Var) \
 ({ unsigned long long _hi, _lo; \
  asm volatile ("rdtsc" : "=a" (_lo), "=d" (_hi)); \
  (Var) = _hi << 32 | _lo; })

void ouput_primes(const int NUM)
{
	unsigned long start, end; 
	HP_TIMING_NOW(start);
	int target_primes[NUM/3],target_index = 0 , bit_index = 0 , offset = 0;
	int flag_len = NUM / 32 ;
	int flag[flag_len + 1 ] ;
	memset(flag ,0 ,sizeof(flag));
	for(int index = 2 ; index  < NUM ; index++)
	{
	    bit_index = index / 32 ;
		offset = index % 32 ;
		if( !(flag[bit_index]&(1 << offset)) )
			target_primes[target_index++] = index ;
	
		for(int filter_index = 0 ;(filter_index < target_index) &&(index*target_primes[filter_index] < NUM)  ;filter_index++)
		{
	  		bit_index	= (index * target_primes[filter_index]) / 32  ;
			offset = (index * target_primes[filter_index]) %32 ;
			flag[bit_index] = ( flag[bit_index] | (1 << offset))  ;
			if(index % target_primes[filter_index] == 0)
				break;
		}
	}
	HP_TIMING_NOW(end);
	for (int i = 0 ; i <target_index ; i++ )
		printf("target_primes : %d \n",target_primes[i] );
	printf("\n the cost cycles are %ld\n", end - start);
	printf("\n the COST time : %lf ns \n", (end - start)/3.6);
}

int main()
{ 
	const int NUM = 99;
 	ouput_primes(NUM);
return 0 ;
}
