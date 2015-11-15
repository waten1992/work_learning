/* Copyright(c) 2007-2015, by MY Capital Inc.
 */
#if !defined(_TRDER_AGENT_PROTOCOL_FRAME_H_1DC6AA5C_DD2C_44A4_B27E_7BF8EF9AB150)
#define _TRDER_AGENT_PROTOCOL_FRAME_H_1DC6AA5C_DD2C_44A4_B27E_7BF8EF9AB150

#include <stdint.h>
#include <time.h>

#if defined(_WINDOWS)
typedef struct timeval {
	long tv_sec;
	long tv_usec;
} timeval;
#endif

#define PROTOCOL_VERSION	"10"		/* Trader-Agent protocol version: V1.0 */
#define TRADER_CMD_SUCCESS	0
#define TRADER_CMD_UNKOWN	-1
#define END_IDENTIFIER		(uint8_t)0xFF

enum {
	M_CMD_E = 'E',		/* stop specific strategy */
	M_CMD_G = 'G',		/* retrieve specific strategy information. */
	M_CMD_L = 'L',		/* login command */
	M_CMD_P = 'P',		/* Pause specific strategy */
	M_CMD_S = 'S',		/* start strategy command */
	M_CMD_U = 'U',		/* Update specific strategy parameters. */
	M_CMD_C = 'C',		/* Download Configuration to trader. */
};

enum {
	M_RESP_S = 'S',		/* Strategy information response */
	M_RESP_O = 'O',		/* Order information response */
	M_RESP_P = 'P',		/* Position information response */
	M_RESP_C = 'C',		/* Contract information response */
	M_RESP_M = 'M',		/* Option market making monitor content.*/
};

#pragma pack(push)
#pragma pack(8)
typedef struct {
	uint16_t id;    /* TODO:check. */
	uint8_t cmd;
	uint32_t len;	/* TODO:check. */
	uint8_t data[0];
	/* uint8_t tail;			 TAIL= FFH */
} command_t;

typedef struct {
	uint16_t id;
	int8_t	type;
	uint32_t len;
	uint8_t data[0];
	/* uint8_t tail;			 TAIL= FFH */
} response_t;

/*
 * responds command 'S'
 */
typedef struct _strategy_resp {
	char name[16];
	char account[32];
	char user[32];
	char broker_id[32];
	uint32_t canceled;
	uint32_t orders;
	uint32_t status;
	/*
	 * all parameters in a string, and the delimiter is ','
	 */
	unsigned char param[0];
} strategy_resp_t;

/*
 * responds command 'O'.
 */
typedef struct _order_resp {
	struct timeval  update_time;	/* UTC time. */
	char st_name[16];
	char contract[64];
	char order_id[32];
	char broker_id[32];
	uint32_t status;
	uint32_t direct;	/* Buy/Sell. */
	uint32_t vol;
	double price;
	uint32_t instr;  	/* Instruction Type: FOK/IOC  */
	uint32_t type;
	double filled_price;
	char rejected_reason[40];
	char notes[0];
} order_resp_t;

/*
 * responds command 'P'
 */
typedef struct _position_resp {
	char account[32];
	char st_name[16];
	char contract[64];
	uint32_t buy_qty;
	uint32_t sell_qty;
	double avg_buy_price;
	double avg_sell_price;
} position_resp_t;

/*
 * This data structure is used to respond the command 'C' from OSS agent.
 */
typedef struct _contract_resp {
	char st_name[16];

	/*
	 * all the symbols in the string, the delimiter is ','. For example,
	 * if a strategy concerns contracts: IF1501, au1501, the string will
	 * be as: "IF1501,AU1501"
	 */
	char symbols[0];
} contract_resp_t;

#endif
