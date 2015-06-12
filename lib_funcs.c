#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "lib_funcs.h"
#include "avm_mem.h"
#include "avm_error.h"
#include "avm_table.h"
#include "execute.h"

extern struct avm_Memcell	retval;
extern unsigned top,topsp;

/*extern apo avm_tobool.c*/
extern char* typeStrings[];

void libfunc_typeof() {
	
	unsigned int n= avm_totalactuals();
	
	if(n!=1)
		avm_error("one argument not (%d) expected in typeof!\n",n);
	else{
		avm_memcellclear(&retval);
		retval.type= string_m;
		retval.data.strVal=strdup(typeStrings[avm_getactual(0)->type]);
	}
}

void libfunc_totalarguments() {
	/* get topsp of previous activation record*/
	unsigned int p_topsp = avm_get_envvalue(topsp+AVM_SAVEDTOPSP_OFFSET);
	avm_memcellclear(&retval);
	
	if(!p_topsp){
		avm_error("total arguments called outside a fuction\n");
		retval.type= nil_m;
	}
	else{
		retval.type =integer_m;
		retval.data.intVal = avm_get_envvalue(p_topsp+AVM_NUMACTUALS_OFFSET);	
	}
}

void libfunc_print(){
	
	unsigned int n=avm_totalactuals();
	unsigned int i=0;

	while(i<n){
		char* s= avm_tostring(avm_getactual(i));
		puts(s);
		free(s);
		i++;
	}
}
