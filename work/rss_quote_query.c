#include "rss_quote_query.h"

struct rss_quote_query {
	uint64_t 	cnt;
	uint16_t 	code_mk;
	uint16_t 	len;
	FILE 		*fp;
}rss_quote_query_t ;

struct rss_quote_query_at {
	FILE 		*fp;
	int 		idx;
	int 		*type;
	uint64_t	*timestamp;
}rss_quote_query_at_t;


struct rss_quote_query *
rss_quote_query_load(const char * rss_quote_query_path)
{
	struct rss_quote_query *p;
	int ret ;
	p = (struct rss_quote_query *)malloc(sizeof(struct rss_quote_query));
	p->fp = fopen(rss_quote_query_path,"r+b");
	ret = fread(p ,(sizeof(struct rss_quote_query)-sizeof(FILE *)),1, p->fp);
	if (ret != 1)
	{
		fprintf(stderr, "%s : %s\n", rss_quote_query_path, strerror(errno));
		return NULL;
	}
	printf("open ok \n");

return p;
}

int rss_quote_query_get_cnt(struct rss_quote_query *p , uint64_t *get_cnt)
{
	*get_cnt = p->cnt;	
	return 0;	
}

int 
rss_quote_query_unload(struct rss_quote_query *p)
{
	fclose(p->fp);
	free(p);
	printf(" close !\n");

return 0;
}

int 
main()
{
	struct rss_quote_query *tmp ;
	uint64_t cnt = 1;
	const char * path = "IF1509.dat";
	tmp =  rss_quote_query_load(path);
	rss_quote_query_get_cnt(tmp,&cnt);
	printf("cnt = %ld \n",cnt);
	rss_quote_query_unload(tmp);
	return 0 ; 
}
