#include "header.h"
#include "utils.h"
#include "coder.h"
#include "rq_fast.h"


using namespace mfast;
using namespace rq_fast;

/* static tempalte message instances.
 * NOTE: these instance only init once.
 */
static rq_fast::cffexl2 cffexl2_message;
static rq_fast::level1 s_l1_msg;

int encode_cffex_l2(void *buff,void *out, size_t *out_len)
{
	int32_t  cffexl2_proto_ver=1;
	struct rq_raw_quote_t *in
		= (struct rq_raw_quote_t *)buff;
	cffexl2_mref ref = cffexl2_message.mref();
	ref.set_protocol_ver().as((int32_t)cffexl2_proto_ver);
	ref.set_timestamp().as((uint64_t)in->epoch_us);
	ref.set_trading_day().as(in->cffexl2_data.szTradingDay);
	ref.set_settlement_GID().as(in->cffexl2_data.szSettlementGroupID);
	ref.set_settlement_ID().as(in->cffexl2_data.nSettlementID);
	ref.set_last_price().as(in->cffexl2_data.dLastPrice);
	ref.set_pre_settlement_price().as(in->cffexl2_data.dPreSettlementPrice);
	ref.set_pre_close_price().as(in->cffexl2_data.dPreClosePrice);
	ref.set_pre_open_interest().as(in->cffexl2_data.dPreOpenInterest);
	ref.set_open_price().as(in->cffexl2_data.dOpenPrice);
	ref.set_highest_price().as(in->cffexl2_data.dHighestPrice);
	ref.set_lowest_price().as(in->cffexl2_data.dLowestPrice);
	ref.set_total_volume().as(in->cffexl2_data.nVolume);
	ref.set_total_turnover().as(in->cffexl2_data.dTurnover);
	ref.set_open_interest().as(in->cffexl2_data.dOpenInterest);
	ref.set_close_price().as(in->cffexl2_data.dClosePrice);
	ref.set_settlement_price().as(in->cffexl2_data.dSettlementPrice);
	ref.set_upper_limit_price().as(in->cffexl2_data.dUpperLimitPrice);
	ref.set_lower_limit_price().as(in->cffexl2_data.dLowerLimitPrice);
	ref.set_pre_delta().as(in->cffexl2_data.dPreDelta);
	ref.set_cur_delta().as(in->cffexl2_data.dCurrDelta);
	ref.set_update_time().as(in->cffexl2_data.szUpdateTime);
	ref.set_update_ms().as(in->cffexl2_data.nUpdateMillisec);
	ref.set_instrument_id().as(in->cffexl2_data.szInstrumentID);
	ref.set_bid_ask_pvs().resize(10);
	double prices[10] = {in->cffexl2_data.dBidPrice1, in->cffexl2_data.dAskPrice1,
						 in->cffexl2_data.dBidPrice2, in->cffexl2_data.dAskPrice2,
						 in->cffexl2_data.dBidPrice3, in->cffexl2_data.dAskPrice3,
						 in->cffexl2_data.dBidPrice4, in->cffexl2_data.dAskPrice4,
						 in->cffexl2_data.dBidPrice5, in->cffexl2_data.dAskPrice5,
						};
	int volumes[10]= { in->cffexl2_data.nBidVolume1, in->cffexl2_data.nAskVolume1,
					   in->cffexl2_data.nBidVolume2, in->cffexl2_data.nAskVolume2,
					   in->cffexl2_data.nBidVolume3, in->cffexl2_data.nAskVolume3,
					   in->cffexl2_data.nBidVolume4, in->cffexl2_data.nAskVolume4,
					   in->cffexl2_data.nBidVolume5, in->cffexl2_data.nAskVolume5,
					 };
	for(int i=0; i<10; ++i) {
		cffexl2_mref::bid_ask_pvs_element_mref  pv(ref.set_bid_ask_pvs()[i]);
		pv.set_level_price().as(prices[i]);
		pv.set_level_vol().as(volumes[i]);
	}
	const mfast::templates_description *descriptions[] =
	{ rq_fast::description() };
	size_t ret_len;
	mfast::fast_encoder encoder;
	encoder.include(descriptions);
	ret_len = encoder.encode(cffexl2_message.cref(),(char *)out, *out_len);
	*out_len =ret_len;
	return 0;
}

