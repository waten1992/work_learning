list_entry()  总结

/* Get typed element from list at a given position.  */
# define list_entry(ptr, type, member) \
  ((type *) ((char *) (ptr) - (unsigned long) (&((type *) 0)->member)))

  1-(unsigned long) (&((type *) 0)->member) 是相对struct type 的地址；
  2-(type *) ((char *) (ptr) 是当前的类型指针的地址；
  3- 上面的相减 就得到了struct  type 的首地址，与member 放在结构体内的位置无关；

  测试用例见:list_entry_test.c

  ./test
  hwg@debian:~/tmp/list_entry(0)$ ./test
test: 0xb62caf60
 num: 0xb62caf70
 price : 0xb62caf78
tmp : 0xb62caf60
  (struct node *)((char *)p): 0xb62caf60
 start: 0x0
sizeof(struct node) : 32
tmp->num : 12 , tmp->price: 9.000000
