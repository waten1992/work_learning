/*
 *  * File Name: my_vector.h
 *   *
 *    * Author: He Wen Guan
 *     *
 *      * Description:
 *       *          make like stl vector
 *        *
 *         * */

#ifndef     MY_VECTOR_H
#define     MY_VECTOR_H


#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>

typedef struct vector {
    void        *start;
    void        *end;
    uint32_t    ele_size;
    uint32_t    tot_cnt;
    uint32_t    capacity;
}vector_t;

#endif
