#include <stdio.h>
#include <string.h>

struct my_marketdata 
{
	long time;
	char contract[64];
		int curr_volume;		/*当前量*/
			int b_total_volume;		/*买成交量*/
				int s_total_volume;		/*卖成交量*/
				double last_price;      /*最新价*/
				double b_open_interest; /*买持仓量*/
							double s_open_interest; /*卖持仓量*/
	
								double buy_price[30];
									int buy_vol[30];
									double sell_price[30];
											int sell_vol[30];
											};

int 
main()
{
	int a[] = {11,2,7,5,6,4,12,16};
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
	printf("sizeof my_marketdata : %d \n",sizeof(struct my_marketdata));
return 0;
}
