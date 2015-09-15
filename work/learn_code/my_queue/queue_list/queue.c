#include "my_queue.h"

struct queue*
queue_constructor()
{
	struct queue *p;
	p = (struct queue *)malloc(sizeof(struct queue));
	if ( NULL == p ) {
		fprintf(stderr,"struct queue * p malloc is fail ! \n ");
		return NULL;
	} 
	/*init struct queue head */
	p->tot_cnt = 0;
	p->head = p->tail = NULL;
	return p;
}

void *
get_queue_front(struct queue *qu)
{
	if (get_queue_empty(qu)) {
		fprintf(stderr, "current queue is empty ! \n");
		return NULL;
	}
	return qu->head;	
}

int 
get_queue_empty(struct queue *qu)
{
	return ((NULL == qu->head) && (NULL == qu->tail));
}

uint32_t
get_queue_size(struct queue *qu)
{
	return qu->tot_cnt;
}

int create_node(struct queue *p, void *in_data ,uint32_t size)
{
	struct qu_content *new_node , *tmp;
	new_node = (struct qu_content *)malloc(sizeof(struct qu_content));
	new_node->content = malloc(size);
	memcpy(new_node->content, in_data, size);
	if (NULL == new_node) {
		fprintf(stderr ,"new_node malloc is fail \n");
		return -1;
	}
	if (NULL == p->tail) {
		p->tail = new_node;
		p->head = new_node;
		new_node->next = NULL;
	} else {
		tmp = p->tail;
    	tmp->next = new_node;
		p->tail = new_node;
		new_node->next = NULL;
	}
	return 0;
}

int 
del_all_node(struct queue *qu)
{
	struct qu_content *tmp ,*cur;
	cur = tmp = qu->head;
	while(tmp != NULL) {
		cur = tmp->next;
		free(tmp->content);
		free(tmp);
		tmp = NULL;
		tmp = cur;
	};
	return 0;
}

int 
del_one_node(struct queue* qu)
{
	struct qu_content *cur;
	cur = qu->head;
	if (qu->head == qu->tail) {
		qu->head = qu->tail = NULL;	
	} else {
		qu->head = cur->next;
	}
	free(cur->content);
	free(cur);
	cur = NULL;
	return 0;
}

int
push_back(struct queue *qu, void *in_data, uint32_t ele_size )
{
	int ret;
	ret = create_node(qu, in_data,ele_size);
	if (-1 == ret) {
		fprintf(stderr,"push_back is fail \n");
		return -1;
	}
	/*update queue struct head */
	qu->tot_cnt += 1;
	return 0;
}


int
pop_front(struct queue *qu)
{
	if (get_queue_empty(qu)) {
		fprintf(stderr, "current queue is empty ! \n");
		return -1;
	}
	del_one_node(qu);
	qu->tot_cnt -= 1;
	return 0;
}

int
queue_destroy(struct queue *qu)
{
	del_all_node(qu);
	free(qu);
	return 0;
}

