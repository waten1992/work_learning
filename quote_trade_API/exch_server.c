/*
 * File Name: quote_trade_api.h
 *
 * Author: He Wen Guan
 *
 * Description:
 * 			exchange server receive client request 
 */

#include "def_quote_trade_struct.h"

#define MAX_QUOTE_READER 32
#define MAX_QUOTE_PROCESSOR 4

static int epl_fd;
static int listen_fd;
static struct epoll_event epl_event;
static int listen_port = 65530;

static int
set_nonblocking(int fd)
{
	int ret = 0;
	int opts = fcntl(fd, F_GETFL);
	if (opts < 0) {
		fprintf(stderr, "fcntl F_GETFL failed : %s\n", strerror(errno));
		goto err_exit;
	}

	opts = opts | O_NONBLOCK;

	ret = fcntl(fd, F_SETFL, opts);
	if (ret < 0) {
		fprintf(stderr, "fcntl F_SETFL failed : %s\n", strerror(errno));
		goto err_exit;
	}

	return 0;
err_exit:
	return -1;
}

static int
exchg_server_init(void)
{
	int ret = 0;
	struct sockaddr_in exchg_server_addr;

	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == listen_fd) {
		fprintf(stderr, "socket failed : %s\n", strerror(errno));
		goto err_exit;
	}

	/* set port reuse */
	int reuse = 1;
	ret = setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
	if (ret < 0) {
		fprintf(stderr, "setsockopt set reuse : %s\n", strerror(errno));
		goto err_exit;
	}

	// set nonblocking
	ret = set_nonblocking(listen_fd);
	if (ret != 0)
	{
		goto err_exit;
	}

	bzero(&exchg_server_addr, sizeof(exchg_server_addr));
    exchg_server_addr.sin_family = AF_INET;
    exchg_server_addr.sin_port = htons(listen_port);
    exchg_server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    ret = bind(listen_fd, (struct sockaddr*)&exchg_server_addr, sizeof(exchg_server_addr));
	if (ret < 0) {
		fprintf(stderr, "bind failed : %s\n", strerror(errno));
		goto err_exit;
	}

	ret = listen(listen_fd, MAX_QUOTE_READER);
	if (ret < 0) {
		fprintf(stderr, "listen failed : %s\n", strerror(errno));
		goto err_exit;
	}

	epl_event.data.fd = listen_fd;
	epl_event.events = EPOLLIN;
    ret = epoll_ctl(epl_fd, EPOLL_CTL_ADD, listen_fd, &epl_event);
	if (ret != 0) {
		fprintf(stderr, "epoll_ctl add failed : %s\n", strerror(errno));
		goto err_exit;
	}

	return 0;
err_exit:
	if (listen_fd > 0) {
		close(listen_fd);
	}
	return -1;
}


static int
accept_new_request(void)
{
	int ret = 0;
	int client_fd = -1;
	struct epoll_event one_event;
	struct sockaddr_in client_addr;
	socklen_t len = sizeof(struct sockaddr);

	client_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &len);
	if (client_fd <= 0) {
		fprintf(stderr, "accept failed : %s, listen_fd = %d\n", strerror(errno), listen_fd);
		goto err_exit;
	}

	fprintf(stderr, "<<<1>>> new connection from fd : %d\n", client_fd);
				
	set_nonblocking(client_fd);

	one_event.data.fd = client_fd;
	one_event.events = EPOLLIN | EPOLLRDHUP;
	ret = epoll_ctl(epl_fd, EPOLL_CTL_ADD, client_fd, &one_event);
	if (ret < 0) {	
		fprintf(stderr, "client_addr : epoll_ctl  failed : %s\n", strerror(errno));
		goto err_exit;
	}

	/*handle request */
	printf("receive form client !\n");
	return 0;

err_exit:
	if (client_fd > 0) {
		close(client_fd);
	}

	return -1;
}

static int
close_request_conn(int fd)
{
	int ret = 0;

	struct epoll_event one_event;
	ret = epoll_ctl(epl_fd, EPOLL_CTL_DEL, fd, &one_event);
	if (ret < 0)
	{
		fprintf(stderr, "epoll_ctl del failed : %s\n", strerror(errno));
		return -1;
	}

	close(fd);
	fprintf(stderr, "<<<4>>> Quote request finished, close connection to fd : %d\n", fd);

	return 0;
}
static int 
start_exchg_server(void)
{
	int ret = 0;
	int count = 0;
	struct epoll_event events[MAX_QUOTE_READER];

	// create epoll
	epl_fd = epoll_create(MAX_QUOTE_READER);
	if (epl_fd < 0) {
		fprintf(stderr, "epoll_ctl add failed : %s\n", strerror(errno));
		return -1;
	}

	// create listen fd, bind
	ret = exchg_server_init();
	if (ret != 0) {
		goto err_exit;
	}

	while (1) {
		int i = 0;
		count = epoll_wait(epl_fd, events, MAX_QUOTE_READER, -1);

		for (i = 0; i < count; i++) {
			int fd = events[i].data.fd;

			if (fd == listen_fd) {
				ret = accept_new_request();
			}
			else if ((events[i].events & EPOLLRDHUP) && (events[i].events & EPOLLIN)){
				ret = close_request_conn(fd);
			}
			else if (events[i].events & EPOLLIN) {
				ret = process_msg(fd);
			}
			else if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP)) {
				fprintf(stderr, "EPOLL ERROR!\n");
			}
		}
	}

err_exit:
	return -1;
}
