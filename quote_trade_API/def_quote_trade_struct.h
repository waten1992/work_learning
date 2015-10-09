/*
 ** File Name: def_quote_trade_struct.h
 **
 ** Author: He Wen Guan
 **
 ** Description:
 **          define the struct of quote_trade_api.c 
 **
 ** */

#ifndef     DEF_QUOTE_TRADE_STRUCT_H
#define     DEF_QUOTE_TRADE_STRUCT_H

#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>
#include <syslog.h>
#include <fcntl.h>
#include <time.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define IP_LEN	32
#define CONTR_LEN 32

struct pla_ord_ret ;
struct canc_ord_ret ;

typedef int (*pla_ret_fn_t)(struct pla_ord_ret *pla_ret);
typedef int (*canc_ret_fn_t)(struct canc_ord_ret *canc_ret);

typedef struct quo_tra_api {
	int sock_fd;
	struct pla_ord_info *pl_info;
	struct canc_ord_info *canc_info;	
	pla_ret_fn_t pla_ord_ret_fn;
	canc_ret_fn_t canc_ord_ret_fn;
}quo_tra_api_t;

typedef struct tra_req_cfg {	
	char exchg_ip[IP_LEN];
	uint16_t exchg_port;
	pla_ret_fn_t pla_ord_ret_fn;
	canc_ret_fn_t canc_ord_ret_fn;
}tra_req_cfg_t;

typedef struct pla_ord_info {
 	int 	user_id;
	char 	contr[CONTR_LEN];
	double 	price;
	uint32_t volume;
	char 	direction;
}pla_ord_info_t;

typedef struct canc_ord_info {
	int 	user_id;
	char 	contr[CONTR_LEN];
	double	limit_price;
	int64_t org_serial_no;
	char 	direction;
}canc_ord_info_t;

typedef struct canc_ord_ret {
	char 		dog_tag; /* '0' ->pla_ord_ret , '1'->canc_ord_ret  */
	char 		entrust_status;
	int64_t 	serial_no;
	int64_t 	entrust_no;
	int 		error_no;
}canc_ord_ret_t;

typedef struct pla_ord_ret {
	char 	dog_tag; /* '0' ->pla_ord_ret , '1'->canc_ord_ret  */
	char    direction;
	char    entrust_status;
	int64_t serial_no;
	char 	contr[CONTR_LEN];
	int64_t entrust_no;
	int64_t volume;
	double  limit_price;
}pla_ord_ret_t;

typedef struct ord_ret_info {
	pla_ord_ret_t 	pl_ret;
	canc_ord_ret_t	cl_ret;
}ord_ret_info_t;

int connect_exchange_server();

#endif
