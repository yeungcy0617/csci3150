/*
* CSCI3150 Assignment 1 - Writing a Simple Shell
* Feel free to modify the given code.
* Press Ctrl-D to end the program
*
*  You may put down your reference here:
*
*/

/* Header Declaration */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
/* Function Declaration */
int getUserInput(char* input);
int tokenizeInput(char* input);
int command(char* output);
char *getcwd(char *buf,size_t size);
int Counter=0;
char *characters[255] = {0};
int noerror=0;
// char *commandss[3][255];
/* Functions */
int main(int argc,char* argv[])
{
	signal(SIGINT,SIG_IGN);
	signal(SIGTERM,SIG_IGN);
	signal(SIGQUIT,SIG_IGN);
	signal(SIGTSTP,SIG_IGN);
	int AND1=1;
	int AND2=1;
	int AND1pos;
	int AND2pos;
	int OR1=1;
	int OR2=1;
	int OR1pos;
	int OR2pos;
	int isExit = 0;

	do {
		char rawInput[255];
		isExit = getUserInput(rawInput);
		if(isExit) break;
		char Input[3][255];
		char check[255][255];
		char check2[255][255];
		char tmpcat[255][255];
		char tmpcat2[255][255];
		char increase=0;
		char increase2=0;
		char *split;
		char noANDOR[255];

int stopsplit =0;
		strcpy(noANDOR, rawInput);
		split = strtok(rawInput," ");
		strcpy(check[increase],split);
		while(split != NULL){
			AND1 = strcmp(split,"&&");
			if( AND1 == 0 && stopsplit==0 ){
				AND1pos = increase;
				stopsplit =1;
			}
			OR1 = strcmp(split,"||" );
			if( OR1 == 0&& stopsplit==0){
				OR1pos = increase;
				stopsplit=1;
			}
			increase++;
			split = strtok(NULL," ");
			if(split != NULL){
				strcpy(check[increase],split);
			}
		}

		for(int k=0;k<255;k++){

			strcpy(tmpcat[k]," ");

		}

		if( OR1pos != 0 ){
			strcpy(Input[0],check[0]);
			for(int b = 1;b<OR1pos;b++){
				strcat(tmpcat[b],check[b]);
				strcat(Input[0],tmpcat[b]);
			}

			strcpy(Input[1],check[OR1pos+1]);
			for(int b =OR1pos+2;b<increase;b++){
				strcat(tmpcat[b],check[b]);
				strcat(Input[1],tmpcat[b]);
			}


		}

		if( AND1pos != 0 ){
			strcpy(Input[0],check[0]);
			for(int b = 1;b<AND1pos;b++){
				strcat(tmpcat[b],check[b]);
				strcat(Input[0],tmpcat[b]);
			}

			strcpy(Input[1],check[AND1pos+1]);
			for(int b =AND1pos+2;b<increase;b++){
				strcat(tmpcat[b],check[b]);
				strcat(Input[1],tmpcat[b]);
			}

		}
		// printf("::%s\n",Input[1] );
		split = strtok(Input[1]," ");
		if(split!=NULL){
			strcpy(check2[increase2],split);
		while(split != NULL){
			AND2 = strcmp(split,"&&");
			if( AND2 == 0 ){
				AND2pos = increase2;
			}
			OR2 = strcmp(split,"||");
			if( OR2 == 0){
				OR2pos = increase2;
			}
			increase2++;
			split = strtok(NULL," ");
			if(split != NULL){
				strcpy(check2[increase2],split);
			}
		}


		for(int p=0;p<255;p++){

			strcpy(tmpcat2[p]," ");

		}
// printf("%d\n", OR2pos);
		if( OR2pos != 0 ){
			strcpy(Input[1],check2[0]);
			for(int b = 1;b<OR2pos;b++){
				strcat(tmpcat2[b],check2[b]);
				strcat(Input[1],tmpcat2[b]);
			}
// printf("--%s\n", check2[OR2pos+1]);
			strcpy(Input[2],check2[OR2pos+1]);
			for(int b =OR2pos+2;b<increase;b++){
				strcat(tmpcat2[b],check2[b]);
				strcat(Input[2],tmpcat2[b]);
			}
		}
		if( AND2pos != 0 ){
			strcpy(Input[1],check2[0]);
			for(int b = 1;b<AND2pos;b++){
				strcat(tmpcat2[b],check2[b]);
				strcat(Input[1],tmpcat2[b]);
			}

			strcpy(Input[2],check2[AND2pos+1]);
			for(int b =AND2pos+2;b<increase2;b++){
				strcat(tmpcat2[b],check2[b]);
				strcat(Input[2],tmpcat2[b]);
			}
		}
		}

		// printf("0%s\n", Input[0]);
		// printf("1%s\n", Input[1]);
		// printf("2%s\n", Input[2]);
		if(OR1pos != 0){
			for (int a = 0; a < 3; ++a)
		{
			if(tokenizeInput(Input[a])!=1){
				break;
			}
		}
		}else 		if(AND1pos!= 0){
			for (int a = 0; a < 3; ++a)
		{
			if(tokenizeInput(Input[a])!=0){
				break;
			}
		}
		}
		else{
			tokenizeInput(noANDOR);

		}

	} while(isExit = 1);
	return 0;
}

