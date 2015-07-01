#include <header.h>
#include <unistd.h>
//under test sources
#include <comm.h>
#include <coder.h>

int test_send()
{
	printf("start send\n");
	int ret;
	ret = comm_init();
	if(ret <0) {
		printf("error to init comm\n");
		return -1;
	}
	//
	char target_ip[]="127.0.0.1";
	char identity[]="client";
	void *sock=create_client_sock(target_ip, 10000, identity);
	if(!sock) {
		printf("error to create client sock\n");
		return -1;
	}
	//
	char msg[128];
	int i;
	for(i=0; i<100; ++i) {
		snprintf(msg, sizeof(msg),"I am from client %d \n\n",i);
		ret = mq_msg_send(sock, msg, strlen(msg));
		if(ret <0) {
			printf("error to send msg\n");
			return -1;
		}
		usleep(5e5);
	}
	printf("start finished\n");
	comm_destroy();
	getchar();
	return 0;
}

int decode_quote_cffexl2(void *quote_struct, size_t quote_struct_size)
{
	struct rq_raw_quote_t *decoded = (struct rq_raw_quote_t *)quote_struct;
	printf("decoded eps=%ld\n", decoded->epoch_us);
	return 0;
}

int decode_quote_l1(void *quote_struct, size_t quote_struct_size)
{
	struct rq_raw_quote_t *decoded = (struct rq_raw_quote_t *)quote_struct;
	printf("decoded eps=%ld\n", decoded->epoch_us);
	return 0;
}

void test_cffexl2_ende(struct rq_raw_quote_t *data)
{
	//	printf("Enter %s\n", __FUNCTION__);
	int ret;
	char fast_buff[1024];
	bzero(fast_buff, sizeof(fast_buff));
	size_t fast_buff_len=sizeof(fast_buff);
	ret =  encode_quote(GTA_UDP_CFFEX_QUOTE_TYPE,
						(void *)data, sizeof(*data),
						(void *)fast_buff, &fast_buff_len);
	if(ret< 0) {
		printf("encode errro\n");
	}
	set_decode_callback(GTA_UDP_CFFEX_QUOTE_TYPE,
						decode_quote_cffexl2);
	decode_quote(fast_buff, sizeof(fast_buff));
	if(ret< 0) {
		printf("decode errro\n");
	}
}

void test_level1_ende(struct rq_raw_quote_t *data)
{
	//	printf("Enter %s\n", __FUNCTION__);
	int ret;
	char fast_buff[1024];
	bzero(fast_buff, sizeof(fast_buff));
	size_t fast_buff_len=sizeof(fast_buff);
	ret =  encode_quote(SHFE_EX_QUOTE_TYPE,
						(void *)data, sizeof(*data),
						(void *)fast_buff, &fast_buff_len);
	if(ret< 0) {
		printf("encode errro\n");
	}
	//set_decode_callback(GTA_UDP_CFFEX_QUOTE_TYPE,
	//			decode_quote_cffexl2);
	decode_quote(fast_buff, sizeof(fast_buff));
	if(ret< 0) {
		printf("decode errro\n");
	}
}

int test_ende()
{
#define DATA_FILE "cffex_level2_gta_tcp_20150601.dat"
	printf("Enter %s\n", __FUNCTION__);
	const char *file_name=DATA_FILE;
	/*
	 * inital read with libc/fxxx
	 * later can be replaced with mmap.
	 * */
	FILE *fbin=fopen(file_name, "r+");
	if(!fbin) {
		printf("error to open %s\n", file_name);
		return -1;
	}
	/* read header */
	ssize_t nread;
	struct file_header head;
	nread=fread(&head, sizeof(head),1, fbin);
	if((ssize_t)nread <0) {
		printf("error to read header\n");
		return -1;
	}
	//print_header(&head);
	//getchar();
	//TEST: add callback
	set_decode_callback(SHFE_EX_QUOTE_TYPE,
						decode_quote_l1);
	/* loop read items.*/
	int i;
	struct rq_raw_quote_t item;
	for(i=0; i<head.item_qt; ++i) {
		nread =fread(&item,sizeof(item), 1,fbin);
		if(nread <= 0) {
			if(nread ==0) {
				printf("reach to fiel end.\n");
			} else {
				printf("error to read item %d.\n", i);
				return -1;
			}
		}
		printf("original eps=%ld ", item.epoch_us);
		//test_cffexl2_ende(&item);
		test_level1_ende(&item);
		/*
		   std::vector<char> buffer;
		   buffer.reserve(2048);

		   int len= encode_cffexl2_with_fast(message, &item, buffer);

		   decode_cffexl2_with_fast(&buffer[0],len,&item_fast);
		   */
	}
	return 0;
}




int main(void)
{
	test_ende();
	return 0;
}
