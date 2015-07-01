#if !defined(__COMM_H__20150623__)
#define __COMM_H__20150623__
#include "header.h"

int comm_init();
void *create_server_sock(const char *src, int port);
void *create_client_sock(const char *target_ip, int target_port,
						 const char *identity);
int mq_msg_recv_poll(void *sock, rq_recv_callback handler);
int mq_msg_send(void *sock, char *buff, size_t buf_len);
void comm_destroy();

#endif
