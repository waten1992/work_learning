#include <rqb/bridge.h>

void fake_ex1_data_type(struct rq_raw_quote_t *data)
{
	data->epoch_us = 1;
	strcpy(data->l1_depth_data.TradingDay, "001");
	strcpy(data->l1_depth_data.SettlementGroupID, "002");
	data->l1_depth_data.SettlementID = 10;
	data->l1_depth_data.LastPrice = 0.1;
	data->l1_depth_data.PreSettlementPrice=0.2;
	data->l1_depth_data.PreClosePrice=0.3;
	data->l1_depth_data.PreOpenInterest=0.4;
	data->l1_depth_data.OpenPrice=0.5;
	data->l1_depth_data.HighestPrice = 0.6;
	data->l1_depth_data.LowestPrice = 0.7;
	data->l1_depth_data.Volume =11;
	data->l1_depth_data.Turnover = 0.8;
	data->l1_depth_data.OpenInterest = 0.9;
	data->l1_depth_data.ClosePrice = 1.0;
	data->l1_depth_data.SettlementPrice = 1.1;
	data->l1_depth_data.UpperLimitPrice = 1.2;
	data->l1_depth_data.LowerLimitPrice= 1.3;
	///昨虚实度
	data->l1_depth_data.PreDelta=1.4;
	///今虚实度
	data->l1_depth_data.CurrDelta =1.5;
	///最后修改时间
	strcpy(data->l1_depth_data.UpdateTime,
		   "1");
	///最后修改毫秒
	data->l1_depth_data.UpdateMillisec = 12;
	///合约代码
	strcpy(data->l1_depth_data.InstrumentID, "2");
	///申买价一
	data->l1_depth_data.BidPrice1 = 1.6;
	///申买量一
	data->l1_depth_data.BidVolume1 = 15;
	///申卖价一
	data->l1_depth_data.AskPrice1 =1.7;
	///申卖量一
	data->l1_depth_data.AskVolume1 =16;
	///申买价二
	data->l1_depth_data.BidPrice2 =1.8;
	///申买量二
	data->l1_depth_data.BidVolume2 =17;
	///申卖价二
	data->l1_depth_data.AskPrice2 = 1.9;
	///申卖量二
	data->l1_depth_data.AskVolume2 =18;
	///申买价三
	data->l1_depth_data.BidPrice3 =2.0;
	///申买量三
	data->l1_depth_data.BidVolume3 =19;
	///申卖价三
	data->l1_depth_data.AskPrice3 =2.1;
	///申卖量三
	data->l1_depth_data.AskVolume3 =20;
	///申买价四
	data->l1_depth_data.BidPrice4 = 2.2;
	///申买量四
	data->l1_depth_data.BidVolume4 =21;
	///申卖价四
	data->l1_depth_data.AskPrice4 = 2.3;
	///申卖量四
	data->l1_depth_data.AskVolume4 =22;
	///申买价五
	data->l1_depth_data.BidPrice5 =2.4;
	///申买量五
	data->l1_depth_data.BidVolume5 =23;
	///申卖价五
	data->l1_depth_data.AskPrice5 =2.5;
	///申卖量五
	data->l1_depth_data.AskVolume5 =24;
	///业务发生日期
	strcpy(data->l1_depth_data.ActionDay, "45");
}

void test_pub1()
{
	char target_ip[]="192.168.1.136";
	int target_port=10000;
	char id[]="nw";
	int ret=connect_rq_receiver(target_ip,
								target_port,
								id);
	if(ret <0) {
		printf("error to connect to rq receiver\n");
		return;
	}
	struct rq_raw_quote_t raw_data;
	memset(&raw_data, 0,sizeof(raw_data));
	fake_ex1_data_type(&raw_data);
	ret = publish_rq(SHFE_EX_QUOTE_TYPE,
					 &raw_data,
					 sizeof(raw_data));
	if(ret <0) {
		printf("error to publish rq");
		return;
	}
}

int main(void)
{
	test_pub1();
	return 0;
}
