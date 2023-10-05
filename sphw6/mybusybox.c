#include<stdio.h>
#include<string.h>
#include<libgen.h>
#include<stdlib.h>

int main(int argc, char** argv){
	char exeBuf[4096] = "";
	char* exename = basename(argv[0]);
	strcat(exeBuf, exename);
	for(int i=1; i<argc; i++){
	    strcat(exeBuf, " ");
	    strcat(exeBuf, argv[i]);
	}
	//printf("%s\n", exename);
	system(exeBuf);
	
	return 0;
}
