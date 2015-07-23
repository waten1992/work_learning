#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include <pthread.h>
#include <unistd.h>

int init_suite1(void)
{
      return 0;
}

/* The suite cleanup function.
 *  * Closes the temporary file used by the tests.
 *   * Returns zero on success, non-zero otherwise.
 *    */
int clean_suite1(void)
{
      return 0;
}
void test_sem(void)
{
      CU_ASSERT(200 == cunit_test_main(100));
      CU_ASSERT(2200 == cunit_test_main(1000));
	  CU_ASSERT(22200 == cunit_test_main(10000));
	  CU_ASSERT(222200 == cunit_test_main(100000));
	  CU_ASSERT(2222200 == cunit_test_main(1000000));
}

/* The main() function for setting up and running the tests.
 *  * Returns a CUE_SUCCESS on successful running, another
 *   * CUnit error code on failure.
 *    */
int main()
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ((NULL == CU_add_test(pSuite, "test of sem()\n", test_sem)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
