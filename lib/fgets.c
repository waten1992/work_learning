/* fgets: get at most n chars from iop */
char *fgets(char *s, int n, FILE *iop)
{
    register int c;
    register char *cs;
    cs = s;
    while (--n > 0 && (c = getc(iop)) != EOF)

        if ((*cs++ = c) == '\n')
            break;
    *cs = '\0';
    return (c == EOF && cs == s) ? NULL : s;
}
/*
  1 #include<stdio.h>
  2 #include<stdlib.h>
  3 #include<string.h>
  4 int main()
  5 {
  6         char buf[20];
  7         memset(buf,'\0',sizeof(buf));
  8         fgets(buf,sizeof(buf),stdin);
  9         int i = 0 ;
 10         while(buf[i] != '\0'  )
 11         {
 12                 printf("%d \t",buf[i]);
 13                 i++;
 14         }
 15 return 0;

  ½á¹û£º

    pwd006@Debain:~/test$ gcc -o fgets fgets.c
    pwd006@Debain:~/test$ ./fgets
    ho
    104 	111 	10 	pwd006@Debain:~/test$
  }
~


*/
