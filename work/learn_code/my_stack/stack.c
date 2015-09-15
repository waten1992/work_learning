#include "my_stack.h"

struct stack *
stack_constructor(uint32_t ele_size, uint32_t capacity)
{
	struct stack *p;
	int size = ele_size * capacity ;
	if (ele_size <= 0 || capacity <= 0) {
		fprintf(stderr,"ele_size or capacity is invalid \n");
		return NULL;
	}
	p = (struct stack *)malloc(sizeof(struct stack));
	if ( NULL == p ) {
		fprintf(stderr,"struct stack * p malloc is fail ! \n ");
		return NULL;
	} 
	p->bottom = malloc(size);
	if ( NULL == p->bottom ) {
		fprintf(stderr,"struct stack * p->bottom  malloc is fail ! \n ");
		return NULL;
	} 
	p->cur_pos = p->bottom;
	p->top = p->bottom + size;
	p->capacity = capacity;
	p->tot_cnt = 0;
	p->ele_size = ele_size;

	return p;
}

void *
get_stack_top(struct stack *st)
{
	if (get_stack_empty(st)) {
		fprintf(stderr, "current stack is empty ! \n");
		return NULL;
	}
	return st->cur_pos;
}

int
get_stack_empty(struct stack *st)
{
	return (st->cur_pos == st->bottom);
}

uint32_t
get_stack_size(struct stack *st)
{
	return st->tot_cnt;
}

int
push(struct stack *st, void *in_data ,uint32_t ele_size)
{
	char *tmp ;
	int ret;
	if (ele_size != st->ele_size ) {
		fprintf(stderr,"ele_size is invalid \n");
		return -1;
	}

	if (st->tot_cnt >= st->capacity) {
		ret = st_reallocate(st);
		if (-1 == ret) {
			fprintf(stderr," st reallocate is fail \n");
			return -1;
		}
	}
	tmp = (char *)st->cur_pos + st->ele_size;
    memcpy(tmp , in_data, ele_size);

	st->tot_cnt += 1;
	st->cur_pos = tmp ;

	return 0;
}

int
st_reallocate(struct stack *st)
{
	/*double capacity allocate to new stack capacity*/
	uint32_t re_size =  (st->ele_size * st->tot_cnt)*2;
	void *tmp ;
	tmp = realloc(st->bottom,re_size);
	if (NULL == tmp) {
		fprintf(stderr,"st realloc is fail ! \n ");
		return -1;
	}
	st->bottom = tmp;
	st->capacity = 2*st->capacity;
	st->cur_pos = st->bottom + st->tot_cnt * st->ele_size;
	st->top = st->bottom + st->capacity*st->ele_size;
	return 0;
}

int
pop(struct stack *st)
{
	if (get_stack_empty(st)) {
		fprintf(stderr, "stack is empty,no data pop \n");
		return -1;
	}
	st->cur_pos = (char *)st->cur_pos - st->ele_size;
	st->tot_cnt -= 1;
	return 0;
}

int
stack_destroy(struct stack *st)
{
	free(st->bottom);
	free(st);
	return 0;
}



