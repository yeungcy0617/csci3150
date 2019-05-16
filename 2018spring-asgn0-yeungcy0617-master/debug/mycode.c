/************************************
** Main Program for a Buggy Program

************************************/
#include <stdio.h>
#include "doMath.h"
#include "doStr.h"

int main(int argc,char *argv[]) {

	double res = (doMath(3,4));
	char* resStr = doStr();
        printf("res = %lf\n",res);
	printf("String is %s\n",resStr);
	return 0;
}
