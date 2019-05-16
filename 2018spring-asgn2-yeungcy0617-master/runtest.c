#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<CUnit/Basic.h>
#include<sys/time.h>
#include"util.h"

int cmpID(const void *a, const void *b);

Point* generateDataset(int number, int dim,  float arg, int seed);


Point* points = NULL;  // This variable store the pointer that points at all the points.
Point* permissiblePoints = NULL;  // This variable store the pointer that points at all the permissible points.
int* checkPermissiblePointID = NULL; // 
int permissiblePointNum = 0;
int checkPermissiblePointNum = 0;
int iter = 0;

typedef struct testcase{
	int number;
	int dim;
	float arg;
	int seed;
	int threads;
	char result[100];
	char testcase[64];
} Testcase;

Testcase * testcases;

int init_test(Testcase test) {

//	Testcase test = testcases[iter];
	points = generateDataset(test.number, test.dim, test.arg, test.seed);
	if(points == NULL)
	{
		return -1;
	}
	FILE * file = fopen(test.result, "r");
	if(file == NULL){
		printf("cannot open %s\n", test.result);
		return -1;
	}
	
	int n = fscanf(file, "%d", &checkPermissiblePointNum);
	if(n != 1)
	{
		printf("READ ERROR: cannot read the number of permissible points in %s\n", test.result);
		return -1;
	}
	checkPermissiblePointID = (int*) malloc(sizeof(int) * checkPermissiblePointNum);
	if(checkPermissiblePointID == NULL) 
	{
		printf("CAN'T allocate memory for checkPermissiblePointID array!\n");
		return -1;
	}
	
	for(int i = 0; i < checkPermissiblePointNum; i++ )
	{
		n = fscanf(file,"%d",&checkPermissiblePointID[i]);
		if(n != 1){
			printf("READ ERROR: cannot read checkPermissiblePointID[%d]\n", i);
			return -1;
		}
	}
	return 0;
	
}

// It is used for cleaning the pointers.
int clean_test(void)
{
	if(points != NULL)
		free(points);
	points = NULL;
	if(checkPermissiblePointID != NULL)
		free(checkPermissiblePointID);
	checkPermissiblePointID = NULL;
	checkPermissiblePointNum = 0;

	if(permissiblePoints != NULL) 
		free(permissiblePoints);
	permissiblePoints = NULL;
	permissiblePointNum = 0;
	iter ++;  // Here we set iter ++, because we want to go next test case.
	return 0;
}

int init_suite(void){return 0;}
int clean_suite(void) {return 0;}

int testCase(void)
{
	struct timeval t_start, t_end;
	int threadNum;
	Testcase test = testcases[iter];

	int status = init_test(test);

	if(status == -1){
		clean_test();
		return 0;
	}
	if(test.threads != 0)
		threadNum = test.threads;
	gettimeofday(&t_start, NULL);

	permissiblePointNum = asgn2_pthread(points, &permissiblePoints, test.number, test.dim, threadNum);

	gettimeofday(&t_end, NULL);
	double t_ep = (t_end.tv_sec - t_start.tv_sec) * 1000000.0 + t_end.tv_usec - t_start.tv_usec;
	t_ep = t_ep / 1000000.0;
	printf("Time cost: %.4lfs\n", t_ep);
	
	if(permissiblePoints != NULL && permissiblePointNum != 0)
		qsort(permissiblePoints, permissiblePointNum, sizeof(Point), cmpID);

	if(permissiblePointNum != checkPermissiblePointNum){
		clean_test();
		return 0;
	} else {
		for(int i = 0; i < checkPermissiblePointNum; i++){  // Why we need to use -std=c99
			if(permissiblePoints[i].ID != checkPermissiblePointID[i]){
				clean_test();
				return 0;
			}
		}	

		clean_test();
		return 1;
	}
}


void test(void){
	CU_ASSERT(testCase());
}


int main(int agrc, char* argv[]){

	FILE * fr = fopen("./testcase/testsuite.txt","r");
	if( fr == NULL ){
		printf("ERROR: cannot open the inputfile.txt file.\n");
		exit(1);
	}
	int N;
	CU_pTest *tests = (CU_pTest*) malloc(sizeof(CU_pTest) * 13);
	testcases = (Testcase*)malloc(sizeof(Testcase) * 13);

	for(int i = 0; i < 13; i ++) {
		N = fscanf(fr, "%d %d %f %d %d %s", &testcases[i].number, &testcases[i].dim,
					&testcases[i].arg, &testcases[i].seed, &testcases[i].threads, testcases[i].result);
		if(i == 0){
			sprintf(testcases[i].testcase, "toyTestCase");
		} else if( i <= 10 ) {
			sprintf(testcases[i].testcase, "testcase%d", i);
		} else {
			sprintf(testcases[i].testcase, "bonusTest%d", i - 10);
		}
	}
	
	CU_pSuite pSuite = NULL;
	/* initialize the CUnit test registry */
	if(CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

		/* add a suite to the registry */
	pSuite = CU_add_suite("SUITE", init_suite, clean_suite);
	if(NULL == pSuite ){
		CU_cleanup_registry();
		return CU_get_error();
	}

	for(int i = 0; i < 13; i++){
		if((tests[i] = CU_add_test(pSuite, testcases[i].testcase, test)) == NULL) {
			CU_cleanup_registry();
			return CU_get_error();
		}
	}
	
	
	CU_basic_set_mode(CU_BRM_VERBOSE);
	
	int select;
//	CU_basic_run_tests();
	printf("Type '0' to run a toy testcase; Type a number of '1'~'12' to select a testcase; Type '13' to run all the 13 testcases: ");

	if((scanf("%d", &select)) != 1){
		printf("Please type a number of '0' ~ '13'!\n");
		return 0;
	}
	if( select == 13 ){
		CU_basic_run_tests();
	} else if(select >=0 && select <= 12) {
		iter += select;
		CU_basic_run_test(pSuite, tests[select]);
	} else {
		printf("Please type a number of '0' ~ '13'!\n");
		return 0;
	}

	CU_cleanup_registry();

//	printf("Finally, your score is %d!\n", score);

	free(testcases);
	return CU_get_error();
}
