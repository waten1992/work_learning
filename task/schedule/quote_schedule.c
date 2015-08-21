#include "schedule.h"

/*
 *declared function prototype
 * 
 * */

int 
add(struct quote_schedule_t *qs);

int 
del(struct quote_schedule_t *qs  , int del_id );

struct quote_schedule_t *
init_quote_schedule();

void 
destory_quote_schedule(struct quote_schedule_t *qs);


/*
 *start codeing 
 *
 * */

uint32_t 
Is_Leap_year(uint32_t year )
{
    uint32_t Leap = 0 ;
    if( ((year%4 == 0)&&(year%100 != 0)) ||(year%400==0)) {
		Leap = 1 ;
	}
return Leap ;
}

uint32_t 
calculate_year_key( uint32_t date )
{
	uint32_t  Leap_array[] = {0 ,1 ,1 ,1 ,2 ,2 ,2 ,2 ,3 ,3 ,3 ,3 ,4 ,4 ,4 ,4 ,5   ,5 ,5 ,5 ,6 ,6 ,6 ,6 ,7 ,7 ,7 ,7 ,8 ,8 ,8 ,8 ,9 ,9 ,9 ,9 ,10 ,10 ,10 ,10 };
  
    uint32_t  min_month_flag[] ={0,0,0,1,1,2,2,2,3,3,4,4}; //NOT ZERO mean stand   the total of min month from January,except February
    uint32_t  day ,month ,year ,Leap = 0 ,all_day ,year_day ;
  
    day     =   date %100		;
    month   =   (date%10000)/100;
    year    =   (date/10000)	;
    Leap =  Is_Leap_year(year)	;
  
    if ((month -1) >= 2){
        year_day  = (month-2)*31 -min_month_flag[month-2] + day  + 28 + Leap 		 ;           
        all_day   = year_day + (year - 2012)*365 +Leap_array[year-2012] - Start_day  ;
 
    }else if (month == 2) {
       	year_day = 31 + day 													 ;
		all_day  = year_day + (year -2012)*365 +Leap_array[year-2012] - Start_day;
    }else{
		all_day = day + (year - 2012)*365 +Leap_array[year-2012] - Start_day;
    }   

return all_day;
}



int 
add(struct quote_schedule_t *qs)
{
	int ret_id ;	
	uint32_t begin_date ,end_date ,deep ;
/*check task_array is available for client requst*/	
	for(int i = 0; i < MAX_TASK_NUM; i++) {	
		if(qs->task_array[i].next_sub_task == NULL) {
			ret_id = i ;
			break;
		}
	}	

/* copy the arg of the quote input data	to quote_schedule_t *qs 	*/
	begin_date 	= calculate_year_key(qs->input_info->begin_date) 	; 
	end_date 	= calculate_year_key(qs->input_info->end_date) 		;
	deep 		= (end_date - begin_date) + 1						;
	
	struct day_schedule_t *sub_task ;
	sub_task = (struct day_schedule_t *)malloc(deep*sizeof(struct day_schedule_t));
  	
	for(int i = 0 ; i < deep ; i++) {
		sub_task[i].date_key = begin_date + i 					;	
		sub_task[i].rank 	 = qs->input_info->rank 			;
		memcpy(sub_task[i].item ,qs->input_info->item ,ITEM_LEN);	
	}

	qs->task_array[ret_id].next_sub_task = sub_task ;

#if 0 //for test
	for(int i = 0  ; i < deep ; i++) {
		 printf("i = %d , date :%d , item : %s \n",i,sub_task[i].date_key,sub_task[i].item);
	}
#endif 

return ret_id ;
}

int 
del(struct quote_schedule_t *qs ,int del_id)
{
	free(qs->task_array[del_id].next_sub_task)		;

	qs->task_array[del_id].next_sub_task  = NULL	;		

return 0; 
}

struct quote_schedule_t *
init_quote_schedule()
{
	struct quote_schedule_t *qs ;
	qs = (struct quote_schedule_t *)malloc (sizeof(struct quote_schedule_t )) ;

    struct task_node_t *task_array ;
	task_array = (struct task_node_t *)malloc( MAX_TASK_NUM * sizeof(struct task_node_t)) ;

	for(int i = 0 ; i < MAX_TASK_NUM ; i++) {
		task_array[i].next_sub_task = NULL; 
	}

	qs->task_array = task_array ;			

return qs ;
}

void 
quote_schedule_func(struct quote_schedule_t *qs)
{
	uint32_t step = 0, head_index = 0 ,tail_index = 0;

	for (int i = 0 ; i < MAX_TASK_NUM ; i++) {
		while(qs->task_array[i].next_sub_task == NULL) {
			i++ ;
		}
		step =  i + 1 ;

		while ((qs->task_array[step].next_sub_task  == NULL) && (step < MAX_TASK_NUM) ) {	
			step++;
		}
	
		head_index = qs->task_array[i].cur_sub_index ;
		tail_index = qs->task_array[step].cur_sub_index;
		
		struct	day_schedule_t *cur_tmp;
		cur_tmp = &(qs->task_array[i].next_sub_task[head_index]);
		
		struct  day_schedule_t *step_tmp;
		step_tmp =&(qs->task_array[step].next_sub_task[tail_index]) ;

		if (step_tmp->item != cur_tmp->item  ) {
			printf("contract 1 : %s , contract 2 : %s \n ", step_tmp->item , cur_tmp->item);
		qs->task_array[i].cur_sub_index++		;
		qs->task_array[step].cur_sub_index++	;	
		}		
	}
}

void 
destory_quote_schedule(struct quote_schedule_t *qs)
{
	for(int i = 0 ; i < MAX_TASK_NUM ; i++) {
		free(qs->task_array[i].next_sub_task);
	}
	free(qs->task_array);
	free(qs)			;
	printf("destory_quote_schedule is finish \n");
}

int 
main()
{
	struct quote_schedule_t *qs 	;
	struct quote_input_info_t *input, *input_1; 
	uint32_t ret_id 				;

	input = (struct quote_input_info_t *)malloc(sizeof(struct quote_input_info_t));
	input_1 = (struct quote_input_info_t *)malloc(sizeof(struct quote_input_info_t));
	
	input->begin_date = 20150701 ;
	input->end_date   = 20150731 ;
	input->item		  = "shag"   ;
	input->rank 	  = 1 		 ;

	input_1->begin_date = 20150701 ;
    input_1->end_date   = 20150731 ;
    input_1->item       = "IF"   ;   
    input_1->rank       = 1        ;


	qs = init_quote_schedule()		;	
	qs->input_info = input 			;
	ret_id  = add(qs)				;
	printf ("ret_id : %d \n", ret_id);
	
	qs->input_info = input_1 		;
	ret_id  = add(qs)				;
	printf ("ret_id : %d \n", ret_id);
	quote_schedule_func(qs);
printf("0701: %d ,0731=%d \n",calculate_year_key(20150701),calculate_year_key(20150731));	
	destory_quote_schedule(qs)		;
return 0 ;
}
