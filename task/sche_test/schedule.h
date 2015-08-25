#ifndef TASK_SCHED_H
#define TASK_SCHED_H

/*
 *  *File Name 	: schedule.h 
 *   *
 *    *Description	: This file is description of quote task schedule
 *     * 
 *      *Author 		: He Wen Guan
 *       *
 *        *Time 			: 2015-8-20
 *         *
 *          *Copyright (c) 2007-2015 MY Capital Inc.
 *           *
 *            * */
 
#ifdef __cplusplus

extern "C"

{
#endif
 
#include <stdint.h>


typedef struct task {
	uint32_t beg_date;
	uint32_t end_date;
	char 	item[8];
	uint32_t rank;
}task_t;


typedef struct task_sched_cfg {
	char quote_origin_data_path[128];
	char quote_item_path[128];
} task_sched_cfg_t;

struct task_sched*
task_sched_init(task_sched_cfg_t* cfg);

/*
 *  * return task id
 *   * >= 0 : valid task id
 *    * <0   : invalid task id 
 *     */
int
task_sched_add(struct task_sched* ts, task_t* task);

int
task_sched_del(struct task_sched* ts, int task_id);

void
task_sched_destroy(struct task_sched* ts);

void 
task_quote_sched_func(struct task_sched *ts);


#ifdef __cplusplus
}
#endif

#endif
