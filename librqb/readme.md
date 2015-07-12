#redis 推送程序，按照web端json格式化；
关于推送模型：
    没有使用多线程的生产者和消费者，默认是拿到数据就转发；
    如果转发失败就再次转:
    代码：
      320     int  loop_test = 1 ;
      321     while(loop_test)
      322     {
      323         reply =(redisReply *) redisCommand(c,"LPUSH mylist %s",quote_array);
      324         if(reply != NULL) //if redisCommand send fail , it will be restart
      325             loop_test = 0 ;
      326     }
      327     freeReplyObject(reply);

关于数据：
    item：
    exchange:
    amount:
    price_change:
    我没有在结构体内找到，是我自己伪造的数据；
    
关于数据类型：
            double类型，默认给了7位；因为不知道数据最大值是多少；

关于测试结果：
send 端：
        pwd006@Debain:~/trader/src/rss/rss_quote/librqb/test$ ./test_rqb_send 
        [debug] connected to tcp://192.168.52.136:10000

recv 端：
      pwd006@Debain:~/trader/src/rss/rss_quote/librqb/test$ ./test_rqb_recv 
        [debug] listen on tcp://eth0:10000

        start to pull quote
        get quote 10, size=376
        record----------> 0  
        quote_array--> {"src":"hwguan_test","type":"trading_msg","data":{"column":["contract","item","exchange","last_price","volume","amount","price_change","open_interest","open_interest_change","open","low","high"],"data":["2","item_cu","exchange","0.10000","11","amount","price_change","0.90000","0.40000","0.50000","0.70000","0.60000"],"STATE":"OK","type":"trading_msg"}}
         
        --------------
        reply->str:  {"src":"hwguan_test","type":"trading_msg","data":{"column":["contract","item","exchange","last_price","volume","amount","price_change","open_interest","open_interest_change","open","low","high"],"data":["2","item_cu","exchange","0.10000","11","amount","price_change","0.90000","0.40000","0.50000","0.70000","0.60000"],"STATE":"OK","type":"trading_msg"}}
        ^C



redis-cli 请求返回的数据：
127.0.0.1:6379> lrange mylist 0 -1
1) "{\"src\":\"hwguan_test\",\"type\":\"trading_msg\",\"data\":{\"column\":[\"contract\",\"item\",\"exchange\",\"last_price\",\"volume\",\"amount\",\"price_change\",\"open_interest\",\"open_interest_change\",\"open\",\"low\",\"high\"],\"data\":[\"2\",\"item_cu\",\"exchange\",\"0.10000\",\"11\",\"amount\",\"price_change\",\"0.90000\",\"0.40000\",\"0.50000\",\"0.70000\",\"0.60000\"],\"STATE\":\"OK\",\"type\":\"trading_msg\"}}"



Json 格式化的结果解析如下：
{
    "src":"hwguan_test",
    "type":"trading_msg",
    "data":{
        "column":[
            "contract",
            "item",
            "exchange",
            "last_price",
            "volume",
            "amount",
            "price_change",
            "open_interest",
            "open_interest_change",
            "open",
            "low",
            "high"
        ],
        "data":[
            "2",
            "item_cu",
            "exchange",
            "0.10000",
            "11",
            "amount",
            "price_change",
            "0.90000",
            "0.40000",
            "0.50000",
            "0.70000",
            "0.60000"
        ],
        "STATE":"OK",
        "type":"trading_msg"
    }
}