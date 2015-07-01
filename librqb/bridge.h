#if !defined(__RSS_QUOTE_BRIDGE_FEEDER_20150616__)
#define __RSS_QUOTE_BRIDGE_FEEDER_20150616__
#include <stdio.h>
#include <quote/quote_enum.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 
 * 创建rss行情分发服务 
 * 行情分发端(client)接口 
 * @para target_ip:行情接收程序的目标IP
 * @para target_port:行情接收程序的目标端口 
 * @para identity 标识发送端的身份，发送端的id必须唯一
 * @retval -1: 错误，可以通过get_error查询错误内容;
 * 	    0:成功
 */
int connect_rq_receiver(char *target_ip, 
		int target_port,char* identity);
#pragma pack(push)
#pragma pack(8)
struct rq_raw_quote_t
{
	uint64_t epoch_us;
	/*annonymous union */
	union{
		struct CFfexFtdcDepthMarketData cffexl2_data;
		struct CDepthMarketDataField l1_depth_data;
	};
};
#pragma pack(pop)
/* 
 * 分发RSS行情
 * 行情分发端接口 
 * @parm quote_type 行情类型 枚举值请参见 quote/quote_cmn_save.h
 * @parm data 行情内容缓冲区, 行情数据类型请参见数据类型rq_raw_quote_t
 * 	@see struct rq_raw_quote_t  
 * @parm data_size 行情内容缓冲区大小
 * @retval -1: 错误，可以通过get_error查询错误内容;
 * 	    0:成功
 */
int publish_rq(int quote_type, void *data, size_t data_size);

/* 
 * 连接到RSS行情服务程序
 * 行情接收端端(server)接口 
 * @para src ：可指定绑定的IP地址或端口，如 "192.168.1.100" 或 "eth0"
 * @para port: 服务监听的端口号
 * @parm data_size 行情内容缓冲区大小
 * @retval -1: 错误，可以通过get_error查询错误内容;
 * 	    0:成功
 */
int create_rq_receiver(char * src, int port);

/* 
 * 行情接收轮询
 * 行情接收端端接口 ,
 * NOTE: 该轮询为阻塞方式，暂未提供停止接口，有需要再加上;
 * @parm rq_recv_callback 为行情接收回调接口;
	 * quote_type 行情类型
	 * @parm data 行情内容缓冲区指针
	 * @parm data_size 行情内容缓冲区大小
 */
typedef int (*rq_recv_callback)(int quote_type, void *data, size_t data_size);
void recv_rq_poll(rq_recv_callback callback);

/* 
 * 关闭rss行情连接
 * 行情分发端/接收端接口
 */
void close_rq();
/* 
 * 获取错误;
 * 行情分发端/接收端接口
 * @para buff 错误信息字符缓冲区大小;
 * @len  [in/out] 输入时为缓冲区大小，输出时为错误信息的字符串长度;
 */
void get_error(char *buff, int *len);

#ifdef __cplusplus
}
#endif

#endif 
