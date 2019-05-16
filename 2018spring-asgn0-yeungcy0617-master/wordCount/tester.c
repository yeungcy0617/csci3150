/**************************************************
* Tester for your code.
* DO NOT MODIFY
* 
**************************************************/
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "count.h"

#undef printf
#undef fprintf

#define PERMARK 20

int init_suite(void) { return 0; }
int clean_suite(void) {
  unlink("TEST_STDOUT");
  unlink("TEST_STDERR");
  unlink("tmp.txt");

  return 0; }

void checkTwoOutputs(char *input1,char* input2)
{
  char line[1024],line2[1024];
  FILE* subFS = fopen(input1,"r");
  FILE* demoFS = fopen(input2,"r");
  CU_ASSERT_PTR_NOT_NULL_FATAL(subFS);
  CU_ASSERT_PTR_NOT_NULL_FATAL(demoFS);
  CU_ASSERT_PTR_NOT_NULL(fgets(line,1024,subFS));
  CU_ASSERT_PTR_NOT_NULL(fgets(line2,1024,demoFS));

  CU_ASSERT_STRING_EQUAL(line,line2); // Check if output matches.

  fclose(subFS);
  fclose(demoFS);
}
void testcase1(void)
{
  // Test for invalid file
  char* argv[] = {"wc","hello.txt",NULL};
  int argc = sizeof(argv)/sizeof(char*) -1;
  count(argc,argv);
  system("./mywc_demo hello.txt > tmp.txt");
  checkTwoOutputs("TEST_STDOUT","tmp.txt");
}

void testcase2(void)
{
  // Test for invalid file
  char* argv[] = {"wc","404",NULL};
  int argc = sizeof(argv)/sizeof(char*) -1;
  count(argc,argv);
  system("./mywc_demo 404 > tmp.txt");

  checkTwoOutputs("TEST_STDOUT","tmp.txt");
}

void testcase3(void)
{
  // Test for invalid argument
  char* argv[] = {"wc",NULL};
  int argc = sizeof(argv)/sizeof(char*) -1;
  count(argc,argv);
  system("./mywc_demo > tmp.txt");

  checkTwoOutputs("TEST_STDOUT","tmp.txt");
}

void testcase4(void)
{
  // Test for data1.txt
  char* argv[] = {"wc","testcases/data1.txt",NULL};
  int argc = sizeof(argv)/sizeof(char*) -1;
  count(argc,argv);
  system("./mywc_demo testcases/data1.txt > tmp.txt");

  checkTwoOutputs("TEST_STDOUT","tmp.txt");
}

void testcase5(void)
{
  // Test for data1.txt
  char* argv[] = {"wc","testcases/data2.txt",NULL};
  int argc = sizeof(argv)/sizeof(char*) -1;
  count(argc,argv);
  system("./mywc_demo testcases/data2.txt > tmp.txt");

  checkTwoOutputs("TEST_STDOUT","tmp.txt");
}


int main ( void )
{

  printf("\n\n**CSCI3150 Assignment 0 Tester**\n");
  printf("Mark per Suite: [%d]\n\n",PERMARK);

	CU_pSuite pSuite = NULL;
  CU_pSuite pSuite2 = NULL;
  CU_pSuite pSuite3 = NULL;
  CU_pSuite pSuite4 = NULL;
  CU_pSuite pSuite5 = NULL;

	if ( CUE_SUCCESS != CU_initialize_registry() )
	      return CU_get_error();
	pSuite = CU_add_suite( "TestCase1: hello.txt", init_suite, clean_suite );
   	if ( NULL == pSuite ) {
      		CU_cleanup_registry();
      		return CU_get_error();
   }
	if (NULL == CU_add_test(pSuite, "Output Same as wc_demo?", testcase1))
	{
		CU_cleanup_registry();
		return CU_get_error();

	}

  pSuite2 = CU_add_suite( "TestCase2: Non Exist File", init_suite, clean_suite );
   	if ( NULL == pSuite2 ) {
      		CU_cleanup_registry();
      		return CU_get_error();
   }
	if (NULL == CU_add_test(pSuite2, "Error Message Printed?", testcase2))
	{
		CU_cleanup_registry();
		return CU_get_error();

	}

  pSuite3 = CU_add_suite( "TestCase3: Invalid Argument Numbers", init_suite, clean_suite );
    if ( NULL == pSuite3 ) {
          CU_cleanup_registry();
          return CU_get_error();
   }
  if (NULL == CU_add_test(pSuite3, "Error Message Printed?", testcase3))
  {
    CU_cleanup_registry();
    return CU_get_error();

  }

  pSuite4 = CU_add_suite( "TestCase4: testcases/data1.txt", init_suite, clean_suite );
    if ( NULL == pSuite4 ) {
          CU_cleanup_registry();
          return CU_get_error();
   }
  if (NULL == CU_add_test(pSuite4, "Output same as wc_demo?", testcase4))
  {
    CU_cleanup_registry();
    return CU_get_error();

  }

  pSuite5 = CU_add_suite( "TestCase5: testcases/data2.txt", init_suite, clean_suite );
    if ( NULL == pSuite5 ) {
          CU_cleanup_registry();
          return CU_get_error();
   }
  if (NULL == CU_add_test(pSuite5, "Output same as wc_demo?", testcase5))
  {
    CU_cleanup_registry();
    return CU_get_error();

  }



	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_basic_show_failures(CU_get_failure_list());

  int total = CU_get_number_of_tests_run();
  int success =  total -  CU_get_number_of_tests_failed();

  printf("\n\n#######################################\n");
  printf("# Cases Passed: [%d]/[%d]%16s\n",success,total,"#");
  printf("# Score for Assignment 0: [%03d]/[%d] #\n",success * PERMARK,total * PERMARK);
  printf("#######################################\n");
	 CU_cleanup_registry();

   	return CU_get_error();
}