int encode_dce_md_best_deep(void *buff ,void *out, size_t *out_len)
{
	//MDBestAndDeep_MY
	return 0;
}


int encode_dce_arbi(void *buff ,void *out, size_t *out_len)
{
	//MDArbi_MY
	return 0;
}

int encode_dce_md_ten_entrust(void *buff ,void *out, size_t *out_len)
{
	//MDTenEntrust_MY
	return 0;
}

int encode_dce_order_stat(void *buff ,void *out, size_t *out_len)
{
	//MDOrderStatistic_MY
	return 0;
}

int encode_dce_rt_price(void *buff ,void *out, size_t *out_len)
{
	//MDRealTimePrice_MY
	return 0;
}

int encode_dce_match_price_qt(void *buff ,void *out, size_t *out_len)
{
	//MDMarchPriceQty_MY
	return 0;
}

int encode_czce_snapshot_field(void *buff ,void *out, size_t *out_len)
{
	//ZCEL2QuotSnapshotField_MY
	return 0;
}
int encode_czce_cmb_field(void *buff ,void *out, size_t *out_len)
{
	//ZCEQuotCMBQuotField_MY
	return 0;
}

int encode_depth_md_l1(void *buff ,void *out, size_t *out_len)
{
	//struct CDepthMarketDataField
	int32_t  l1_proto_ver=1;
	struct rq_raw_quote_t *in
		= (struct rq_raw_quote_t *)buff;
	level1_mref  ref = s_l1_msg.mref();
	ref.set_protocol_ver().as(l1_proto_ver);
	ref.set_timestamp().as((uint64_t)in->epoch_us);
	ref.set_trading_day().as(in->l1_depth_data.TradingDay);
	ref.set_settlement_GID().as(in->l1_depth_data.SettlementGroupID);
	ref.set_settlement_ID().as(in->l1_depth_data.SettlementID);
	ref.set_last_price().as(in->l1_depth_data.LastPrice);
	ref.set_pre_settlement_price().as(in->l1_depth_data.PreSettlementPrice);
	ref.set_pre_close_price().as(in->l1_depth_data.PreClosePrice);
	ref.set_pre_open_interest().as(in->l1_depth_data.PreOpenInterest);
	ref.set_open_price().as(in->l1_depth_data.OpenPrice);
	ref.set_highest_price().as(in->l1_depth_data.HighestPrice);
	ref.set_lowest_price().as(in->l1_depth_data.LowestPrice);
	ref.set_total_volume().as(in->l1_depth_data.Volume);
	ref.set_total_turnover().as(in->l1_depth_data.Turnover);
	ref.set_open_interest().as(in->l1_depth_data.OpenInterest);
	ref.set_close_price().as(in->l1_depth_data.ClosePrice);
	ref.set_settlement_price().as(in->l1_depth_data.SettlementPrice);
	ref.set_upper_limit_price().as(in->l1_depth_data.UpperLimitPrice);
	ref.set_lower_limit_price().as(in->l1_depth_data.LowerLimitPrice);
	ref.set_pre_delta().as(in->l1_depth_data.PreDelta);
	ref.set_cur_delta().as(in->l1_depth_data.CurrDelta);
	ref.set_update_time().as(in->l1_depth_data.UpdateTime);
	ref.set_update_ms().as(in->l1_depth_data.UpdateMillisec);
	ref.set_instrument_id().as(in->l1_depth_data.InstrumentID);
	ref.set_bid_ask_pvs().resize(10);
	double prices[10] = {in->l1_depth_data.BidPrice1, in->l1_depth_data.AskPrice1,
						 in->l1_depth_data.BidPrice2, in->l1_depth_data.AskPrice2,
						 in->l1_depth_data.BidPrice3, in->l1_depth_data.AskPrice3,
						 in->l1_depth_data.BidPrice4, in->l1_depth_data.AskPrice4,
						 in->l1_depth_data.BidPrice5, in->l1_depth_data.AskPrice5,
						};
	int volumes[10]= { in->l1_depth_data.BidVolume1, in->l1_depth_data.AskVolume1,
					   in->l1_depth_data.BidVolume2, in->l1_depth_data.AskVolume2,
					   in->l1_depth_data.BidVolume3, in->l1_depth_data.AskVolume3,
					   in->l1_depth_data.BidVolume4, in->l1_depth_data.AskVolume4,
					   in->l1_depth_data.BidVolume5, in->l1_depth_data.AskVolume5,
					 };
	for(int i=0; i<10; ++i) {
		level1_mref::bid_ask_pvs_element_mref  pv(ref.set_bid_ask_pvs()[i]);
		pv.set_level_price().as(prices[i]);
		pv.set_level_vol().as(volumes[i]);
	}
	const mfast::templates_description *descriptions[] =
	{ rq_fast::description() };
	size_t ret_len;
	mfast::fast_encoder encoder;
	encoder.include(descriptions);
	ret_len = encoder.encode(s_l1_msg.cref(),(char *)out, *out_len);
	*out_len =ret_len;
	return 0;
}

