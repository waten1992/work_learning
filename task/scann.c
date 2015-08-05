#include<stdio.h>
#include<malloc.h>
#include<string.h>
int main()
{
char *p,*tmp_p;
p = malloc(128);
memset(p,0,128);
p = "20141009 shag ag1410 5 /mnt/data/TickData/SHFE/20141009/";
int tmp = 0 ;
tmp_p = p ;
while(tmp_p != NULL)
{
	tmp++;
	tmp_p++;
}
printf("%d\n",tmp);
return 0;
}
