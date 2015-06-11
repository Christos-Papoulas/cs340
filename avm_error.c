#include <stdio.h>

extern unsigned char 	executionFinished ;

void avm_warning(char* format, ...){

	fprintf(stderr,"\n Warning: %s ",format);
	return;
}

void avm_error(char* format, ...){
	
	fprintf(stderr,"\n Error: %s ",format);
	executionFinished=1;
	return;
}