int encode_tdf_market_data_l2(void *buff ,void *out, size_t *out_len)
{
	//TDF_MARKET_DATA_MY
	return 0;
}

int encode_tdf_index_data_l2(void *buff ,void *out, size_t *out_len)
{
	//TDF_INDEX_DATA_MY
	return 0;
}

int encode_quote(int quote_type, void *quote, size_t quote_len,
				 void *out, size_t *out_len)
{
	int i,ret=0;
	typedef struct {
		int type;
		int (*handler)(void *quote, void *out, size_t *out_len);
	} encode_arary_t;
	//TODO: replace with O(1) algorithm complexity (with hash-map)
	const encode_arary_t array[]= {
		{GTA_UDP_CFFEX_QUOTE_TYPE,  encode_cffex_l2},
		{SHFE_EX_QUOTE_TYPE, encode_depth_md_l1},
		{DCE_MDBESTANDDEEP_QUOTE_TYPE,  encode_dce_md_best_deep},
		{DCE_ARBI_QUOTE_TYPE,  encode_dce_arbi},
		{DCE_MDTENENTRUST_QUOTE_TYPE,encode_dce_md_ten_entrust},
		{DCE_MDORDERSTATISTIC_QUOTE_TYPE,encode_dce_order_stat},
		{DCE_MDREALTIMEPRICE_QUOTE_TYPE,encode_dce_order_stat},
		{DCE_MDMARCHPRICEQTY_QUOTE_TYPE,encode_dce_match_price_qt},
		{CZCE_LEVEL2_QUOTE_TYPE, encode_czce_snapshot_field },
		{CZCE_CMB_QUOTE_TYPE, encode_czce_cmb_field},
		{TDF_STOCK_QUOTE_TYPE,	encode_tdf_market_data_l2},
		{TDF_INDEX_QUOTE_TYPE,	encode_tdf_index_data_l2},
	};
	for(i=0; i<ARRAY_SIZE(array); ++i) {
		if(quote_type == array[i].type) {
			/*
			if(quote_len != array[i].quote_struct_size){
				char err[]="quote type and size mismatch\n";
				set_error(err);
				assert(false);
				return FAILURE;
			}
			*/
			ret= array[i].handler(quote, out,out_len);
			break;
		}
	}
	return ret;
}

