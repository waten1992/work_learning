#include "vector.h"

typedef struct vector {
	void 		*start_add;
	uint32_t 	ele_size;
	int 		tot_cnt;
	uint32_t 	cur;
	uint32_t	capacity;
	
}vector_t;


struct vector * 
constructor(uint32_t ele_size, uint32_t capacity)
{
	struct vector *v;
	uint32_t tot_size = ele_size * capacity;
	if (ele_size <= 0 || capacity <= 0 ) {
		fprintf(stderr,"constructor func para is error! \n");
		return NULL;
	}
	v = (struct vector *)malloc(sizeof(struct vector) + tot_size);
	if (NULL == )
}

int 
main()
{
	printf("hello \n");

return 0;
}
