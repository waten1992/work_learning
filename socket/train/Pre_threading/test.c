#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define Start_day 	153
	
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

unsigned int  Is_Leap_year(unsigned int year )
{
	unsigned int Leap = 0 ;
	if( ((year%4 == 0)&&(year%100 != 0)) ||(year%400==0))
		Leap = 1 ;
return Leap ;
}

int Binary_search(int a[] , int n,int x )
{
    int low = 0 , high =n-1 , mid ;
    while(low <= high)
    {   mid = low + (high-low)/2; //防止溢出
        if(a[mid] == x)
            return mid;
        else if (a[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}
int main(int argc , char *argv[])
{
#if 0
	union key test ;
	memset(&test,0,8);
	test.bit.a = 1;
	test.bit.b = 1;
	test.bit.c = 1;
	test.bit.d = 1;
	test.bit.e = 1;

#endif
#if 0
	int a[2][3]={
				 {1,2,3},
				 {4,5,6}
				};
	printf("%d , 5/2 = %d \n",a[0][0],5/2);
#endif 

#if 1
if (argc < 2 )
{
	printf("argc < 2 \n");
	return -1 ;
}
unsigned int Leap_array[] = {0 ,1 ,1 ,1 ,2 ,2 ,2 ,2 ,3 ,3 ,3 ,3 ,4 ,4 ,4 ,4 ,5 ,5 ,5 ,5 ,6 ,6 ,6 ,6 ,7 ,7 ,7 ,7 ,8 ,8 ,8 ,8 ,9 ,9 ,9 ,9 ,10 ,10 ,10 ,10 };
//unsigned int Leap_array[40]= {0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,2 ,0 ,0 ,0 ,3 ,0 ,0 ,0 ,4 ,0 ,0 ,0 ,5 ,0 ,0 ,0 ,6 ,0 ,0 ,0 ,7 ,0 ,0 ,0 ,8 ,0 ,0 ,0 ,9 ,0 ,0 ,0} ;// = {2012,2016,2020,2024,2028,2032,2036,2040,2044,2048}; //40 year ,start from 2012,but 2012 is set 0,
unsigned int min_month_flag[] ={0,0,0,1,1,2,2,2,3,3,4,4}; //NOT ZERO mean stand the total of min month from January,except February
unsigned int date = atoi(argv[1]);
unsigned int day , month , year, Leap = 0 ,all_day ,year_day ,Leap_times ,tmp =1;

day 	= 	date %100;
month 	= 	(date%10000)/100;
year 	=	(date/10000);
Leap =  Is_Leap_year(year);
#if 1
 //generator for Leap_array[]
for(int i =2012 ; i < 2052 ;i++)
	{
		if (Is_Leap_year(i))
		{
				Leap_array[i-2012] = tmp-1 ;
			tmp++;
		}
		else
			Leap_array[i-2012] = tmp-1;			
	}
//Leap_times = Binary_search(Leap_array,sizeof(Leap_array)/sizeof(Leap_array[0]),year)+1;

for(int i = 0 ;i < 40  ; i++)
{

	printf("%d ,",Leap_array[i]);
}

#endif
printf("leap=%d , Leap_times : %d \n",Leap,Leap_array[year-2012]);
printf("year = %d ,month = %d ,day = %d\n",year ,month ,day);


#if 1
	if ((month -1) >= 2)
	{
		year_day  = (month-2)*31 -min_month_flag[month-2] + day  + 28 + Leap ; 		
		all_day   = year_day + (year - 2012)*365 +Leap_array[year-2012] - Start_day;
	}
	else if (month == 2)
	{
		year_day = 31 + day ;
		all_day  = year_day + (year -2012)*365 +Leap_array[year-2012] - Start_day;

	}
	else
	{
		all_day = day + (year - 2012)*365 +Leap_array[year-2012] - Start_day;	
	}

printf("%d  \n", all_day);

#endif

#endif 	

return 0;
}
