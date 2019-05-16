/******************************
* Program code for doStr()
******************************/
#include "doStr.h"
char* doStr()
{
	/*---------------------------------------- */
	// Can We do something like this?
	char string[] = "Hello World!";
	string[0] = 'C';

	/*---------------------------------------- */
	
	char *output = malloc(sizeof(string)/sizeof(char));
	strcpy(output,string);
	return output;

}
