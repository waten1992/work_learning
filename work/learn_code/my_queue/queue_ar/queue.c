#include "my_queue.h"

struct queue*
queue_constructor(uint32_t ele_size, uint32_t capacity)
{
	struct queue *p;
	int size = ele_size * capacity ;
	if (ele_size <= 0 || capacity <= 0) {
		fprintf(stderr,"ele_size or capacity is invalid \n");
		return NULL;
	}
	p = (struct queue *)malloc(sizeof(struct queue));
	if ( NULL == p ) {
		fprintf(stderr,"struct queue * p malloc is fail ! \n ");
		return NULL;
	} 
	p->start = malloc(size);
	if ( NULL == p->start ) {
		fprintf(stderr,"struct queue * p->start  malloc is fail ! \n ");
		return NULL;
	} 
	/*init struct queue head */
	p->capacity = capacity;
	p->head = p->tail = 0;
	p->tot_cnt = 0;
	p->ele_size = ele_size;

	return p;
}

void *
get_queue_front(struct queue *qu)
{
	if (get_queue_empty(qu)) {
		fprintf(stderr, "current queue is empty ! \n");
		return NULL;
	}
	return ((char *)qu->start + qu->ele_size*qu->head);	
}

int
get_queue_full(struct queue *qu)
{
	if (qu->tot_cnt == qu->capacity) {
		return 1;
	} 
	return 0 ;
}

int 
get_queue_empty(struct queue *qu)
{
	return (!qu->tot_cnt);
}

uint32_t
get_queue_size(struct queue *qu)
{
	return qu->tot_cnt;
}

int
push_back(struct queue *qu, void *in_data ,uint32_t ele_size)
{
	int ret;
	void *tmp;
	if (ele_size != qu->ele_size ) {
		fprintf(stderr,"push_back() ele_size is invalid \n");
		return -1;
	}	
	if (get_queue_full(qu)) {
		fprintf(stderr," queue is full \n");
		return -1;
	}
 	tmp = (char *)qu->start + (qu->tail*qu->ele_size);
    memcpy(tmp, in_data, ele_size);
	/*update queue struct head */
	qu->tot_cnt += 1;
	qu->tail = (qu->tail + 1) % qu->capacity;
	return 0;
}

int
pop_front(struct queue *qu)
{
	if (get_queue_empty(qu)) {
		fprintf(stderr, "current queue is empty ! \n");
		return -1;
	}
	qu->tot_cnt -= 1;
	qu->head = (qu->head + 1) % qu->capacity;
	return 0;
}

int
queue_destroy(struct queue *qu)
{
	free(qu->start);
	free(qu);
	return 0;
}

