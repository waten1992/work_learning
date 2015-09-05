#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <stdint.h>

#define START_YEAR		1970

typedef struct my_tm {
	int tm_sec;    /* Seconds (0-60) */
	int tm_min;    /* Minutes (0-59) */
	int tm_hour;   /* Hours (0-23) */
	int tm_mday;   /* Day of the month (1-31) */
	int tm_mon;    /* Month (1-12) */
	int tm_year;   /* Year - 2015 */
}my_tm_t;

typedef struct ret_date {
	uint32_t 	month;
	uint32_t 	day;
}ret_date_t;

uint32_t  Is_Leap_year(uint32_t year )
{
       uint32_t Leap = 0 ;
       if( ((year%4 == 0)&&(year%100 != 0)) ||(year%400==0))
            Leap = 1 ;
  return Leap ;
}

ret_date_t * 
calculate_the_month(uint32_t days , uint32_t year)
{
	uint32_t  sum = 0 , i = 0;
	uint32_t tmp[12];
	uint32_t month_array[] = {1,0,1,0,1,0,1,1,0,1,0,1};
	ret_date_t *ret_date = (ret_date_t *)malloc(sizeof(ret_date_t));
	for (i = 0;i < 12; i++) {
		if (month_array[i]) {
			sum += 31;
		} else {
			sum += 30;  
		}
 		tmp[i] = sum ;
		if (i ==1) {
			if (Is_Leap_year(year)) {
				sum -= 1;
				tmp[i] = sum;
			} else {
				sum -= 2;
				tmp[i] = sum;	
			}
		}
	}

	for (i = 0; i < 12 ; i++) {
		if ((i != 11)&& (days > tmp[i]) && (days < tmp[i+1])) {
			ret_date->month = i + 2;
			break;
		} 	
		if (11 == i) {
			ret_date->month = 12 ;	
		}
	}
	ret_date->day = days - tmp[i];
	
return ret_date ;
}

int
fmt_time(long long sec_since_epoch )
{
	struct my_tm *date ;
	int Leap_year_num =0 , i = 0;
	date = (struct my_tm *)malloc(sizeof(my_tm_t));

	date->tm_sec = sec_since_epoch % 60 ;
	date->tm_min = (sec_since_epoch % 3600)/60;
	date->tm_hour = (sec_since_epoch % (24*3600))/3600 + 8 ;
	date->tm_year = (sec_since_epoch /(365*24*3600)) +START_YEAR;

	for (i = START_YEAR ; i < date->tm_year ; i++ ) {
		if (Is_Leap_year(i) ) {
			Leap_year_num++;
			/*	printf("%d = %d \n",i,Leap_year_num); */
		}
	}
	int tmp_days =  ((sec_since_epoch -(365*24*3600*(date->tm_year - START_YEAR)) - Leap_year_num*24*3600)*1.0)/(1.0*(24*3600)) + 0.5;
	ret_date_t *ret = calculate_the_month (tmp_days,date->tm_year);
	date->tm_mon = ret->month;	
	date->tm_mday = ret->day ;

	printf("%d-%d-%d  %d:%d:%d\n",date->tm_year,date->tm_mon,date->tm_mday,date->tm_hour,date->tm_min,date->tm_sec);

	free(date);
	free(ret);		
return 0;
}

int main()
{
 	time_t timep;
    time(&timep);
	fmt_time(timep);
return 0 ;
}
