#include <stdio.h>
#include <malloc.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#include "trader_agent_protocol_frame.h" 
#include "mi_type.h"

#define RECV_MSG_SIZE 4096
#define SEND_CFG_LEN (sizeof(command_t) + sizeof(trad_sim_cfg_t) + 1)
#define DEBUG 1
#define IP_LEN 32

typedef struct trad_sim_cfg {
    unsigned int interval; /* base: ms */
    unsigned int tot_time; /* base : s */
    unsigned int exchg_type; /* reference mi_type.h */
}trad_sim_cfg_t;

typedef struct tra_req_cfg {    
    char ip[IP_LEN];
    uint16_t port;
}tra_req_cfg_t;


void 
extract_stra_msg(response_t *recv_msg)
{
    strategy_resp_t *rsp;
    rsp = (strategy_resp_t *)recv_msg->data;
    
    printf("*****extract_stra_msg***** \n");
    
    printf("ID: %d , type :%c , len: %d  \n", 
            recv_msg->id,
            recv_msg->type,
            recv_msg->len);

    printf("Str_name: %s , account : %s , user : %s , broker_id: %s \n",
            rsp->name,
            rsp->account,
            rsp->user,
            rsp->broker_id);

    printf("***** strategy message finish ***** \n");
}

void 
extract_ord_msg(response_t *recv_msg)
{
    order_resp_t *rsp;
    rsp = (order_resp_t *)recv_msg->data;
    
    printf("*****extract_ord_msg***** \n");
    
    printf("ID: %d , type :%c , len: %d  \n", 
            recv_msg->id,
            recv_msg->type,
            recv_msg->len);

    printf("Str_name: %s , contract : %s , price : %s , broker_id: %s , vol : %d\n",
            rsp->st_name,
            rsp->contract,
            rsp->price,
            rsp->broker_id,
            rsp->vol);

    printf("***** order message finish ***** \n");
}


void 
extract_pos_msg(response_t *recv_msg)
{
    position_resp_t *rsp;
    rsp = (position_resp_t *)recv_msg->data;
    
    printf("*****extract_pos_msg***** \n");
    
    printf("ID: %d , type :%c , len: %d  \n", 
            recv_msg->id,
            recv_msg->type,
            recv_msg->len);

    printf("Str_name: %s , contract : %s , contract : %s , buy_qty : %d\n",
            rsp->st_name,
            rsp->contract,
            rsp->contract,
            rsp->buy_qty);

    printf("***** position message finish ***** \n");
}

void 
extract_contr_msg( response_t *recv_msg )
{
    contract_resp_t *rsp;
    rsp = (contract_resp_t *)recv_msg->data;

    printf("*****extract_contr_msg***** \n");
    
    printf("ID: %d , type :%c , len: %d  \n", 
            recv_msg->id,
            recv_msg->type,
            recv_msg->len);

      printf("Str_name: %s , account : %s \n",
            rsp->st_name,
            rsp->symbols);

    printf("***** contract  message finish ***** \n");

}


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
    timeout.tv_sec = 10;    // timeout 10 seconds

    bzero(&local_addr,sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    if(inet_aton(con_exchg_cfg->exchg_ip, &local_addr.sin_addr) == 0) {
        fprintf(stderr, "Local IP Address Error  %s\n", con_exchg_cfg->exchg_ip);
        goto err_exit;
    }
    local_addr.sin_port = htons(0);

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd < 0) {
        fprintf(stderr, "socket failed : %s\n", strerror(errno));
        return -1;
    }
    
    /* set port reuse */
    int reuse = 1;
    ret = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    if (-1 == ret ) {
        fprintf(stderr, "setsockopt set reuse : %s\n", strerror(errno));
        goto err_exit;
    }

    ret = bind(sock_fd,(struct sockaddr*)&local_addr, sizeof(local_addr));
    if (-1 == ret ) {
        fprintf(stderr, "client bind failed : %s\n", strerror(errno));
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
    if(-1 == ret ) {
        fprintf(stderr, "Failed to do setsockopt, %s\n", strerror(errno));
        goto err_exit;
    }
    
    ret = connect(sock_fd, (struct sockaddr*)&exchg_server_addr, len);
    if(-1 == ret ) {
        fprintf(stderr, "Can Not Connect To %s!\n", con_exchg_cfg->exchg_ip);
        goto err_exit;
    }

    return sock_fd;
err_exit:
    close(sock_fd);
    return -1;  
}




/* arguments : local_ip local_port remote_ip remote_port */
int main(int argc, char *argv[])
{
    /* demo with tcpv4, don't check the arguments */
    char *ip_r = argv[1];      /* server ip */
    char *port_r = argv[2];    /* server port */

    int fd ;
    tra_req_cfg_t con_cfg;
    strncpy(con_cfg.ip, port_r, IP_LEN);
    con_cfg.port = atoi(port_r);

    fd = connect_exchange_server(&con_cfg);

    command_t *send_msg ;
    send_msg = (command_t *)calloc(1, SEND_CFG_LEN);
    if (NULL == send_msg) {
        printf("send_msg calloc is failed \n");
        return -1;
    }
    
    response_t recv_msg;
    trad_sim_cfg_t  *cfg;
    cfg = (trad_sim_cfg_t *)send_msg->data;
    
    send_msg->id = 1992 ; 
    send_msg->cmd = M_CMD_S;
    send_msg->len = sizeof(trad_sim_cfg_t) + 1;
    
    cfg->interval = 500;
    cfg->tot_time = 1;
    cfg->exchg_type = MI_CFEX_DEEP;
    
    if (send(fd, send_msg, SEND_CFG_LEN, 0) == -1 ) {
        printf("SEND O_NONBLOCK mode IS ERROR, errno number: %d\n",errno);
    }
    printf(" send success ! \n");

    while (1) {
        int ret = recv(fd, &recv_msg, RECV_MSG_SIZE, 0);
        if (-1 == ret ) {
                fprintf(stderr, "client recv data failed : %s\n", strerror(errno));
                goto err_exit;
        } 
        else if ( recv_msg.type == 0 ) {
                printf(" %d , %d , %d \n", 
                        recv_msg.id,
                        recv_msg.type,
                        recv_msg.len);
        } else {
                int type = recv_msg.type ;
                switch(type) {
                    case M_RESP_S:
                        extract_stra_msg(&recv_msg);
                        break;
                    case M_RESP_O:
                        extract_ord_msg(&recv_msg);
                        break;
                    case M_RESP_P:
                        extract_pos_msg(&recv_msg);
                        break;
                    case M_RESP_C:
                        extract_contr_msg(&recv_msg);
                        break;
                    default:
                        printf(" CMD type  is  error \n");
                } 
        }
    }
    
    close(fd);
    return 0 ;

err_exit:
    close(fd);
    return -1;
}