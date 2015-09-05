/*
 * File name 	: quote_service.h 
 *
 * Author  		: He Wen Guan
 * 
 * Description	: Input (date , item ,rank) query contract content   
 *
 * Copyright (c) 2007-2015 MY Capital Inc.
 * */

#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<malloc.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>


#define History_len		425212
#define Type_size		16
#define Tmp_array_len 	64
#define Start_value		96
#define Days			7320
#define Start_day 		153
#define Item_num		43
#define Item_hash_index	43
#define	Rank_hash_index	14
# define HP_TIMING_NOW(Var) \
 ({ unsigned long long _hi, _lo; \
  asm volatile ("rdtsc" : "=a" (_lo), "=d" (_hi)); \
  (Var) = _hi << 32 | _lo; })


typedef unsigned int uint32_t ;

typedef struct qsvr {
	uint32_t 	date ;
	char 		item[8];
	char 		contract[8];
	uint32_t 	rank;
	char 		quote_record[24];
	char 		address[128];
	struct qsvr *next ; 
}qsvr_data;

struct quote_map {

    uint32_t    ****index_array     ;   
    uint32_t    *hash               ;
    struct qsvr *origin_array       ;
    qsvr_data   qsvr_struct         ;
};

struct input_info_t {
	uint32_t 	date_key;
	char 		item[8];
	uint32_t 	rank;
}; 

struct quote_map*
qsvr_init(const char *origin_data_path,const char *item_path);

void
qsvr_find(struct quote_map* qm, uint32_t date , char *item , uint32_t rank , struct qsvr *ret_val );

void
qsvr_destroy(struct quote_map* qm);

uint32_t 
calculate_item_key(char *array );

uint32_t 
Is_Leap_year(uint32_t year );

uint32_t 
calculate_year_key( uint32_t date );

void
map_key(struct quote_map *map_val , uint32_t len );

void 
init_history_quote();









