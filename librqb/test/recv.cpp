#include <header.h>
#include <comm.h>

int do_msg(void *buff, size_t buff_len)
{
	printf("received[%ld]: %s",buff_len, (char *)buff);
	return 0;
}

int main()
{
	printf("start receive\n");
	int ret;
	ret = comm_init();
	if(ret <0) {
		printf("error to init comm\n");
		return -1;
	}
	//
	char src_ip[]="127.0.0.1";
	void *sock=create_server_sock(src_ip, 10000);
	if(!sock) {
		printf("error to create client sock\n");
		return -1;
	}
	//
	mq_msg_recv_poll(sock, do_msg);
	comm_destroy();
	getchar();
	return 0;
}
