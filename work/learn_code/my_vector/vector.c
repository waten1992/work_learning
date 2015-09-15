#include "my_vector.h"

struct vector *
vector_constructor(uint32_t ele_size, uint32_t capacity)
{
	struct vector *v;
	uint32_t tot_size = ele_size * capacity;
	if (ele_size <= 0 || capacity <= 0 ) {
		fprintf(stderr,"constructor func para is error! \n");
		return NULL;
	}

	v = (struct vector *)malloc(sizeof(struct vector));
	if (NULL == v) {
        fprintf(stderr,"struct vector is fail %s\n",strerror(errno));
        return NULL;
	}

	v->start = malloc(tot_size);
	if (NULL == v) {
        fprintf(stderr,"v->start is fail %s\n",strerror(errno));
        return NULL;
	}
	v->ele_size = ele_size;
	v->capacity = capacity;
	v->end = v->start;
	v->tot_cnt = 0;
	return v;
}

void *
get_vector_begin(struct vector *v)
{
    return v->start;
}

void *
get_vector_end(struct vector *v)
{
    return v->end;
}

void *
get_vector_at(struct vector *v, int cur_pos)
{ 
	if (cur_pos >= v->tot_cnt || cur_pos < 0) {
		fprintf(stderr,"vector cur_pos is invalid \n");
		return NULL;
	}
	char *tmp = (char *)v->start + v->ele_size * cur_pos;
	return tmp;
}

uint32_t
get_vector_size(struct vector *v){
	return v->tot_cnt;
}

uint32_t 
get_vector_capacity(struct vector *v)
{
	return v->capacity;
}

int 
push_back(struct vector *v, void *in_data ,uint32_t ele_size)
{
	int ret ;
	if (ele_size != v->ele_size ) {
		fprintf(stderr,"ele_size is invalid \n");
		return -1;		
	}
	
	if (v->tot_cnt >= v->capacity) {
		ret = reallocate(v);
		if (-1 == ret) {
			fprintf(stderr,"reallocate is fail \n");
			return -1;
		}	
	}
	memcpy(v->end , in_data, ele_size);
	/* update vector struct record */
	v->tot_cnt += 1;
	v->end = (char *)v->end +v->ele_size;
return 0;
}

int 
reallocate(struct vector *v)
{
	/*double original capacity allocate*/
	printf("************reallocate was called*****************\n");
	int  re_size = (v->capacity * v->ele_size)*2 ; 
	void *tmp = realloc(v->start,re_size);
	if (NULL == tmp) {
		fprintf(stderr,"reallocate is fail! \n");
		return -1;
	}
	v->start = tmp;
	v->end =(char *)v->start + (v->ele_size * v->tot_cnt);
	v->capacity *= 2;
return 0;
}

int 
pop_back(struct vector *v)
{
	if ( v->tot_cnt == 0 ) {
		fprintf(stderr,"pop_back is fail, no element for pop \n");
		return -1;
	}
	v->end = (char *)v->end - (v->ele_size); 	
	v->tot_cnt -= 1; 
	
return 0;	
}

int 
vector_insert_one_ele(struct vector *v, void *data_in ,int insert_idx)
{
	int idx , ret;
	if (insert_idx > v->tot_cnt || insert_idx < 0){
		fprintf(stderr,"insert_idx is invalid \n");
		return  -1;
	}

	if (v->tot_cnt + 1 == v->capacity ) {
		ret = reallocate(v);
		if (-1 == ret) {
			fprintf(stderr,"reallocate is fail \n");
			return -1;
		}
	}
	/* everytime memcpy one struct avoid memory overlap */
	/*  
	char *tmp ;
	for (idx = v->tot_cnt ; idx >= insert_idx ;idx--) {
		tmp = (char *)v->start + (idx * v->ele_size);
		memcpy((tmp + v->ele_size), tmp , v->ele_size);
	}
	*/
	char *cur = (char *)v->start + (insert_idx * v->ele_size);
	char *next = cur + v->ele_size;
	int size = (v->tot_cnt - insert_idx )*v->ele_size; 
	memmove(next,cur,size); /*this function avoid memory overlap*/
	memcpy(cur, data_in, v->ele_size );
	/*update the vector struct */
	v->tot_cnt += 1;
	v->end = (char *)v->end + (v->ele_size);
	
	return 0;	
}

int 
vector_clear(struct vector *v)
{
	v->end = v->start;
	v->tot_cnt = 0;
return 0;	
}

int 
vector_erase_one_ele(struct vector *v, int erase_idx)
{
	int idx ;
	if (erase_idx >= v->tot_cnt || erase_idx < 0){
		fprintf(stderr,"erase_idx is invalid \n");
		return  -1;
	}
	/*
	for (idx = erase_idx; idx < v->tot_cnt ;idx ++) {
		char *tmp = (char *)v->start + (idx * v->ele_size) ;
		memcpy( tmp, tmp+v->ele_size, v->ele_size);
	}
	*/
	char *cur = (char *)v->start + (erase_idx * v->ele_size);
	char *next = cur + v->ele_size;
	int size = (v->tot_cnt - erase_idx)*v->ele_size ;
	memmove(cur,next, size);
	/*update the vector struct */
	v->tot_cnt -= 1;
	v->end = (char *)v->end - (v->ele_size);
return 0;
}

int 
vector_destroy(struct vector *v)
{
	free(v->start);
	free(v);
return 0;
}
