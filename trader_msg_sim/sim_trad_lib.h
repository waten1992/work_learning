#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>
#include <unistd.h>
#include <malloc.h>
#include <stdint.h>
#include <time.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>

#include "mi_type.h"
#include "trader_agent_protocol_frame.h"

#define SET_TAIL (0xff)
#define TAIL_LEN 1
#define RSP_LEN (sizeof(response_t))
#define LOG_RSP_LEN (sizeof(response_t)+TAIL_LEN)
#define STRA_RSP_LEN (sizeof(response_t) + sizeof(strategy_resp_t) +TAIL_LEN)
#define ORD_RSP_LEN (sizeof(response_t) + sizeof(order_resp_t) +TAIL_LEN)
#define POS_RSP_LEN (sizeof(response_t) + sizeof(position_resp_t) + TAIL_LEN)
#define CONTR_RSP_LEN (sizeof(response_t) + sizeof(contract_resp_t) + strlen("MY1512")+ 1 + TAIL_LEN)
#define BUF_SIZE 64

typedef struct trad_sim_cfg {
	unsigned int interval; /* base: ms */
	unsigned int tot_time; /* base : s */
	unsigned int exchg_type; /* reference mi_type.h */
}trad_sim_cfg_t;

typedef struct sim_trader{
	unsigned int interval;
	unsigned int tot_size;
	unsigned int exchg_type;	
}sim_trader_t;

typedef struct node {
	char contract[64];
}node_t;

typedef struct sim_trader  sim_trader_t;
typedef struct trad_sim_cfg trad_sim_cfg_t;

sim_trader_t *
sim_trader_init(trad_sim_cfg_t *cfg);

unsigned int 
sim_trader_size(sim_trader_t  *sim_data);

int 
sim_trader_start(sim_trader_t  *sim_data, int fd);

int 
sim_trader_destroy(sim_trader_t  *sim_data);