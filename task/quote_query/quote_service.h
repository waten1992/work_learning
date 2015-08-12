/*
 *	quote_service.h 
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
#define Type_size		5
#define Tmp_array_len 	64
#define Start_value		96
#define Days			7320
#define Start_day 		153
#define Item_num		43
#define Second_hash_index	86
# define HP_TIMING_NOW(Var) \
 ({ unsigned long long _hi, _lo; \
  asm volatile ("rdtsc" : "=a" (_lo), "=d" (_hi)); \
  (Var) = _hi << 32 | _lo; })


typedef unsigned int u32_int ;
typedef struct qsvr
{
	u32_int 	date ;
	char 		item[8];
	char 		contract[8];
	u32_int 	rank;
	char 		quote_record[24];
	char 		address[128];
	struct qsvr *next ; 
}qsvr_data;

struct quote_map;

struct quote_map*
qsvr_init(const char *path);

void
qsvr_find(struct quote_map* qm, u32_int date , char *item , u32_int rank , struct qsvr *ret_val );

void
qsvr_destroy(struct quote_map* qm);
