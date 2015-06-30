#include <sys/sem.h>

	int semctl(int sem_id, int sem_num, int command, ...);
	int semget(key_t key, int num_sems, int sem_flags);
	int semop(int sem_id, struct sembuf *sem_ops, size_t num_sem_ops);

struct sembuf 
{
	short sem_num;
	short sem_op;
	short sem_flg;
}   

/*  管道  */
int pipe (int file_descriptor[2]) ;
写到file_descriptor[1] 中的数据都可以从file_descriptor[0]读出来；


/*内存共享*/

void *shmat(int shm_id, const void *shm_addr, int shmflg);// shm_id链接到进程的地址空间
	创建共享内存后，是不能被任何进程访问；
	shm_id :	 共享内存ID
	shm_addr: 	 进程的位置
	shmflg: 	 is a set of bitwise flags;
		SHM_RND:	in conjunction with shm_addr
		SHM_RDONLY: makes the attached memory read-only


	If the shmat call is successful, it returns a pointer to the first byte of shared memory. On failure –1
is returned.

int shmctl(int shm_id, int cmd, struct shmid_ds *buf);
		struct shmid_ds
		{
			uid_t shm_perm.uid;
			uid_t shm_perm.gid;
			mode_t shm_perm.mode;
		}
	shm_id, is the identifier returned from shmget;

	command, is the action to take. It can take three values, shown in the following table.
	Command Description
	IPC_STAT 	Sets the data in the shmid_ds structure to reflect the values associated with the shared memory.
	IPC_SET 	Sets the values associated with the shared memory to those provided inthe shmid_ds data structure, if the process has permission to do so.
	IPC_RMID 	Deletes the shared memory segment.

	buf, is a pointer to the structure containing the modes and permissions for the shared memory.
	On success, it returns 0, on failure, –1;

int shmdt(const void *shm_addr); 
	The shmdt function detaches the shared memory from the current process. It takes a pointer to the address
returned by shmat. On success, it returns 0, on error –1. Note that detaching the shared memory doesn’t
delete it; it just makes that memory unavailable to the current process.

int shmget(key_t key, size_t size, int shmflg); //创建共享内存
	key 是标识符；
	size 共享的内存容量, page_size的倍数;
	shmflg 


--------------------------

消息队列：
	优点：和管道相比，它独立于发送和接受进程而存在；

IPC状态命令：
		ipcs  -s 查看信号量的使用；
		ipcs  -m 共享内存情况；
		ipcrm -m <id>  删除共享内存；

		ipcs -q 显示消息队列
		ipcrm -q 删除消息队列 

socket :
		常用的端口号在：/etc/services 中 
		头文件：netinet/in.h
		/* Generic socket address structure (for connect, bind, and accept) */
		struct sockaddr 
		{
			unsigned short sa_family; /* Protocol family */
			char sa_data[14]; /* Address data. */
		};
/* Internet-style socket address structure */
		struct sockaddr_in
		 {
			unsigned short sin_family; /* Address family (always AF_INET) */
			unsigned short sin_port; /* Port number in network byte order */
			struct in_addr sin_addr; /* IP address in network byte order */
			unsigned char sin_zero[8]; /* Pad to sizeof(struct sockaddr) */
		};

		The IP address structure, in_addr, is defined as follows:
		struct in_addr 
		{
			unsigned long int s_addr;
		};

		typedef struct sockaddr SA;

		#include <sys/types.h>
		#include <sys/socket.h>
		int socket(int domain, int type, int protocol);
			domain = AF_INET , type = SOCK_STREAM (tcp), protocol = 0; 
			
			Domain 			Description
			AF_UNIX 			UNIX internal (file system sockets)
			AF_INET 			ARPA Internet protocols (UNIX network sockets)
			
			type
			SOCK_STREAM		TCP
			SOCK_DGRAM		UDP
		Returns: nonnegative descriptor if OK, −1 on error

		#include <sys/socket.h>
		int bind(int sockfd, const struct sockaddr *address, size_t address_len); 
			告诉内核把 address 服务器套接字的地址和sockfd 绑定起来；
			address_len = sizeof(sockaddr_in) ;
		Returns: 0 if OK, −1 on error

		#include <sys/socket.h>
		int listen(int sockfd, int backlog);
			建立监听描述符；backlog:在队列中的链接数目大于backlog ，内核就开始拒绝建立连接；
			Returns: 0 if OK, −1 on error

		#include <sys/socket.h> 
		int connect(int sockfd, struct sockaddr *serv_addr, int addrlen);  //对于客户端来说,
			Returns: 0 if OK, −1 on error
			阻塞函数！
			和服务器的地址serv_addr建立连接，直到链接成功；sockfd 描述符可以读写了；
			addrlen = sizeof(sockaddr_in);

		#include <sys/socket.h>
		int accept(int listenfd, struct sockaddr *addr, int *addrlen);  //阻塞函数
			Returns: nonnegative connected descriptor if OK, −1 on error
			addr ---写客户端套接字的地址

		如果listenfd 队列为空，accept 是阻塞的，直到listenfd不为空；可以通过对套接字文件描述符设置O_NONBLOCK来改变：
		函数fcntl可以改变这个：
		int flags = fcntl(socket, F_GETFL, 0);
		fcntl(socket, F_SETFL, O_NONBLOCK|flags);


		#include <netinet/in.h>
		unsigned long int htonl(unsigned long int hostlong); // host to network ,long 
		unsigned short int htons(unsigned short int hostshort);
		unsigned long int ntohl(unsigned long int netlong);
		unsigned short int ntohs(unsigned short int netshort);
		//规避大小端问题
		端口号: htons(port);
		ip号码：htonl(INADDR_ANY);


		#include <netdb.h>
		struct hostent *gethostbyaddr(const void *addr, size_t len, int type);
		struct hostent *gethostbyname(const char *name);
		//
		struct hostent
		 {
			char *h_name; /* name of the host */
			char **h_aliases; /* list of aliases (nicknames) */
			int h_addrtype; /* address type */
			int h_length; /* length in bytes of the address */
			char **h_addr_list /* list of address (network order) */
		};

