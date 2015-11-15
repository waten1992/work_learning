#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <errno.h>
#include <syslog.h>

#include "trader_agent_protocol_frame.h"
#include "sim_trad_lib.h"
#include "mi_type.h"

#define MAX_CONNECTION 128
#define MSG_BUF_SIZE 4096
#define LISTEN_PORT 8888


struct epoll_event s_events[MAX_CONNECTION];

static
int epl_fd;

static int
accept_new_connection(int listen_fd)
{
	int ret = 0;
	int opts;
	int client_fd = -1;
	struct epoll_event one_event;
	struct sockaddr_in client_addr;
	socklen_t len = sizeof(struct sockaddr);

	client_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &len);
	if (client_fd <= 0) {
		syslog(LOG_ERR, "accept failed : %s, listen_fd = %d\n", strerror(errno), listen_fd);
		goto err_exit;
	}
	syslog(LOG_INFO, "accept fd %d from %s\n", client_fd, inet_ntoa(client_addr.sin_addr));
	
	/* set nonblocking */
	opts = fcntl(listen_fd, F_GETFL);
	if (opts < 0) {
		syslog(LOG_ERR, "fcntl F_GETFL failed : %s\n", strerror(errno));
		goto err_exit;
	}

	opts = opts | O_NONBLOCK;

	ret = fcntl(listen_fd, F_SETFL, opts);
	if (ret < 0) {
		syslog(LOG_ERR, "fcntl F_SETFL failed : %s\n", strerror(errno));
		goto err_exit;
	}

	one_event.data.fd = client_fd;
	one_event.events = EPOLLIN | EPOLLRDHUP;
	ret = epoll_ctl(epl_fd, EPOLL_CTL_ADD, client_fd, &one_event);
	if (ret < 0) {
		syslog(LOG_ERR, "client_addr : epoll_ctl  failed : %s\n", strerror(errno));
		goto err_exit;
	}

	return 0;
err_exit:
	if (client_fd > 0) {
		close(client_fd);
	}

	return -1;
}

response_t *
constr_send_rsp(command_t * recv_data)
{
	response_t *login_rsp;
	login_rsp = calloc(1,sizeof(response_t)+1);
	if (login_rsp == NULL) {
		syslog(LOG_ERR, "login_rsp calloc is failed !\n");
		return NULL;
	}
	login_rsp->id = recv_data->id;
	login_rsp->type = 0;
	login_rsp->len = 0;
	login_rsp->data[0] |=  0xff;
	
	return login_rsp;
}

int  
receive_data (int fd)
{
	char buf[MSG_BUF_SIZE];
	int ret = 0;
	while (1) {
		ret = recv(fd, buf, MSG_BUF_SIZE, 0);
		if ((-1 == ret) && (errno == EWOULDBLOCK || errno == EAGAIN)) {
				continue;
		} 
		else if(-1 == ret) {
			syslog(LOG_ERR, "recv error is failed ! : %s\n" , strerror(errno));
			goto err_exit;
		}
		break;
	}

	command_t *recv_data;
	recv_data = (command_t *)buf;
	printf("CMD : %c \n", recv_data->cmd );
	if (recv_data->cmd == M_CMD_L) {
		
		response_t *login_rsp;
		login_rsp = constr_send_rsp(recv_data);
		if (login_rsp == NULL) {
			syslog(LOG_ERR, "constr_send_rsp() is failed !\n");
			return -1;
		}
		
		ret = send(fd, login_rsp, LOG_RSP_LEN, 0);
		if (ret == -1) {
			syslog(LOG_ERR, "send() login_rsp  is failed !\n");
			return -1;
		}
		free(login_rsp);
	} 
	else if (recv_data->cmd == M_CMD_S) {
		//parser cfg data ,call funtion
		sim_trader_t *sim_data;
		trad_sim_cfg_t *cfg;
		cfg = (trad_sim_cfg_t *)recv_data->data;
		
		sim_data = sim_trader_init(cfg);
		if (sim_data == NULL) {
			syslog(LOG_ERR,"sim_trader_init() IS failed \n");
			return -1;
		}
		int size = sim_trader_size(sim_data);
		ret = sim_trader_start(sim_data, fd);
		if (ret == -1) {
			syslog(LOG_ERR,"sim_trader_start() IS failed \n");
			return -1;
		}
		sim_trader_destroy(sim_data);
	} 
	else {
		syslog(LOG_ERR , "unexpected cmd %c  , ID : %d , len : %d \n", 
				recv_data->cmd,
				recv_data->id,
				recv_data->len);
		return -1;
	}

err_exit:
	if (fd > 0) {
		close(fd);
		syslog(LOG_ERR, " recv_data()  fd  is close ! \n");
	}
	return -1;	
}

