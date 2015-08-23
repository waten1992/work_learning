#include "schedule.h"
#include "quote_service.h"
/*
 *  *start codeing 
 *   *
 *    * */
int 
add(struct quote_schedule_t *qs)
{
	int ret_id = 0 ;
	unsigned long start, end;	
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
	memset(sub_task,0,deep*sizeof(struct day_schedule_t));
#if 1 // init day_task 	
	HP_TIMING_NOW(start);
	for(int i = 0 ; i < deep ; i++) {
		sub_task[i].date_key = begin_date + i 					;	
		sub_task[i].rank 	 = qs->input_info->rank 			;
		memcpy(sub_task[i].item ,qs->input_info->item ,ITEM_LEN);
		handle_quote_query(&sub_task[i]);	
	}
	HP_TIMING_NOW(end);
#endif
/*init the task_node_t */
	qs->task_array[ret_id].next_sub_task = sub_task;
	qs->task_array[ret_id].begin_date = begin_date;
	qs->task_array[ret_id].end_date = end_date;
	qs->task_array[ret_id].deep = deep;
	qs->task_array[ret_id].rank = qs->input_info->rank;
	qs->task_array[ret_id].cur_sub_index = 0;
	memcpy(qs->task_array[ret_id].item,qs->input_info->item,ITEM_LEN);

	printf("\n ****the cost time  are %lf ns\n", (end - start)/3.6)        ;
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

	for (int i = 0 ; i < MAX_TASK_NUM ; i++) {
		task_array[i].next_sub_task = NULL; 
	}

	qs->task_array = task_array ;			

return qs ;
}

void 
quote_schedule_func(struct quote_schedule_t *qs)
{
	uint32_t step = 0, head_index = 0 ,tail_index = 0;

	int i = 0 ;
	while (1) {
	start : while((qs->task_array[i].next_sub_task == NULL) && (i < MAX_TASK_NUM)) {
			i++ ;
		}

		if(MAX_TASK_NUM  == i ) {
			i = 0 ;   /*start from zero */
			goto start ;
		} else {
			step =  i + 1 ;
		}

		while ((qs->task_array[step].next_sub_task  == NULL) && (step < MAX_TASK_NUM)) {	
			step++;
		}

		head_index = qs->task_array[i].cur_sub_index ;
		struct	day_schedule_t *cur_tmp;
		cur_tmp = &(qs->task_array[i].next_sub_task[head_index]);
		
		
		if (MAX_TASK_NUM == step) {
			//series output qs->task_array[i] 
			printf("Series- date_key: %d ,item : %s ,rank : %d , contract : %s \n",cur_tmp->date_key ,cur_tmp->item ,cur_tmp->rank,cur_tmp->contract);
			qs->task_array[i].cur_sub_index++;			
		}else {

			tail_index = qs->task_array[step].cur_sub_index;
			struct  day_schedule_t *step_tmp;
			step_tmp =&(qs->task_array[step].next_sub_task[tail_index]) ;

			if (step_tmp->item != cur_tmp->item  ) {
	Parallel:	printf("Parallel-date_key: %d ,item : %s ,rank : %d , contract : %s \n",cur_tmp->date_key ,cur_tmp->item ,cur_tmp->rank,cur_tmp->contract);
				printf("Parallel-date_key: %d ,item : %s ,rank : %d , contract : %s \n",step_tmp->date_key ,step_tmp->item ,step_tmp->rank,step_tmp->contract);
				qs->task_array[i].cur_sub_index++		;
				qs->task_array[step].cur_sub_index++	;	
			}else {
				if (step_tmp->contract != cur_tmp->contract) {
					goto Parallel; /* jmp Parallel handle */
				}else {
					printf("first-date_key: %d ,item : %s ,rank : %d , contract : %s \n",cur_tmp->date_key ,cur_tmp->item ,cur_tmp->rank,cur_tmp->contract);
					printf("second-date_key: %d ,item : %s ,rank : %d , contract : %s \n",step_tmp->date_key ,step_tmp->item ,step_tmp->rank,step_tmp->contract);
				}	
			}
		}		
		/*when task_node finish ,need free this task */
		if (qs->task_array[i].cur_sub_index == qs->task_array[i].deep) {
			free(qs->task_array[i].next_sub_task);
			qs->task_array[i].next_sub_task = NULL ;		
			printf("clear : %d !\n",i);	
		}
		if (qs->task_array[step].cur_sub_index == qs->task_array[step].deep ) {
			free(qs->task_array[step].next_sub_task);
			qs->task_array[step].next_sub_task = NULL;
			printf("clear : %d !\n",step);
		}
		i = step ;
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
	memset(input,0,sizeof(struct quote_input_info_t));
	input_1 = (struct quote_input_info_t *)malloc(sizeof(struct quote_input_info_t));
	memset(input_1,0,sizeof(struct quote_input_info_t));
	
	input->begin_date = 20150601 ;
	input->end_date   = 20150631 ;
	sprintf(input->item,"%s","IF");
	input->rank = 2 ;

	input_1->begin_date = 20150701 ;
    input_1->end_date   = 20150731 ;
	sprintf(input_1->item,"%s","IF");
    input_1->rank       = 1        ;

	printf("quote_input_info_t :  %ld \n",sizeof(struct quote_schedule_t));
	init_history_quote();	
	qs = init_quote_schedule()		;	
	qs->input_info = input 			;
	ret_id  = add(qs)				;
	printf ("ret_id : %d \n", ret_id);
	
	qs->input_info = input_1 		;
	ret_id  = add(qs)				;
	printf ("ret_id : %d \n", ret_id);
	quote_schedule_func(qs);
//	handle_quote_query(input_1);
	printf("0701: %d ,0731=%d \n",calculate_year_key(20150701),calculate_year_key(20150731));	
	destory_quote_schedule(qs)		;
return 0 ;
}
