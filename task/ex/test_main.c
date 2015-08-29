#include "quote_service.h"
#include "schedule.h"

int 
main()
{
	struct task_sched_cfg *dir;
    struct task_sched *ts ;
	int del_id ;
    dir = (struct task_sched_cfg *)malloc(sizeof(struct task_sched_cfg ));
    if (NULL == dir) {
        printf("struct task_sched_cfg dir allocate is error , errno is : %s \n",strerror(errno));
    }
    snprintf(dir->quote_origin_data_path ,PATH_LEN ,"%s","../rss_file_path.txt");
    snprintf(dir->quote_item_path,PATH_LEN,"%s","uniq.txt");
    ts = task_sched_init(dir);

    struct task **task_info ;
    task_info = (struct task **)malloc(sizeof(struct task));

    for (int i = 0; i < TEST_NUM ;i++) {
        task_info[i] = (struct task *)malloc(sizeof(struct task));
        if (NULL == task_info[i]) {
            printf("task_info[%d] allocate is error , errno is : %s \n",i,strerror(errno));
        }
    }   
    
    for(int i = 0; i < TEST_NUM ;i++) {
        memset(task_info[i],0,sizeof(struct task));
    }   
    
	
    task_info[0]->beg_date = 20150601 ;
    task_info[0]->end_date   = 20150631 ;
    snprintf(task_info[0]->item,ITEM_LEN,"%s","IF");
    task_info[0]->rank = 1;
    task_sched_add(ts,task_info[0]);

    task_info[1]->beg_date = 20150615;
    task_info[1]->end_date   = 20150631 ;
    snprintf(task_info[1]->item,ITEM_LEN,"%s","dljm");
    task_info[1]->rank = 1;
    task_sched_add(ts,task_info[1]);
	sleep(10);
	del_id = 0;
	printf("del IF \n");
	task_sched_del(ts,del_id);	
	
	task_info[2]->beg_date = 20150601 ;
    task_info[2]->end_date   = 20150631 ;
    snprintf(task_info[2]->item,ITEM_LEN,"%s","shag");
    task_info[2]->rank = 1;
    task_sched_add(ts,task_info[2]);
       
	while (1) 
		;
    task_sched_destroy(ts);

return 0;
}
