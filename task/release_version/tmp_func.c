#include "quote_service.h"
#include "schedule.h"
extern void quote_find_use_date_key(struct quote_map* qm,struct day_schedule_t *input );
struct quote_map *test_map ;

void 
init_history_quote()
{
	const char *origin_data_path = "../test_version/input_data.txt" ; 
	const char *item_path = "uniq.txt"                              ;

	printf("start ! \n")												;
	test_map =  qsvr_init(origin_data_path,item_path)					;
	printf("test find \n")											;

}
int 
handle_quote_query(struct day_schedule_t *input)
{
    unsigned long start, end											;
	
	struct quote_map *tmp_map ;
	tmp_map = (struct quote_map *)malloc(sizeof(struct quote_map));
	memcpy(tmp_map, test_map,sizeof(struct quote_map)) ;	
	
	HP_TIMING_NOW(start)												;
//	qsvr_find(test_map,test_time,test_item,test_rank,test_val)		;
	quote_find_use_date_key(tmp_map,input);
	HP_TIMING_NOW(end)												;
#if 0
	if (0 != (*input->contract) ) {	
		printf("item : %s ,contract : %s",input->item,input->contract);
	}else {
		printf("****NO DATA !****\n");
	}
#endif
		printf("\n the cost cycles are %lf ns\n", (end - start)/3.6)		;
		free(tmp_map);
return 0 ;
}
