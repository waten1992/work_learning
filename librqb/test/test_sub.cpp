#include <rqb/bridge.h>

int on_recv_quote(int quote_type, void *data, size_t data_size)
{
	printf("get quote %d, size=%ld\n", quote_type, data_size);
	struct rq_raw_quote_t *quote = (struct rq_raw_quote_t *)data;
	printf("ep=%ld\n", quote->epoch_us);
	printf("trading quote=%s\n",quote->l1_depth_data.TradingDay);
	printf("LastPrice =%.2f,\n", quote->l1_depth_data.LastPrice);
	/*
		quote->l1_depth_data.PreSettlementPrice
		quote->l1_depth_data.PreClosePrice
		quote->l1_depth_data.PreOpenInterest
		quote->l1_depth_data.OpenPrice
		quote->l1_depth_data.HighestPrice
		quote->l1_depth_data.LowestPrice
		quote->l1_depth_data.Volume
		quote->l1_depth_data.Turnover
		quote->l1_depth_data.OpenInterest
		quote->l1_depth_data.ClosePrice
		quote->l1_depth_data.SettlementPrice
		quote->l1_depth_data.UpperLimitPrice
		quote->l1_depth_data.LowerLimitPrice
		*/
	return 0;
}


int main()
{
	int ret;
	char bind_addr[]="eth0";
	ret= create_rq_receiver(bind_addr,10000);
	if(ret<0) {
		printf("error ot create rq receiver\n");
		return -1;
	}
	printf("start to pull quote\n");
	recv_rq_poll(on_recv_quote);
	return 0;
}