/*
  GetUserInput()
  - To parse User Input and remove new line character at the end.
  - Copy the cleansed input to parameter.
  - Return 1 if encountered EOF (Ctrl-D), 0 otherwise.
*/
int getUserInput(char* input)
{
	char buf[255];
	char *s = buf;
	char cwd[PATH_MAX+1];

	if(getcwd(cwd,PATH_MAX+1) !=NULL)
	{
		printf("[3150 Shell:%s]=> ", cwd);
	}

	if(fgets(buf,255,stdin) == NULL)
	{
		putchar('\n');
		return 1;
	}
  // Remove \n
	for(;*s != '\n';s++);
		*s = '\0';

	strcpy(input,buf);
	return 0;
}
/*
  tokenizeInput()
  - Tokenize the string stored in parameter, delimiter is space
  - In given code, it only prints out the token.
  Please implement the remaining part.
*/

int tokenizeInput(char* input)
{
	char buf[255];
	char output[255];
	int bye;
	int push;
	int gofolder;
	int hello;
	int ifconfig;
	int dirs;
	int pop;
	char path1[255];
	int* nextempty;
	char cm[255];
	char tmp[255];
	char tmp2[255];
	char* current;
	char currenttmp[255];
	char des[255];
	char Directory[500][500];


	char path[PATH_MAX+1];

	strcpy(buf,input);

	char* token = strtok(buf," ");
	if(token != NULL)
	{
		strcpy(cm,token);
		bye = strcmp(token,"bye");
		push = strcmp(token,"push");
		gofolder = strcmp(token,"gofolder");
		hello = strcmp(token,"hello");
		dirs = strcmp(token,"dirs");
		pop = strcmp(token,"pop");
		if(bye == 0 ){
			token = strtok(NULL," ");
			if(token == NULL){
				exit(0);                                                                                                                             
			}
			printf("bye: wrong number of arguments\n");
		}
		else if( push == 0 ){
			token = strtok(NULL," ");
			if(token == NULL){
				printf("push: wrong number of arguments\n");
				noerror=1;
			}
			else{
				strcpy(des,token);
				token=strtok(NULL," ");
				if(token != NULL){
					printf("%s: wrong number of directory\n",cm);
					noerror=1;
				}
				else{
					if(getcwd(path,PATH_MAX+1)!= NULL){
						current = path;
						strcpy(currenttmp,current);	
						strcpy(Directory[Counter],current);

						if(chdir(des) != -1){
							if(getcwd(path,PATH_MAX+1) != NULL){
								for(int no=0;no<=Counter;no++){
									printf("%d %s\n",no,Directory[Counter-no]);
								}

							}
							Counter++;
						}
						else{
							printf("{%s}: cannot change directory\n",des);
							noerror=1;
						}
					}	
				}

			}
		}
		else if( dirs == 0 ){
			token = strtok(NULL," ");
			if(token != NULL){
				printf("%s: wrong number of arguments\n", cm);
				noerror=1;
			}
			else{

				for(int j=0;j<=Counter-1;j++){
					printf("%d %s\n",j,Directory[j]);
				}
			}
		}
		else if ( pop == 0 ){
			token = strtok(NULL," ");
			if(token == NULL){

				Counter--;
				strcpy(des,Directory[Counter]);
				if(chdir(des) != -1){
					for(int no=Counter;no>=Counter;no--){
						if(Counter>0){
							printf("%d %s\n",Counter-no,Directory[Counter-no]);
						}
					}
				}
				else{
					printf("%s: directory stack empty\n",cm);
					noerror=1;
				}
			}
			else{
				printf("%s: wrong number of arguments\n", cm);
				noerror=1;
			}


		}
		else if(gofolder == 0){
			token = strtok(NULL," ");
			if(token == NULL || strtok(NULL," ") != NULL){
				printf("%s: wrong number of arguments\n", cm);
				noerror=1;
			}
			else{
				strcpy(des,token);
				if(chdir(des) != -1){

				}

			}

		}

		else{

			if(token != NULL){
				int increment=0;
				while(token != NULL){
					// printf("%s\n", token);
					characters[increment] = token;
					//printf("%s\n",characters[increment]);
					token = strtok(NULL," ");
					increment++;
				}
				int status;
				int res;
				res = fork();
				if(res == 0){
					char tmp5[255] = "/bin/";
					strcat(tmp5,characters[0]);

					if(execvp(tmp5,characters)<0){
						char  tmp3[255]= "/usr/bin/";
						strcat(tmp3,characters[0]);
						

						if(execvp(tmp3,characters)<0){
							char  tmp4[255]= "./";
							strcat(tmp4,characters[0]);
							if(execvp(tmp4,characters)<0){
								printf("{%s}: command not found\n",characters[0] );
								exit(1);
							}
						}
					}
					exit(0);

				}else{
					waitpid(res,&status,WUNTRACED);
					noerror= WEXITSTATUS(status);
				}

			}
			

		}

	}
	return noerror;

}




int command(char* output){

	int and;
	int or;
	char* cmd = output;

	while(cmd != NULL){
		and = strcmp(output, "&&");
		or = strcmp(output, "||");
		break;
	}

	return 0;
}
