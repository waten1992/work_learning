/*
 ** File name    : quote_service.h 
 **
 ** Author       : He Wen Guan
 ** 
 ** Description  : Input (date , item ,rank) query contract content   
 **
 ** Copyright (c) 2007-2015 MY Capital Inc.
 **
 * * */

#include "schedule.h"
#include "quote_service.h"

struct task_sched*
task_sched_init(task_sched_cfg_t* cfg)
{
	struct task_sched *ts;
	ts = (task_sched_t *)malloc(sizeof(task_sched_t));
	if (NULL == ts) {
          printf("ts allocate is error , errno is : %s \n",strerror(errno));
    }

    struct task_node *task_array ;
    task_array = (struct task_node *)malloc( MAX_TASK_NUM * sizeof(struct task_node));
    if (NULL == task_array ) { 
        printf("task_array allocate is error , errno is : %s \n",strerror(errno));
    }   

    for (int i = 0 ; i < MAX_TASK_NUM ; i++) {
        task_array[i].next_sub_task = NULL; 
    }   

    ts->task_array = task_array ;

    struct quote_map * query_index ;
    query_index = (quote_map_t *)malloc(sizeof(quote_map_t));
    if (NULL == query_index ) { 
        printf("query_index allocate is error , errno is : %s \n",strerror(errno));
    }  
    ts->query_index = query_index;

    ts->query_index = qsvr_init(cfg->quote_origin_data_path,cfg->quote_item_path);
return ts;
}

void
handle_quote_query(struct task_sched *ts ,struct day_schedule *input)
{
    unsigned long start, end;
		
	HP_TIMING_NOW(start);
	quote_find_use_date_key(ts,input);
	HP_TIMING_NOW(end);

	printf("\n the cost cycles are %lf ns\n", (end - start)/3.6)		;
}

int
task_sched_add(struct task_sched* ts, task_t* task)
{
	int ret_id = 0 ;
    unsigned long start, end;
    uint32_t begin_date ,end_date ,deep ;

	/*check task_array is available for client requst*/
    for(int i = 0; i < MAX_TASK_NUM; i++) {
        if(ts->task_array[i].next_sub_task == NULL) {
            ret_id = i ;
            break;
        }
    }

	/* copy the arg of the quote input data to quote_schedule_t *qs  */
    begin_date  = calculate_year_key(task->beg_date);
    end_date    = calculate_year_key(task->end_date);
    deep        = (end_date - begin_date) + 1;

    struct day_schedule *sub_task ;
    sub_task = (struct day_schedule *)malloc(deep*sizeof(struct day_schedule));
    if (NULL == sub_task) {
        printf("sub_task allocate fail: %s\n", strerror(errno));
    }
    memset(sub_task,0,deep*sizeof(struct day_schedule));

	/*init the task_node_t */
    ts->task_array[ret_id].next_sub_task    = sub_task;
    ts->task_array[ret_id].deep             = deep;
    ts->task_array[ret_id].rank             = task->rank;
    ts->task_array[ret_id].cur_sub_index    = 0;
    memcpy(ts->task_array[ret_id].item,task->item,ITEM_LEN);

	/* init day_task */  
    HP_TIMING_NOW(start);
    for(int i = 0 ; i < deep ; i++) {
        sub_task[i].date_key = begin_date + i;
        sub_task[i].rank     = task->rank;
        memcpy(sub_task[i].item ,task->item ,ITEM_LEN);
        handle_quote_query(ts,&sub_task[i]);
    }
    HP_TIMING_NOW(end);

    printf("\n ****the cost time  are %lf ns\n", (end - start)/3.6);
return ret_id ;
}

int
task_sched_del(struct task_sched* ts, int task_id)
{
	free(ts->task_array[task_id].next_sub_task);
	ts->task_array[task_id].next_sub_task  = NULL;
return 0; 
}

void
task_quote_sched_func(struct task_sched *ts)
{
    uint32_t step = 0, head_index = 0 ,tail_index = 0;

    int i = 0 ; 
    while (1) {

        while (1) {
            while ((ts->task_array[i].next_sub_task == NULL) && (i < MAX_TASK_NUM)) {                i++ ;
            }
    
            if(MAX_TASK_NUM  == i ) {
                i = 0 ;   /*start from zero */
            } else {
                step = i + 1;
                break;
            }
        }
        head_index = ts->task_array[i].cur_sub_index ;
        struct  day_schedule *cur_tmp;
        cur_tmp = &(ts->task_array[i].next_sub_task[head_index]);

        while (1) {
            while ((ts->task_array[step].next_sub_task  == NULL) && (step < MAX_TASK_NUM)) {
                step++;
            }
    
            if (MAX_TASK_NUM == step) {
                step = 0;
            } else {
                if(step == i){
                    printf("Series- date_key: %d ,item : %s ,rank : %d , contract : %s \n",cur_tmp->date_key ,cur_tmp->item ,cur_tmp->rank,cur_tmp->contract);
 printf("\n");
                    ts->task_array[i].cur_sub_index++;
                }
                break;
            }
        }
        if (i != step) {
            tail_index = ts->task_array[step].cur_sub_index;
            struct  day_schedule *step_tmp;
            step_tmp =&(ts->task_array[step].next_sub_task[tail_index]) ;

            if ((step_tmp->item != cur_tmp->item ) ||
                (step_tmp->contract != cur_tmp->contract) ||
                ((step_tmp->rank == cur_tmp->rank) && (step_tmp->date_key == cur_tmp->date_key))) {
                printf("Parallel-date_key: %d ,item : %s ,rank : %d , contract : %s \n",cur_tmp->date_key ,cur_tmp->item ,cur_tmp->rank,cur_tmp->contract);
                printf("Parallel-date_key: %d ,item : %s ,rank : %d , contract : %s \n",step_tmp->date_key ,step_tmp->item ,step_tmp->rank,step_tmp->contract);
                printf("\n");

                ts->task_array[i].cur_sub_index++       ;
                ts->task_array[step].cur_sub_index++    ;
            }else {
                printf("Series_first-date_key: %d ,item : %s ,rank : %d , contract : %s \n",cur_tmp->date_key ,cur_tmp->item ,cur_tmp->rank,cur_tmp->contract);
                printf("Series_second-date_key: %d ,item : %s ,rank : %d , contract : %s \n",step_tmp->date_key ,step_tmp->item ,step_tmp->rank,step_tmp->contract);
                printf("\n");
            }

        }
        /*when task_node finish ,need free this task,if (i == step) just output one time */
		if (ts->task_array[i].cur_sub_index == ts->task_array[i].deep) {
			task_sched_del(ts,i);
			printf("clear : %d !\n",i);
		}
		if ((ts->task_array[step].cur_sub_index == ts->task_array[step].deep) && (i != step)) {
			task_sched_del(ts,step);
			printf("clear : %d !\n",step);
		}
        i = step ;
    }
}

void
task_sched_destroy(struct task_sched* ts)
{
	for(int i = 0 ; i < MAX_TASK_NUM ; i++) {
		if(ts->task_array[i].next_sub_task != NULL) {
			free(ts->task_array[i].next_sub_task);
    	}
	}   
    free(ts->task_array);
    free(ts)            ;
    printf("destory_quote_schedule is finish \n");
}

