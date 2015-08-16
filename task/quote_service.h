/*
 *	quote_service.h 
 * */
typedef unsigned int u32_int ;
typedef struct qsvr
{
	u32_int 	date ;
	char 		item[8];
	char 		contract[8];
	u32_int 	rank;
	char 		quote_record[24];
	char 		addrss[128];
};

struct qsvr*	qsvr_init(const char *path );

void	qsvr_find(u32_int date , const char *item , u32_int rank , struct qsvr*ret_val );

void
qsvr_destroy(struct qsvr *des_val);