static int
close_connection(int fd)
{
	int ret = 0;
	struct epoll_event one_event;

	ret = epoll_ctl(epl_fd, EPOLL_CTL_DEL, fd, &one_event);
	if (ret < 0) {
		syslog(LOG_ERR, "epoll_ctl del failed : %s\n", strerror(errno));
		//return -1;
	}

	close(fd);
	syslog(LOG_INFO, "close fd : %d\n", fd);

	return 0;

err_exit:
	return -1;
}


static void
start_epoll(void)
{
	int ret;
	int count;
	int reuse = -1;	
	int opts;
	struct epoll_event new_event;
	struct sockaddr_in listen_addr;
	int listen_fd;

	epl_fd = epoll_create(MAX_CONNECTION);
	if (epl_fd < 0) {
		return;
	}

	/* listen */
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == listen_fd) {
		syslog(LOG_ERR, "socket failed : %s\n", strerror(errno));
		goto err_exit;
	}

	/* set port reuse */
	ret = setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
	if (ret < 0) {
		syslog(LOG_ERR, "setsockopt set reuse : %s\n", strerror(errno));
		goto err_exit;
	}

	/* set nonblocking */
	opts = fcntl(listen_fd, F_GETFL);
	if (opts < 0) {
		syslog(LOG_ERR, "fcntl F_GETFL failed : %s\n", strerror(errno));
		goto err_exit;
	}

	opts = opts | O_NONBLOCK;

	ret = fcntl(listen_fd, F_SETFL, opts);
	if (ret < 0) {
		syslog(LOG_ERR, "fcntl F_SETFL failed : %s\n", strerror(errno));
		goto err_exit;
	}

	/* bind */
	bzero(&listen_addr, sizeof(listen_addr));
	listen_addr.sin_family = AF_INET;
	listen_addr.sin_port = htons(LISTEN_PORT);
	listen_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ret = bind(listen_fd, (struct sockaddr*)&listen_addr, sizeof(listen_addr));
	if (ret < 0) {
		syslog(LOG_ERR, "bind failed : %s\n", strerror(errno));
		goto err_exit;
	}

	/* listen */
	ret = listen(listen_fd, MAX_CONNECTION);
	if (ret < 0) {
		syslog(LOG_ERR, "listen failed : %s\n", strerror(errno));
		goto err_exit;
	}

	/* add epoll event */
	new_event.data.fd = listen_fd;
	new_event.events = EPOLLIN;
	ret = epoll_ctl(epl_fd, EPOLL_CTL_ADD, listen_fd, &new_event);
	if (ret != 0) {
		syslog(LOG_ERR, "epoll_ctl add failed : %s\n", strerror(errno));
		goto err_exit;
	}

	/* start waiting for event */
	while (1) {
		int i;
		count = epoll_wait(epl_fd, s_events, MAX_CONNECTION, -1);

		for (i = 0; i < count; i++) {
			const int cur_fd = s_events[i].data.fd;

			/* new connection, from trader or controller, or bad guy... */
			if (cur_fd == listen_fd) {
				ret = accept_new_connection(listen_fd);
			}
			else {
				/* close the connection */
				if ((s_events[i].events & EPOLLRDHUP) && (s_events[i].events & EPOLLIN)) {
					ret = close_connection(cur_fd);
				}
				/* incoming data */
				else if (s_events[i].events & EPOLLIN) {
					ret = receive_data(cur_fd);
				}
				/* epoll error */
				else if ((s_events[i].events & EPOLLERR) || (s_events[i].events & EPOLLHUP)) {
					syslog(LOG_ERR, "epoll error!\n");
				}
			}
		}
	}

	return;
err_exit:
	return;
}

int main(int argc, char* argv[])
{
	/* create epoll, waiting for connection */
	start_epoll();
	return 0;
}