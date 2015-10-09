/*
 * File Name: quote_trade_api.c
 *
 * Author: He Wen Guan
 *
 * Description:
 * 			client request place_order cancel_order to exchange server api 
 */

#include "def_quote_trade_struct.h"

#define LOACL_PORT  9999

int
connect_exchange_server(struct tra_req_cfg *con_exchg_cfg)
{
	int ret = 0;
	int sock_fd = 0;
    struct sockaddr_in exchg_server_addr;
	struct sockaddr_in local_addr;
	struct timeval timeout;
	memset(&timeout, 0, sizeof(timeout));
	socklen_t t_len = sizeof(timeout);
	timeout.tv_sec = 10;	// timeout 10 seconds

    bzero(&local_addr,sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = htons(INADDR_ANY);
    local_addr.sin_port = htons(LOACL_PORT);

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd < 0) {
        fprintf(stderr, "socket failed : %s\n", strerror(errno));
        return -1;
    }

    ret = bind(sock_fd,(struct sockaddr*)&local_addr, sizeof(local_addr));
	if (ret < 0) {
        fprintf(stderr, "bind failed : %s\n", strerror(errno));
        goto err_exit;
    }
 
    bzero(&exchg_server_addr, sizeof(exchg_server_addr));
    exchg_server_addr.sin_family = AF_INET;
    if(inet_aton(con_exchg_cfg->exchg_ip, &exchg_server_addr.sin_addr) == 0) {
        fprintf(stderr, "Server IP Address Error : %s\n", con_exchg_cfg->exchg_ip);
        goto err_exit;
    }
    exchg_server_addr.sin_port = htons(con_exchg_cfg->exchg_port);
    socklen_t len = sizeof(exchg_server_addr);

	ret = setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(struct timeval));
	if(ret < 0) {
        fprintf(stderr, "Failed to do setsockopt, %s\n", strerror(errno));
        goto err_exit;
    }
	
	ret = connect(sock_fd, (struct sockaddr*)&exchg_server_addr, len);
    if(ret < 0) {
        fprintf(stderr, "Can Not Connect To %s!\n", con_exchg_cfg->exchg_ip);
        goto err_exit;
    }
	return sock_fd;
err_exit:
    close(sock_fd);
	return -1;	
}

struct quo_tra_api *
trade_request_init(struct tra_req_cfg *con_exchg_cfg)
{
	struct quo_tra_api *qt_api;
	qt_api = (struct quo_tra_api *)malloc(sizeof(struct quo_tra_api));
	int ret = connect_exchange_server(con_exchg_cfg);
	if (-1 == ret){
		fprintf(stderr,"Can't connect server!\n");
		return NULL;
	}
	qt_api->sock_fd = ret;
    qt_api->pla_ord_ret_fn = con_exchg_cfg->pla_ord_ret_fn;
    qt_api->canc_ord_ret_fn = con_exchg_cfg->canc_ord_ret_fn;

	return qt_api;
}

int 
place_order(struct quo_tra_api *qt_api)
{
    int ret = send(qt_api->sock_fd, qt_api->pl_info, sizeof(qt_api->pl_info), 0);
    if (-1 == ret ) {
        fprintf(stderr, "send qt_api->pl_info failed : %s\n", strerror(errno));
        goto err_exit;
    }

    ret = recv(qt_api->sock_fd, &qt_api->pla_ord_ret_fn, sizeof(qt_api->pla_ord_ret_fn), 0);
    if(-1 == ret) {
        fprintf(stderr, "recv failed from exchange server : %s, rcv_len = %d\n",strerror(errno), ret);
        goto err_exit;
    }

    return 0;
err_exit:
    close(qt_api->sock_fd);   
    return -1;
}

int 
cancel_order(struct quo_tra_api *qt_api)
{
    int ret = send(qt_api->sock_fd, qt_api->canc_info, sizeof(qt_api->canc_info), 0);
    if (-1 == ret ) {
        fprintf(stderr, "send qt_api->canc_info failed : %s\n", strerror(errno));
        goto err_exit;
    }

    ret = recv(qt_api->sock_fd, &qt_api->canc_ord_ret_fn, sizeof(qt_api->canc_ord_ret_fn), 0);
    if(-1 == ret) {
        fprintf(stderr, "recv failed from exchange server : %s, rcv_len = %d\n",strerror(errno), ret);
        goto err_exit;
    }

    return 0;
err_exit:
    close(qt_api->sock_fd);   
    return -1;
}

int 
pla_ord_ret(struct pla_ord_info *pl_ret)
{
    printf(" come from server pla_ord_ret \n");
    return 0;
}

int
canc_ord_ret(struct pla_ord_ret *pla_ret)
{
    printf(" come from server pla_ord_ret \n");
    return 0;
}

