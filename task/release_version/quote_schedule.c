#include "schedule.h"

/*
 *  *declared function prototype
 *   * 
 *    * */

int 
add(struct quote_schedule_t *qs);

int 
del(struct quote_schedule_t *qs  , int del_id );

struct quote_schedule_t *
init_quote_schedule();

void 
destory_quote_schedule(struct quote_schedule_t *qs);

extern int  handle_quote_query(struct quote_input_info_t *input);
extern uint32_t Is_Leap_year(uint32_t year );

extern uint32_t calculate_year_key( uint32_t date );

/*
 *  *start codeing 
 *   *
 *    * */


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
	//quote_schedule_func(qs);
	handle_quote_query(input_1);
	printf("0701: %d ,0731=%d \n",calculate_year_key(20150701),calculate_year_key(20150731));	
	destory_quote_schedule(qs)		;
return 0 ;
}
