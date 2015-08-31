/*
 * File name 	: quote_schedule.h 
 *
 * Author  		: He Wen Guan
 * 
 * Description	: The struct of schedule ;   
 *
 * Copyright (c) 2007-2015 MY Capital Inc.
 * */

#include <stdint.h>
#include <pthread.h>

#define     MAX_TASK_NUM        50 


typedef struct day_schedule {
    uint32_t    date_key;
    char        item[8];
    uint32_t    rank;
    char        contract[8];
} day_schedule_t;

typedef struct task_node {
	uint32_t    deep;
    uint32_t    cur_sub_index;
    char        item[8];
    uint32_t    rank;
    struct day_schedule  *next_sub_task;
}task_node_t;

typedef struct task_sched { 
    struct task_node    *task_array;  
    struct quote_map    *query_index;
	pthread_mutex_t 	lock[MAX_TASK_NUM];
} task_sched_t ; 


