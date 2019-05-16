/***********************************
* Program code for count()
***********************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "util.h"

int count(int argc,char *argv[])
{
	FILE *fp = fopen( argv[1],"r" );
	if(argc != 2 ){
		printf( "Wrong Number of Argument!\n" );
		return 0;
	}else if( fp == NULL){
		printf( "Cannot open the file!\n" );
		return 0;
	}else{
		struct stat st;
		stat(argv[1], &st);
		int size = st.st_size;	
		char * string ;
		string= malloc (size);
		fread (string, 1, size, fp);  
		int words = 0,  lines = 1;

		if(string[0] != ' ' && string[0] != '\n' && string[0] != '\t' ) words++;

		for (int i = 1; i < size - 1; i++)
		{
			if (string[i] == '\n')   lines++;
			if(string[i] == ' ' || string[i] == '\n' || string[i] == '\t' ){
				
				if(string[i+1] != ' ' && string[i+1] != '\n' && string[i+1] != '\t' )
					words++;
			}
			

		}
		printf("%d %d %d %s\n",lines,words,size,argv[1]);
		fclose(fp);
		return 0;
	}
}