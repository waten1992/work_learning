#include "my_stack.h" 
#include "stack.h"

#define 	CAPACITY	4

int
main()
{
	int ar[] = {1,2,3,4};
	int idx ;
	void *ret;
	struct  stack *st;
	st = stack_constructor(sizeof(int), CAPACITY);
	for (idx = 0; idx < sizeof(ar)/sizeof(ar[0]); idx++ ) {
		push( st, &ar[idx],sizeof(int));
	}
	/*test get_stack_top */
	ret = get_stack_top(st);
	printf("get_stack_top : %d\n",*(int *)ret);
	
	/*test get_stack_size()*/
	printf("current get_stack_size : %d\n",get_stack_size(st));

	/*test pop() */
	pop(st);
	ret = get_stack_top(st);
	printf("get_stack_top : %d\n",*(int *)ret);

	/*test get_stack_empty()*/
	pop(st);
	pop(st);
	pop(st);
	pop(st);
	printf("get_stack_empty : %d \n",get_stack_empty(st));
	
	ret = get_stack_top(st);
	if (NULL == ret) {
		printf("It empty now! \n");
	} else {
		printf("get_stack_top : %d\n",*(int *)ret);
	}
	/*test stack_destroy()*/
	stack_destroy(st);
	printf("clean up ~ \n");

return 0;
}
