/*
 * File Name: client.c
 *
 * Author: He Wen Guan
 *
 * Description:
 * 			client request place_order and cancel_order to exchange server 
 */

#include "def_quote_trade_struct.h"

#define SERVER_PORT 65530

int 
main()
{
	struct tra_req_cfg con_exchg_cfg[1];
	char *server_ip = "127.0.0.5"; 
	memcpy(con_exchg_cfg[0].exchg_ip,server_ip,IP_LEN);
	con_exchg_cfg[0].exchg_port = SERVER_PORT;
	
	struct quo_tra_api *qt_api;
	qt_api = trade_request_init(&con_exchg_cfg[0]);
	if (NULL == qt_api ) {
        fprintf(stderr, "trade_request_init() is fail\n");
        return -1;
    }

    int ret = place_order(qt_api);
    if (-1 == ret ) {
        fprintf(stderr, "place_order() is fail\n");
        return -1;
    }

	return 0;
}
