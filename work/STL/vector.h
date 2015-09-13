/*
 * File Name: vector.h
 *
 * Author: He Wen Guan
 *
 * Description:
 * 			make like stl vector 
 *
 * */

#ifndef 	MY_VECTOR_H
#define 	MY_VECTOR_H

#include <stdio.h>
#include <stdint.h>
#include <error.h>
#include <errno.h>
#include <string.h>

#ifdef _cplusplus
extern "C"
{
#endif 		

struct vector;

struct vector*
constructor(uint32_t ele_size, uint32_t capacity);

void *
get_vector_begin(struct vector *v);

void *
get_vector_end(struct vector *v);

void *
get_vector_at(struct vector *v);

uint32_t
get_vector_size(struct vector *v);

int 
push_back(struct vector *v, void *in_data ,uint32_t ele_size);

int 
pop_back(struct vector *v);


#ifdef _cplusplus
}
#endif

#endif 