int decode_cffex_l2(mfast::message_cref &abs_ref, rq_recv_callback handler)
{
	struct rq_raw_quote_t out;
	cffexl2_cref ref = static_cast<cffexl2_cref>(abs_ref);
	//decode from message.
	out.epoch_us = (u_int64_t)ref.get_timestamp().value();
	strncpy(out.cffexl2_data.szTradingDay , ref.get_trading_day().c_str(),
			sizeof(out.cffexl2_data.szTradingDay));
	strncpy(out.cffexl2_data.szSettlementGroupID,ref.get_settlement_GID().c_str(),
			sizeof(out.cffexl2_data.szSettlementGroupID));
	out.cffexl2_data.nSettlementID  =ref.get_settlement_ID().value();
	out.cffexl2_data.dLastPrice = (ref.get_last_price());
	out.cffexl2_data.dPreSettlementPrice= (ref.get_pre_settlement_price());
	out.cffexl2_data.dPreClosePrice = (ref.get_pre_close_price());
	out.cffexl2_data.dPreOpenInterest= (ref.get_pre_open_interest());
	out.cffexl2_data.dOpenPrice= (ref.get_open_price());
	out.cffexl2_data.dHighestPrice  = (ref.get_highest_price());
	out.cffexl2_data.dLowestPrice= (ref.get_lowest_price());
	out.cffexl2_data.nVolume= ref.get_total_volume().value();
	out.cffexl2_data.dTurnover= (ref.get_total_turnover());
	out.cffexl2_data.dOpenInterest= (ref.get_open_interest());
	out.cffexl2_data.dClosePrice= (ref.get_close_price());
	out.cffexl2_data.dSettlementPrice= (ref.get_settlement_price());
	out.cffexl2_data.dUpperLimitPrice= (ref.get_upper_limit_price());
	out.cffexl2_data.dLowerLimitPrice= (ref.get_lower_limit_price());
	out.cffexl2_data.dPreDelta= (ref.get_pre_delta());
	out.cffexl2_data.dCurrDelta= (ref.get_cur_delta());
	strncpy(out.cffexl2_data.szUpdateTime,ref.get_update_time().c_str(),
			sizeof(out.cffexl2_data.szUpdateTime));
	out.cffexl2_data.nUpdateMillisec= ref.get_update_ms().value();
	strncpy(out.cffexl2_data.szInstrumentID, ref.get_instrument_id().c_str(),
			sizeof(out.cffexl2_data.szInstrumentID));
	//decode price-level.
	int pv_size= ref.get_bid_ask_pvs().size();
	double *prices[10] = {&out.cffexl2_data.dBidPrice1, &out.cffexl2_data.dAskPrice1,
						  &out.cffexl2_data.dBidPrice2, &out.cffexl2_data.dAskPrice2,
						  &out.cffexl2_data.dBidPrice3, &out.cffexl2_data.dAskPrice3,
						  &out.cffexl2_data.dBidPrice4, &out.cffexl2_data.dAskPrice4,
						  &out.cffexl2_data.dBidPrice5, &out.cffexl2_data.dAskPrice5,
						 };
	int *volumes[10]= { &out.cffexl2_data.nBidVolume1, &out.cffexl2_data.nAskVolume1,
						&out.cffexl2_data.nBidVolume2, &out.cffexl2_data.nAskVolume2,
						&out.cffexl2_data.nBidVolume3, &out.cffexl2_data.nAskVolume3,
						&out.cffexl2_data.nBidVolume4, &out.cffexl2_data.nAskVolume4,
						&out.cffexl2_data.nBidVolume5, &out.cffexl2_data.nAskVolume5,
					  };
	if(pv_size != 10) {
		//TODO:error condition
		fprintf(stderr, "pvs size =%d\n",pv_size);
	}
	for(int i=0; i<pv_size; ++i) {
		*prices[i]=ref.get_bid_ask_pvs()[i].get_level_price();
		*volumes[i] = ref.get_bid_ask_pvs()[i].get_level_vol().value();
	}
	handler(abs_ref.id(),&out ,sizeof(out));
	return 0;
}


int decode_dce_md_best_deep(mfast::message_cref &abs_ref,
							rq_recv_callback handler)

{
	//MDBestAndDeep_MY
	return 0;
}


int decode_dce_arbi(mfast::message_cref &abs_ref, rq_recv_callback handler)
{
	//MDArbi_MY
	return 0;
}

