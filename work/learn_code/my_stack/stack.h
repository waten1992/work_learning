/*
 * File Name: stack.h
 *
 * Author: He Wen Guan
 *
 * Description:
 * 			make like stl stack
 *
 * */

#ifndef 	MY_STACK
#define 	MY_STACK

#include "my_stack.h"

#ifdef _cplusplus
extern "C"
{
#endif


struct stack;

struct stack*
stack_constructor(uint32_t ele_size, uint32_t capacity);

void *
get_stack_top(struct stack *st);

int
get_stack_empty(struct stack *st);

uint32_t
get_stack_size(struct stack *st);

int
push(struct stack *st, void *in_data ,uint32_t ele_size);

int
pop(struct stack *st);

int
stack_destroy(struct stack *st);

#ifdef _cplusplus
}
#endif

#endif
