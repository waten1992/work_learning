NAME
       bzero - write zero-valued bytes

SYNOPSIS
       #include <strings.h>

       void bzero(void *s, size_t n);

DESCRIPTION
       The  bzero()  function  sets the first n bytes of the area starting at s to zero
       (bytes containing '\0').



/* 测试  */  
CODE:
    #include<stdio.h>
    #include<string.h>
    int main()
     {
     
         char s[] ="he";
         printf("-->%d\n",sizeof(s));
         int tmp  = sizeof(s);
       
        bzero(s,tmp);
        for(int i = 0 ; i < tmp ; i++)
        {
            printf("%d\t",s[i]);
        }   
        
        printf(" \n " );
        return  0 ;
    } 
结果：
pwd006@Debain:~$ vi bzero.c
pwd006@Debain:~$ gcc -o bz bzero.c -std=gnu11
pwd006@Debain:~$ ./bz 
-->3
0 0 0  
pwd006@Debain:~$ 