/*******************************************
* Tester for your code.
* DO NOT MODIFY
*
*******************************************/
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include <stdio.h>
#include "doMath.h"
#include "doStr.h"

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }


void test_1(void) {
  CU_ASSERT_EQUAL( doMath(3,4), 81);

}

void test_2(void) {
  CU_ASSERT_STRING_EQUAL(doStr(),"Cello World!");
}
int main ( void )
{
	CU_pSuite pSuite = NULL;
	CU_pSuite pSuite2 = NULL;

	if ( CUE_SUCCESS != CU_initialize_registry() )
	      return CU_get_error();
	pSuite = CU_add_suite( "Testcase1: doMath()", init_suite, clean_suite );
   	if ( NULL == pSuite ) {
      		CU_cleanup_registry();
      		return CU_get_error();
   }
	if (NULL == CU_add_test(pSuite, "3^4 Gets correct values?", test_1))
	{
		CU_cleanup_registry();
		return CU_get_error();	

	}

	pSuite2 = CU_add_suite( "Testcase2: doStr()", init_suite, clean_suite );
   	if ( NULL == pSuite2 ) {
      		CU_cleanup_registry();
      		return CU_get_error();
   }
	if (NULL == CU_add_test(pSuite2, "Successfully Change First 'H' to 'C'?", test_2))
	{
		CU_cleanup_registry();
		return CU_get_error();

	}
	
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_basic_show_failures(CU_get_failure_list());
	 CU_cleanup_registry();
   	return CU_get_error();
}
