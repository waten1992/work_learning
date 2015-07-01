#if !defined(__CODER_H__0624__)
#define __CODER_H__0624__

#include "header.h"
#include "rq_fast.h"


#pragma pack(push)
#pragma pack(8)
struct file_header {
	int32_t item_qt;
	int16_t data_flag;
	int16_t item_len;
};

#pragma pack(pop)


int encode_quote(int quote_type, void *quote, size_t quote_len,
				 void *out, size_t *out_len);

int decode_quote(const char *fast_buff, size_t buff_len,
				 rq_recv_callback  on_quote_recv);


#endif
