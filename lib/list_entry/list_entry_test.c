#include <stdio.h>

# define list_entry(ptr, type, member) \
	  ((type *) ((char *) (ptr) - (unsigned long) (&((type *) 0)->member)))

typedef struct list_head
{
	  struct list_head *next;
	  struct list_head *prev;
} list_t;

struct node {
	struct list_head list;
	int 	num;
	double 	price;
};

int 
main()
{
	struct node test, *tmp;
	struct list_head *list, *p;
	test.num = 12;
	test.price = 9.0;
	p = &test.list;
	printf("test: 0x%x \n num: 0x%x \n price : 0x%x \n",
			&test,
			&test.num , 
			&test.price);
	tmp = list_entry(p,struct node,list);
	printf("tmp : 0x%x \n  (struct node *)((char *)p): 0x%x \n start: 0x%x \n",
			tmp,
			(struct node *)((char *)p),
			(unsigned long) (&((struct node *) 0)->list));

	printf("sizeof(struct node) : %d \n",sizeof(struct node));
	printf("tmp->num : %d , tmp->price: %f \n",
			tmp->num,
			tmp->price);
return 0;
}
