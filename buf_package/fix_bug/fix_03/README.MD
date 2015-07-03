#Add struct test !

struct prototype as follow:

		typedef  struct
    	{
        	int int_type ;
        	char char_type;
   		 }ts;

the result :

	ts size ->8 , test_arry--size--> 32 
	sp->size=8 , i=0 ,i*sp->size = 0 
	address of ---> 25750a0 ,sp->buf = 2575010 
	sp->size=8 , i=1 ,i*sp->size = 8 
	address of ---> 25750a8 ,sp->buf = 2575010 
	sp->size=8 , i=2 ,i*sp->size = 10 
	address of ---> 25750b0 ,sp->buf = 2575010 
	sp->size=8 , i=3 ,i*sp->size = 18 
	address of ---> 25750b8 ,sp->buf = 2575010 
	form master thread num=4 
	sp->num:8
	sp->front:0 
	sp->rear:4 
	child thread , it is successfull 
	----test of value address--->25750a0  
	the result -->0 , a 
	child thread , it is successfull 
	----test of value address--->25750a8  
	the result -->1 , b 
	child thread , it is successfull 
	----test of value address--->25750b0  
	the result -->2 , c 
	child thread , it is successfull 
	----test of value address--->25750b8  
	the result -->3 , d 
	child thread , it is successfull 
	child thread , it is successfull 