int decode_dce_md_ten_entrust(mfast::message_cref &abs_ref,
							  rq_recv_callback handler)
{
	//MDTenEntrust_MY
	return 0;
}

int decode_dce_order_stat(mfast::message_cref &abs_ref,
						  rq_recv_callback handler)
{
	//MDOrderStatistic_MY
	return 0;
}

int decode_dce_rt_price(mfast::message_cref &abs_ref, rq_recv_callback handler)
{
	//MDRealTimePrice_MY
	return 0;
}

int decode_dce_match_price_qt(mfast::message_cref &abs_ref,
							  rq_recv_callback handler)
{
	//MDMarchPriceQty_MY
	return 0;
}

int decode_czce_snapshot_field(mfast::message_cref &abs_ref,
							   rq_recv_callback handler)
{
	//ZCEL2QuotSnapshotField_MY
	return 0;
}

int decode_czce_cmb_field(mfast::message_cref &abs_ref,
						  rq_recv_callback handler)
{
	//ZCEQuotCMBQuotField_MY
	return 0;
}

int decode_depth_md_l1(mfast::message_cref &abs_ref, rq_recv_callback handler)
{
	//CDepthMarketDataField
	struct rq_raw_quote_t out;
	level1_cref  ref = static_cast<level1_cref>(abs_ref);
	//decode from message.
	out.epoch_us = (u_int64_t)ref.get_timestamp().value();
	strncpy(out.l1_depth_data.TradingDay , ref.get_trading_day().c_str(),
			sizeof(out.l1_depth_data.TradingDay));
	strncpy(out.l1_depth_data.SettlementGroupID,ref.get_settlement_GID().c_str(),
			sizeof(out.l1_depth_data.SettlementGroupID));
	out.l1_depth_data.SettlementID  =ref.get_settlement_ID().value();
	out.l1_depth_data.LastPrice = (ref.get_last_price());
	out.l1_depth_data.PreSettlementPrice= (ref.get_pre_settlement_price());
	out.l1_depth_data.PreClosePrice = (ref.get_pre_close_price());
	out.l1_depth_data.PreOpenInterest= (ref.get_pre_open_interest());
	out.l1_depth_data.OpenPrice= (ref.get_open_price());
	out.l1_depth_data.HighestPrice  = (ref.get_highest_price());
	out.l1_depth_data.LowestPrice= (ref.get_lowest_price());
	out.l1_depth_data.Volume= ref.get_total_volume().value();
	out.l1_depth_data.Turnover= (ref.get_total_turnover());
	out.l1_depth_data.OpenInterest= (ref.get_open_interest());
	out.l1_depth_data.ClosePrice= (ref.get_close_price());
	out.l1_depth_data.SettlementPrice= (ref.get_settlement_price());
	out.l1_depth_data.UpperLimitPrice= (ref.get_upper_limit_price());
	out.l1_depth_data.LowerLimitPrice= (ref.get_lower_limit_price());
	out.l1_depth_data.PreDelta= (ref.get_pre_delta());
	out.l1_depth_data.CurrDelta= (ref.get_cur_delta());
	strncpy(out.l1_depth_data.UpdateTime,ref.get_update_time().c_str(),
			sizeof(out.l1_depth_data.UpdateTime));
	out.l1_depth_data.UpdateMillisec= ref.get_update_ms().value();
	strncpy(out.l1_depth_data.InstrumentID, ref.get_instrument_id().c_str(),
			sizeof(out.l1_depth_data.InstrumentID));
	//decode price-level.
	int pv_size= ref.get_bid_ask_pvs().size();
	double *prices[10] = {&out.l1_depth_data.BidPrice1, &out.l1_depth_data.AskPrice1,
						  &out.l1_depth_data.BidPrice2, &out.l1_depth_data.AskPrice2,
						  &out.l1_depth_data.BidPrice3, &out.l1_depth_data.AskPrice3,
						  &out.l1_depth_data.BidPrice4, &out.l1_depth_data.AskPrice4,
						  &out.l1_depth_data.BidPrice5, &out.l1_depth_data.AskPrice5,
						 };
	int *volumes[10]= { &out.l1_depth_data.BidVolume1, &out.l1_depth_data.AskVolume1,
						&out.l1_depth_data.BidVolume2, &out.l1_depth_data.AskVolume2,
						&out.l1_depth_data.BidVolume3, &out.l1_depth_data.AskVolume3,
						&out.l1_depth_data.BidVolume4, &out.l1_depth_data.AskVolume4,
						&out.l1_depth_data.BidVolume5, &out.l1_depth_data.AskVolume5,
					  };
	//debug
	if(pv_size != 10) {
		assert(0);
		return -1;
	}
	for(int i=0; i<pv_size; ++i) {
		*prices[i]=ref.get_bid_ask_pvs()[i].get_level_price();
		*volumes[i] = ref.get_bid_ask_pvs()[i].get_level_vol().value();
	}
	handler(abs_ref.id(), &out ,sizeof(out));
	return 0;
}

