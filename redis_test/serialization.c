#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

#define comma_num  1

typedef  struct 
{
	char * ID ;
	int  name ;
}quote;


int main()
{
	quote *p ;
	char *quote_array ,*quote_rear;
	p = malloc(sizeof(quote));
	char *format_str[2];
	format_str[0] = (char *)malloc(2);
	format_str[1] = (char *)malloc(2);
	
	memset(format_str[0],0,2);
	memset(format_str[1],0,2);
	//format_str[0] ="[";
	//format_str[1] = "{";
//	char str[] = {'{','['};
	char *str = "{[";

	int str_len = 2 ;
//int str_len = sizeof(str)/sizeof(str[0]);
	for(int tmp_index =0 ;tmp_index <str_len ;tmp_index++ )
	{
		sprintf( format_str[tmp_index], "%c", str[tmp_index] );	
	}
	int index=0 ;
	quote_array  = (char *)malloc(sizeof(quote)+comma_num); 
	quote_rear = quote_array ;
   
    printf("sizeof(quote_array)=%d \n",sizeof(quote));
    p->ID = "waten";	
	p->name = 6 ;
	printf("%s\n",quote_rear);
	int i =	snprintf(quote_rear,sizeof(p->ID),"%s",p->ID);
    printf("i= %d ,sizeof(quote)=%d \n",i,sizeof(quote));
	
	printf("%s\n",quote_array);
	//quote_rear = quote_rear + i+1 ;
   // (char *)quote_rear =',';
	 strcat(quote_rear,format_str[index++]);
	printf("%s\n",quote_array);


return 0 ;
}
