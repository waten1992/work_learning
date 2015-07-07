redis 学习文档

1-介绍：

typedef struct redisReply {
    int type; /* REDIS_REPLY_* */
    long long integer; /* The integer when type is REDIS_REPLY_INTEGER */
    int len; /* Length of string */
    char *str; /* Used for both REDIS_REPLY_ERROR and REDIS_REPLY_STRING */
    size_t elements; /* number of elements, for REDIS_REPLY_ARRAY */
    struct redisReply **element; /* elements vector for REDIS_REPLY_ARRAY */
} redisReply;

	
2-常用的命令：

	LIST : 是一个双向链表
			LPUSH:	插入到list的最左边；
				用法：LPUSH key value [value ...] 
				Return value:
					Integer reply: the length of the list after the push operations.
			RPUSH:  插入到list的最右边，同LPUSH一样；

			LRANGE: 查看list的内容；
				用法：LRANGE key start stop  
				-1代表最后一个元素， 0 代表第一个元素。 故查看整个list 用 LRANGE Mylist 0 -1;
				Return value:
						Array reply: list of elements in the specified range.

			LPOP:  弹出list左边的元素
				用法：LPOP key 
				Return value：
					Bulk string reply: the value of the first element, or nil when key does not exist.  

				【注释 Bulk string】
						RESP Bulk Strings
							Bulk Strings are used in order to represent a single binary safe string up to 512 MB in length.
							Bulk Strings are encoded in the following way:

							A "$" byte followed by the number of bytes composing the string (a prefixed length), terminated by CRLF.
							The actual string data.
							
							A final CRLF.

							So the string "foobar" is encoded as follows:	"$6\r\nfoobar\r\n"
							When an empty string is just: 	"$0\r\n\r\n"
							
							RESP Bulk Strings can also be used in order to signal non-existence of a value using a special 
							format that is used to represent a Null value. In this special format the length is -1, 
							and there is no data, so a Null is represented as: "$-1\r\n"
							
							This is called a Null Bulk String.
							
							The client library API should not return an empty string, but a nil object, 
							when the server replies with a Null Bulk String. For example a Ruby library 
							should return 'nil' while a C library should return NULL 
							(or set a special flag in the reply object), and so forth.
			
			BLPOP:  弹出list左边的元素，但是是阻塞的，timeout 表示阻塞的时间；0 表示一直阻塞，直到list中有元素才结束；

				用法：BLPOP key [key ...] timeout 
				Return value
					Array reply: specifically:
						1-A nil multi-bulk when no element could be popped and the timeout expired.
						2-A two-element multi-bulk with the first element being the name of the key
						where an element was popped and the second element being the value of the popped element.


	OBJECT ENCODING : 查看key-vaule 的对象编码
	TYPE value : 查看vaule 对象的类型  
	