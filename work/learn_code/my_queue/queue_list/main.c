/*use linklist store queue elements, don't manage memory allocate*/
#include "my_queue.h" 
#include "queue.h"

int
main()
{
	int ar[] = {1,2,3,4};
	int idx ;
	void *ret;
	struct  queue *qu;
	qu = queue_constructor();
	for (idx = 0; idx < sizeof(ar)/sizeof(ar[0]); idx++ ) {
		push_back( qu, &ar[idx],sizeof(int));
	}
	/*test get_queue_front */
	ret = get_queue_front(qu);
	printf("get_queue_front : %d\n",*(int *)(((struct qu_content *)ret)->content));
	
	/*test get_queue_size()*/
	printf("current get_queue_size : %d\n",get_queue_size(qu));
	
	/*test pop() */
	pop_front(qu);
	pop_front(qu);
	ret = get_queue_front(qu);
	printf("get_queue_front : %d\n",*(int *)(((struct qu_content *)ret)->content));

	/*test get_queue_empty()*/
	pop_front(qu);
	pop_front(qu);
	pop_front(qu);
	printf("get_queue_empty : %d \n",get_queue_empty(qu));	
	ret = get_queue_front(qu);
	if (NULL == ret) {
		printf("It empty now! \n");
	} else {
		printf("get_queue_front : %d\n",*(int *)(((struct qu_content *)ret)->content));
	}
	/*test queue_destroy()*/
	queue_destroy(qu);
	printf("clean up ~ \n");

return 0;
}
