/*
 ** File Name: my_queue.h
 **
 ** Author: He Wen Guan
 **
 ** Description:
 **          make like stl queue , use array store the queue elements 
 **
 ** */

#ifndef     MY_QUEUE_H
#define     MY_QUEUE_H

#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>

typedef struct queue {
    void        *start;
	uint32_t 	head;
	uint32_t 	tail;
    uint32_t    ele_size;
    uint32_t    tot_cnt;
    uint32_t    capacity;
}queue_t;

#endif
