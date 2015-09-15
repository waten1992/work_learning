/*
 ** File Name: my_stack.h
 **
 ** Author: He Wen Guan
 **
 ** Description:
 **          make like stl stack
 **
 ** */

#ifndef     MY_VECTOR_H
#define     MY_VECTOR_H

#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>

typedef struct stack {
    void        *bottom;
    void        *top;
	void 		*cur_pos;
    uint32_t    ele_size;
    uint32_t    tot_cnt;
    uint32_t    capacity;
}stack_t;

#endif
