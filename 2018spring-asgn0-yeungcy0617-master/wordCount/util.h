/***************************************************
* A utility for saving stdout/stderr for unit test
* DO NOT MODIFY!
*
* Adapted from MicBrain/Git-Sample
***************************************************/

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int fake_print(char* fmt, ...);
int fake_fprint(FILE* stream, char* fmt, ...);

/* In testing mode (initialized with -DTESTING fed to gcc and done automatically
 * when you run make beargit-unittest), we need to replace printf and fprintf 
 * with "fakes" that redirect your output to files, which you can read from 
 * in your testing code.
 */
#ifdef TESTING
#define printf fake_print
#define fprintf fake_fprint
#endif
