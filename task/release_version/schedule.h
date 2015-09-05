/*
 *File Name 	: schedule.h 
 *
 *Description	: This file is description of quote task schedule
 * 
 *Author 		: He Wen Guan
 *
 *Time 			: 2015-8-20
 *
 *Copyright (c) 2007-2015 MY Capital Inc.
 *
 * */

#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>
#include <syslog.h>

#define 	MAX_TASK_NUM 	50 
#define 	ITEM_LEN 		8
#define  	Start_day		153 
#define 	CONTRACT_LEN	8

typedef struct day_schedule_t {
	uint32_t 	date_key;
	char 		item[8];
	uint32_t 	rank;
	char 		contract[8];
}day_sch_t;

typedef struct task_node_t {
	uint32_t	begin_date;
	uint32_t 	end_date;
	uint32_t 	deep;
	uint32_t 	cur_sub_index;
	char 		item[8];
	uint32_t 	rank;
	struct day_schedule_t  *next_sub_task;
}task_node_t;

typedef struct quote_input_info_t {
	uint32_t 	begin_date;
	uint32_t	end_date;
	char 		item[8];
	uint32_t 	rank;
}quote_input_info_t ; 

typedef struct quote_schedule_t {
	struct task_node_t 			*task_array;	
	struct quote_input_info_t 	*input_info;
}quote_sch_t ;

int 
task_add(struct quote_schedule_t *qs);

int 
task_del(struct quote_schedule_t *qs , int del_id);

struct quote_schedule_t *
init_quote_schedule();

void 
destory_quote_schedule(struct quote_schedule_t *qs);

void 
quote_schedule_func(struct quote_schedule_t *qs);

extern int  handle_quote_query(struct day_schedule_t *input);
extern uint32_t Is_Leap_year(uint32_t year );
extern uint32_t calculate_year_key( uint32_t date );
extern void init_history_quote();
extern int handle_quote_query(struct day_schedule_t *input) ;
