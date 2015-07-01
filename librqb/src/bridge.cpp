#include "header.h"
#include "utils.h"
#include "comm.h"
#include "coder.h"
#include "../bridge.h"

#define FAST_ENCODE_BUFF_SIZE (4096)
static void *s_client_sock;
static void *s_server_sock;
static char s_fast_buff[FAST_ENCODE_BUFF_SIZE];

/*
 * 创建rss行情分发服务
 * 行情分发端(client)接口
 * @para target_ip:行情接收程序的目标IP
 * @para target_port:行情接收程序的目标端口
 * @para identity 标识发送端的身份，发送端的id必须唯一
 */
int connect_rq_receiver(char *target_ip, int target_port, char *identity)
{
	int ret=0;
	if(s_client_sock !=0 ||
	   s_server_sock !=0) {
		set_error("communication port has been initialized.\n");
		return -1;
	}
	ret= comm_init();
	if(ret <0) {
		set_error("error to init comm\n");
		return ret;
	}
	s_client_sock = create_client_sock(target_ip, 
			target_port,identity);
	if(s_client_sock == 0) {
		set_error("error to create client socket.\n");
		return -1;
	}
	return ret;
}
/*
 * 分发RSS行情
 * 行情分发端接口
 * @parm quote_type 行情类型
 * @parm data 行情内容缓冲区
 * @parm data_size 行情内容缓冲区大小
 */
int publish_rq(int quote_type, void *data, size_t data_size)
{
	int ret=0;
	size_t fast_buff_size=sizeof(s_fast_buff);
	ret = encode_quote(quote_type, data, data_size,
					   s_fast_buff, &fast_buff_size);
	if(ret <0) {
		set_error("error to encode quote type=%d\n",quote_type);
		return -1;
	}

	assert(s_client_sock);
	ret = mq_msg_send(s_client_sock, s_fast_buff, fast_buff_size);
	if(ret <0) {
		set_error("error to send quote by message quote ,type=%d,length=%ld\n",
				  quote_type,  fast_buff_size);
		return -1;
	}
	return ret;
}


/*
 * 连接到RSS行情服务程序
 * 行情接收端端(server)接口
 * @para src ：可指定绑定的IP地址或端口，如 "192.168.1.100" 或 "eth0"
 * @para port: 服务监听的端口号
 * @parm data_size 行情内容缓冲区大小
 */
int create_rq_receiver(char *src, int port)
{
	int ret=0;
	ret = comm_init();
	if(ret < 0) {
		set_error("error to init message queue\n");
		return -1;
	}
	s_server_sock = create_server_sock(src, port);
	if(s_server_sock == 0) {
		set_error("error to create server message queue socket\n");
		return -1;
	}
	return ret;
}

/*
 * 行情接收轮询
 * 行情接收端端接口 ,
 * NOTE: 该轮询为阻塞方式，暂未提供停止接口，有需要再加上;
 * @parm rq_recv_callback 为行情接收回调接口;
	 * quote_type 行情类型
	 * @parm data 行情内容缓冲区指针
	 * @parm data_size 行情内容缓冲区大小
 */
void recv_rq_poll(rq_recv_callback callback)
{
	assert(callback);
	mq_msg_recv_poll(s_server_sock, callback);
}

/*
 * 关闭rss行情连接
 * 行情分发端/接收端接口
 */
void close_rq()
{
	comm_destroy();
}

