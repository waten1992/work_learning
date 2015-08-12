#include "quote_service.h"

//uint32_t
//int32_t

struct quote_map
{
	u32_int 	***index_array ; //index_array[Days][86] 
	qsvr_data	qsvr_struct    ;
};

struct quote_map*
qsvr_init(const char *path)
{
	struct quote_map* qm = (struct quote_map*)malloc(sizeof(*qm));

	// load rss_file_path.txt
	// parse 
	// create map
	
	return qm;
}

void
qsvr_find(struct quote_map* qm, u32_int date , char *item , u32_int rank , struct qsvr *ret_val )
{
	
}

void
qsvr_destroy(struct quote_map* qm)
{
	// release mem of qm
}
