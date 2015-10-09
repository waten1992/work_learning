/*
 * File Name: quote_trade_api.h
 *
 * Author: He Wen Guan
 *
 * Description:
 * 			client request place_order cancel_order to exchange server api 
 *
 * */

#ifndef 	QUOTE_TRADE_API
#define 	QUOTE_TRADE_API

#ifdef _cplusplus
extern "C"
{
#endif

struct quo_tra_api;
struct tra_req_cfg;

struct quo_tra_api*
trade_request_init(struct tra_req_cfg*);

int
place_order(struct quo_tra_api*);

int 
cancel_order(struct quo_tra_api*);

int
trade_request_destroy(struct quo_tra_api*);

#ifdef _cplusplus
}
#endif

#endif
