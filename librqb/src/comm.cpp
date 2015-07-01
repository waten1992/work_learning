#include "header.h"
#include "utils.h"
#include "coder.h"

static void *zmq_ctx;
static void *server_sock;
static void *client_sock;

int comm_init()
{
	static bool s_binit=false;
	if(s_binit) {
		char err[]="zmq context should only be initialized once";
		set_error(err);
		return FAILURE;
	}
	zmq_ctx = zmq_ctx_new();
	s_binit=true;
	return 0;
}

/*  src: bind to a ip address or an endpoint.
 *
 */
void *create_server_sock(const char *src, int port)
{
	char buff[128];
	bzero(buff, sizeof(buff));
	server_sock = zmq_socket(zmq_ctx, ZMQ_ROUTER);
	if(!server_sock) {
		set_error("create server sock failed:%s\n",zmq_strerror(zmq_errno()));
		return NULL;
	}
	snprintf(buff,sizeof(buff), "tcp://%s:%d", src, port);
	set_debug("listen on %s\n", buff);
	if(FAILURE ==  zmq_bind(server_sock, buff)) {
		set_error("bind %s error:%s\n",buff, zmq_strerror(zmq_errno()));
		return NULL;
	}
	return server_sock;
}


void *create_client_sock(const char *target_ip, int target_port,
						 const char *identity)
{
	if(!target_ip || !identity) {
		set_error("error parameters to create client socket\n");
		return NULL;
	}
	assert(zmq_ctx);
	client_sock = zmq_socket(zmq_ctx, ZMQ_DEALER);
	assert(client_sock);
	if(!client_sock) {
		set_error("error to create DEALER socket:%s\n", zmq_strerror(zmq_errno()));
		return NULL;
	}
	zmq_setsockopt(client_sock,ZMQ_IDENTITY,identity, strlen(identity));
	char buff[128];
	bzero(buff, sizeof(buff));
	snprintf(buff,sizeof(buff), "tcp://%s:%d", target_ip, target_port);
	if(FAILURE ==  zmq_connect(client_sock, buff)) {
		set_error("error to connect %s:%s\n",buff, zmq_strerror(zmq_errno()));
		return NULL;
	}
	set_debug("connected to %s", buff);
	return client_sock;
}

int mq_msg_recv_poll(void *sock, rq_recv_callback handler)
{
	assert(sock);
	zmq_pollitem_t items[]= {
		{sock,0,ZMQ_POLLIN,0},
	};
	zmq_msg_t msg_identity,msg_content;
	int len, time_out=500;		//milli-seconds.
	while(1) {
		zmq_poll(items, 1, time_out);
		if(items[0].revents& ZMQ_POLLIN) {
			//handledealer identity.
			zmq_msg_init(&msg_identity);
			len =zmq_msg_recv(&msg_identity, sock, ZMQ_DONTWAIT);
			//TODO: debug
			//debug_print_id(&msg_identity);
			if(len !=FAILURE) {
				//handle recveived msg
				if(zmq_msg_more(&msg_identity)) {
					zmq_msg_init(&msg_content);
					len =zmq_msg_recv(&msg_content, sock, ZMQ_DONTWAIT);
					if(len !=FAILURE) {
						//handle call back.
						decode_quote((const char *)zmq_msg_data(&msg_content),
									 zmq_msg_size(&msg_content),
									 handler);
					} else if(errno !=EAGAIN) {
						set_error("zmq_msg recv error :%s\n",zmq_strerror(zmq_errno()));
					}
					zmq_msg_close(&msg_content);
				}
			} else if(errno!=EAGAIN) {
				set_error(zmq_strerror(zmq_errno()));
			}
			zmq_msg_close(&msg_identity);
		}
	}
	return 0;
}


int mq_msg_send(void *sock, char *buff, size_t buf_len)
{
	zmq_msg_t msg;
	zmq_msg_init_size(&msg, buf_len);
	memcpy(zmq_msg_data(&msg), buff, buf_len);
	int ret;
	ret = zmq_msg_send(&msg, sock, ZMQ_DONTWAIT);
	if(FAILURE == ret) {
		set_error(zmq_strerror(zmq_errno()));
		return FAILURE;
	}
	zmq_msg_close(&msg);
	return 0;
}

/* ZMQ_ROUTER: server side
 *    sock = zmq_socket(ctx, ZMQ_ROUTER)
 *    zmq_bind(sock, "tcp:/_/_*:port")
 *
 * # receive  poll ###
 * zmq_pollitem_t items[]=
 * {
 *	{sock,0,ZMQ_POLLIN,0},
 * }
 *
 * zmq_poll(item, 1, timeout)
 *  if(items[i].revents& ZMQ_POLLIN)
 *    zmq_msg_init()
 *    zmq_msg_send(&msg, sock, ZMQ_DONTWAIT)
 *    zmq_msg_close(&msg)
 * # send ###
 *  zmq_msg_init()
 *  zmq_msg_recv(&msg, sock, ZMQ_DONTWAIT)
 *  zmq_msg_close(&msg)
 *
 *
 * =====================================
 * ZMQ_DEALER: client side
 * setup procedure:
 *  sock= zmq_socket(ctx, ZMQ_DEALER);
 *  zmq_setsockopt(sock,ZMQ_IDENTITY, data,size);
 *  ret = zmq_connect(sock, "dest")
 *
 *
 * # DATA
 * =====================================
 * zmq_msg_data(&msg)
 * zmq_msg_size(&msg)
 *
 *
 *
 * # ERROR
 *  zmq_strerror( zmq_errno)
 *  zmq_errno()
 *
 * # OTHER API
 * zmq_msg_more
zmq_ctx()
zmq_poll
zmq_msg_recv
zmq_int
zmq_socket
zmq_connect
 */
/*void comm_listen(char *addr, int port )
{
	//void * sock= zmq_socket(zmq_ctx, ZMQ_ROUTER);

	//int ret = zmq_bind(sock, "");

}

*/

void comm_destroy()
{
	assert(zmq_ctx);
	if(zmq_ctx) {
		zmq_ctx_destroy(zmq_ctx);
	}
}






