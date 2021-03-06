#include "quote_service.h"

extern void qsvr_find(struct quote_map* qm, uint32_t date , char *item , uint32_t rank , struct qsvr *ret_val );

extern void qsvr_destroy(struct quote_map* qm);

extern struct quote_map* qsvr_init(const char *origin_data_path,const char *item_path);

int main()
{
      const char *origin_data_path = "../rss_file_path.txt";
	  const char *item_path = "uniq.txt"								;
      unsigned long start, end											;

      struct quote_map *test_map 										;
      struct qsvr *test_val 											;

      test_val = (struct qsvr *)malloc(sizeof(struct qsvr))				;
      memset(test_val,0,sizeof(struct qsvr))							;
  
      printf("start ! \n")												;
      test_map =  qsvr_init(origin_data_path,item_path)					;
  
      uint32_t test_time = 20150701 , test_rank = 1						;
      char *test_item ="IF"												;
      printf("test find \n")											;
  
      HP_TIMING_NOW(start)												;
      qsvr_find(test_map,test_time,test_item,test_rank,test_val)		;
      HP_TIMING_NOW(end)												;
  
      if (test_val != NULL) {   
         
	  	printf("date : %d ,item : %s,contract: %s , address : %s\n",test_val->date,test_val->item,test_val->contract,test_val->address  );
     
	  }else {   
            
		printf("can't find \n")	;
        return -1 				;
      }

      printf("\n the cost cycles are %lf ns\n", (end - start)/3.6)		;

      free(test_val)													;
  
  	  qsvr_destroy(test_map)											;
return 0 ;
}
