/*
 ** File Name: my_queue.h
 **
 ** Author: He Wen Guan
 **
 ** Description:
 **          make like stl queue , use linklist stroe the queue elements 
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
    void        *head;
	void 		*tail;
    uint32_t    tot_cnt;
}queue_t;

typedef struct qu_content {
	void *content;
	struct qu_content *next;	
}qu_content_t;

#endif