int decode_tdf_market_data_l2(mfast::message_cref &abs_ref,
							  rq_recv_callback handler)
{
	//TDF_MARKET_DATA_MY
	return 0;
}

int decode_tdf_index_data_l2(mfast::message_cref &abs_ref,
							 rq_recv_callback handler)
{
	//TDF_INDEX_DATA_MY
	return 0;
}

int decode_quote(const char *fast_buff,
				 size_t buff_len, rq_recv_callback  on_quote_recv)
{
	int i,ret=0;
	typedef struct {
		int quote_type;
		int (*decoder)(mfast::message_cref &ref,
					   rq_recv_callback handler);
		//	decode_quote_callback_t handler);
	} decode_arary_t;
	const mfast::templates_description *descriptions[] =
	{ rq_fast::description() };
	mfast::fast_decoder decoder;
	decoder.include(descriptions);
	mfast::message_cref abs_ref=
		decoder.decode(fast_buff,fast_buff+buff_len);
	int quote_template_id = abs_ref.id();
	//TODO: replace with O(1) algorithm complexity (with hash-map)
	const decode_arary_t array[]= {
		{
			GTA_UDP_CFFEX_QUOTE_TYPE,
			decode_cffex_l2
		},
		{
			DCE_MDBESTANDDEEP_QUOTE_TYPE,
			decode_dce_md_best_deep
		},
		{
			DCE_ARBI_QUOTE_TYPE,
			decode_dce_arbi
		},
		{
			DCE_MDTENENTRUST_QUOTE_TYPE,
			decode_dce_md_ten_entrust
		},
		{
			DCE_MDORDERSTATISTIC_QUOTE_TYPE,
			decode_dce_order_stat
		},
		{
			DCE_MDREALTIMEPRICE_QUOTE_TYPE,
			decode_dce_order_stat
		},
		{
			DCE_MDMARCHPRICEQTY_QUOTE_TYPE,
			decode_dce_match_price_qt
		},
		{
			CZCE_LEVEL2_QUOTE_TYPE,
			decode_czce_snapshot_field
		},
		{
			CZCE_CMB_QUOTE_TYPE,
			decode_czce_cmb_field
		},
		{
			SHFE_EX_QUOTE_TYPE,
			decode_depth_md_l1
		},
		{
			TDF_STOCK_QUOTE_TYPE,
			decode_tdf_market_data_l2
		},

		{
			TDF_INDEX_QUOTE_TYPE,
			decode_tdf_index_data_l2
		}
	};
	for(i=0; i<ARRAY_SIZE(array); ++i) {
		//if(decode_map.find(quote_template_id) == decode_map.end()){
		//		set_error("decode map can't find quote type:%d",quote_template_id);
		//		return FAILURE;
		//	}
		//call descreted decoder for each quote type.
		if(quote_template_id == array[i].quote_type) {
			//ret = array[i].decoder(abs_ref,decode_map[quote_template_id]);
			ret = array[i].decoder(abs_ref,on_quote_recv);//decode_map[quote_template_id]);
		}
	}
	return ret;
}

