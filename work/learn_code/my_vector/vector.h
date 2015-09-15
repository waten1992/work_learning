/*
 * File Name: vector.h
 *
 * Author: He Wen Guan
 *
 * Description:
 * 			make like stl vector
 *
 * */

#ifndef 	MY_VECTOR
#define 	MY_VECTOR

#ifdef _cplusplus
extern "C"
{
#endif


struct vector;

struct vector*
vector_constructor(uint32_t ele_size, uint32_t capacity);

void *
get_vector_begin(struct vector *v);

void *
get_vector_end(struct vector *v);

void *
get_vector_at(struct vector *v, int cur_pos);

uint32_t
get_vector_size(struct vector *v);

uint32_t
get_vector_capacity(struct vector *v);

int
push_back(struct vector *v, void *in_data ,uint32_t ele_size);


int
pop_back(struct vector *v);

int 
vector_instert_one_ele(struct vector *v, void *data_in ,int insert_idx);

int 
vector_erase_one_ele(struct vector *v, int erase_idx);

int 
vector_clear(struct vector *v);

int
vector_destroy(struct vector *v);

#ifdef _cplusplus
}
#endif

#endif
