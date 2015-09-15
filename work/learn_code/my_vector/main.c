#include "my_vector.h"
#include "vector.h"

#define     CAPACITY    8
#define 	TEST_NUM	12
#define 	TEST_CUR 	20

typedef struct test {
	int 	num;
	double	price;
}test_t;


int
vector_traversal(struct vector *v)
{
	int idx , tot_cnt ;
	test_t *tmp;
	tot_cnt = v->tot_cnt ;
	for (idx = 0; idx < tot_cnt ; idx++) {
		char *p = (char *)v->start + idx * v->ele_size;
		tmp = (test_t *)p;
		printf ("current element idx = %d,num: %d , price : %f ,tot_cnt = %d\n",
				idx,
				tmp->num,
				tmp->price,
				v->tot_cnt);
	}
	printf("****************************\n");
	return 0;
}

int
main()
{
	struct vector *tmp, *tmp_st;
	void *ret;
	int ar[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	int idx , cur_pos;
#if 1 /*test the struct */
	tmp_st = vector_constructor(sizeof(test_t),CAPACITY);
	test_t * ts = (test_t *)malloc(sizeof(test_t)*TEST_NUM);
	/*init the struct*/
	for (idx = 0; idx < TEST_NUM; idx++) {
		ts[idx].num = idx+1;
		ts[idx].price = 10.0+idx;
	}	
	/*test push_back*/
	for (idx = 0; idx < TEST_NUM; idx++ ) {
		push_back(tmp_st,&ts[idx],sizeof(test_t));
	}
	vector_traversal(tmp_st);
	/*test pop_back */
	pop_back(tmp_st);
	test_t  *t =(test_t *)tmp_st->end;
	printf ("pop an element ,last element num: %d , price : %f ,tot_cnt = %d\n",
			t->num,
			t->price,
			tmp_st->tot_cnt);
	vector_traversal(tmp_st);

	/*test get_vector_at() */
	cur_pos = TEST_CUR;
	ret = get_vector_at(tmp_st, cur_pos);
	t = (test_t *)ret;
	if ( NULL != ret ) {
		printf("TEST_CUR  num: %d ,price :%f \n", t->num, t->price);
	}
	
	/*test vector_erase_one_ele() */
	printf("$$$$$$$$--TEST vector_erase_one_ele()----$$$$\n");
	cur_pos = 2 ;
	ret = get_vector_at(tmp_st, cur_pos);
	t = (test_t *)ret;
	if ( NULL != ret ) {
		printf("before erase num: %d ,price :%f \n", t->num, t->price);
	}
	vector_erase_one_ele( tmp_st, cur_pos);
	ret = get_vector_at(tmp_st, cur_pos);
	t = (test_t *)ret;
	if ( NULL != ret ) {
		printf("after erase  num: %d ,price :%f \n", t->num, t->price);
	}
	vector_traversal(tmp_st);
	/*test vector_insert_one_ele() */
	printf("********TEST vector_insert_one_ele()************\n");
	test_t tt[1];
	tt[0].num = 64;
	tt[0].price = 32.5;
	vector_insert_one_ele(tmp_st,&tt,6);
	vector_traversal(tmp_st);

	/*test vector_clear() */
	vector_clear(tmp_st);
	printf("tot_cnt = %d , start_addr = 0x%x ,end_addr =0x%x \n",
			tmp_st->tot_cnt,
			tmp_st->start,
			tmp_st->end);

	if (vector_destroy(tmp_st) == -1) {
		fprintf(stderr,"vector_destroy if fail \n");
		return -1;
	}
	free(ts);
#endif

#if 0 /*test int ar[] */
	/*constructor */
	tmp = vector_constructor(sizeof(int),CAPACITY);
	printf("ele_size = %d \n capacity: %d \n before insert start addr :%x \n",
            tmp->ele_size,
            tmp->capacity,
			tmp->start);	
	/*test push_back() */
	for(idx = 0; idx < TEST_NUM; idx++) {
		push_back(tmp,&ar[idx],sizeof(int));
	}
    printf(" after insert  end addr : %x \n get_vector tot_size = %d \n", \
			get_vector_end(tmp),
			get_vector_size(tmp));
	
	/*test pop_back */
	pop_back(tmp);
	printf ("last element: %d \n",*(int *)get_vector_end(tmp));

	/*test get_vector_at() */
	cur_pos = TEST_CUR;
	ret = get_vector_at(tmp, cur_pos);
	if ( NULL != ret ) {
		printf("TEST_CUR : %d \n", *(int *)ret);
	}
	if (vector_destroy(tmp) == -1) {
		fprintf(stderr,"vector_destroy if fail \n");
		return -1;
	}
#endif
return 0;
}
