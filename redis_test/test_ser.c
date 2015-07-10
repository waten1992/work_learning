#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

#define comma_num  1
#define char_num 182
#define format_len 112 
#define format_array_len 2
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
	char *format_str[format_len];
	size_t offset = 0;	
	char *content[] = 
	{
			"src",	"hwguan_test",
			"type","trading_msg",
			"data","column",
			"contract","item","exchange","last_price","volume","amount","price_change","open_interest","open_interest_change","open","low","high",
			"data","ag1507","item","A","3417","3521","7541145","-66","1926","50","3493","3486","3521",
			"STATE","OK",
			"type","trading_msg"
		
	};
	
	int	content_len = sizeof(content)/sizeof(content[0]);

	printf("%d\n",sizeof(content[1]));
#if 0		
	for(int tmp_index = 0 ;tmp_index <content_len ;tmp_index++)
		printf("%s \n",content[tmp_index]);
#endif 


	for(int tmp_index = 0 ;tmp_index <format_len ;tmp_index++)
		format_str[tmp_index] = (char *)malloc(2);

	
	for(int tmp_index = 0 ;tmp_index <format_len ;tmp_index++)
		memset(format_str[tmp_index],0,2);
	char *str = "{\"\":\"\",\"\":\"\",\"\":{\"\":[\"\",\"\",\"\",\"\",\"\",\"\",\"\",\"\",\"\",\"\",\"\",\"\"],\"\":[\"\",\"\",\"\",\"\",\"\",\"\",\"\",\"\",\"\",\"\",\"\",\"\"],\"\":\"\",\"\":\"\"}}";


#if 1 // init char to string
	for(int tmp_index =0 ;tmp_index <format_len ;tmp_index++ )
	{
		sprintf( format_str[tmp_index], "%c", str[tmp_index] );	
//		printf("tmp_index = %d $$$str[%d] =%c$$$$%s \n" ,tmp_index,tmp_index,str[tmp_index],format_str[tmp_index]);	
	
	}
#endif 


	size_t format_index=0 , content_index = 0 ;
	quote_array = (char *)malloc(sizeof(content)+char_num);
	quote_rear = quote_array ;
printf("%d \n",sizeof(quote_array));

/*1*/
	offset = snprintf(quote_rear,format_array_len,"%s",format_str[format_index++]);
 //   printf("i= %d ,sizeof(str_index)=%d \n",offset,sizeof(format_str[format_index]));
	quote_rear = quote_rear + offset  ;
	printf("data:  %s  offset :%d  format_index : %d \n",quote_array,offset,format_index);
	
	
	offset = snprintf(quote_rear,format_array_len,"%s",format_str[format_index++]);
	quote_rear = quote_rear + offset  ;
	printf("data:  %s  offset :%d  format_index : %d \n",quote_array,offset,format_index);

	offset = snprintf(quote_rear,sizeof(content[content_index]),"%s",content[content_index++]);
	quote_rear = quote_rear + offset  ;
	printf("data:  %s  offset :%d  content_index : %d \n",quote_array,offset,content_index);
/******str******/
	offset = snprintf(quote_rear,format_array_len,"%s",format_str[format_index++]);
	quote_rear = quote_rear + offset  ;
	printf("data:  %s  offset :%d  format_index : %d \n",quote_array,offset,format_index);

	offset = snprintf(quote_rear,format_array_len,"%s",format_str[format_index++]);
	quote_rear = quote_rear + offset  ;
	printf("data:  %s  offset :%d  format_index : %d \n",quote_array,offset,format_index);

	offset = snprintf(quote_rear,format_array_len,"%s",format_str[format_index++]);
	quote_rear = quote_rear + offset  ;
	printf("data:  %s  offset :%d  format_index : %d \n",quote_array,offset,format_index);

	offset = snprintf(quote_rear,sizeof(content[content_index]),"%s",content[content_index++]);
	quote_rear = quote_rear + offset  ;
	printf("data:  %s  offset :%d  content_index : %d \n",quote_array,offset,content_index);

	offset = snprintf(quote_rear,format_array_len,"%s",format_str[format_index++]);
	quote_rear = quote_rear + offset  ;
	printf("data:  %s  offset :%d  format_index : %d,format_str[format_index]=%s \n",quote_array,offset,format_index,format_str[format_index]);
/*2*/
#if 0 //for test 
	int index=0 ;
	quote_array  = (char *)malloc(sizeof(quote)+comma_num); 
	quote_rear = quote_array ;
   
    printf("sizeof(quote_array)=%d \n",sizeof(quote));
    p->ID = "waten";	
	p->name = 6 ;
	printf("%s\n",quote_rear);
	int i =	snprintf(quote_rear,sizeof(p->ID),"%s",p->ID);
    printf("i= %d ,sizeof(P->ID)=%d \n",i,sizeof(p->ID));
	
	 strcat(quote_rear,format_str[index++]);
	quote_rear  = quote_rear +i +1;
	printf("%s\n",quote_array);

	i =	snprintf(quote_rear,sizeof(p->name),"%d",p->name);
    printf("i= %d ,sizeof(quote)=%d \n",i,sizeof(p->name));

	 strcat(quote_rear,format_str[index++]);
	quote_rear  = quote_rear +i ;
	printf("%s\n",quote_array);
#endif 




return 0 ;
}
