/*
 * File Name: queue.h
 *
 * Author: He Wen Guan
 *
 * Description:
 * 			make like qul queue
 *
 * */

#ifndef 	MY_STACK
#define 	MY_STACK

#include "my_queue.h"

#ifdef _cplusplus
extern "C"
{
#endif


struct queue;

struct queue*
queue_constructor(uint32_t ele_size, uint32_t capacity);

void *
get_queue_front(struct queue *qu);

int
get_queue_empty(struct queue *qu);

uint32_t
get_queue_size(struct queue *qu);

int
push_back(struct queue *qu, void *in_data ,uint32_t ele_size);

int
pop_front(struct queue *qu);

int
queue_destroy(struct queue *qu);

#ifdef _cplusplus
}
#endif

#endif
