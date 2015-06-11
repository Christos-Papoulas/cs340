#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "avm_jmp.h"
#include "dispatcher.h"
#include "avm_mem.h"
#include "avm_tobool.h"

extern unsigned char 	executionFinished;
extern unsigned 		pc;
extern unsigned		currLine ;
extern unsigned		codeSize ;
extern instruction*	code;
/* avm_tobool.c: */
extern char* typeStrings[];
/* avm_mem.c: */
extern struct avm_Memcell ax,bx,cx;
extern struct avm_Memcell	retval;
extern unsigned top,topsp;

void execute_jne(instruction *instr) {
	assert(instr->result->type == label_a);
	
	avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
	avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);
	
	unsigned char result = 0;

	if(rv1->type == undef_m || rv2->type == undef_m){
		avm_error("undef involved in equality!\n");
		executionFinished =1;
	}
	else if (rv1->type == nil_m || rv2->type == nil_m)
		result = rv1->type != nil_m && rv2->type != nil_m;
	else if (rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1)!=avm_tobool(rv2));
	else if (rv1->type != rv1->type)
		avm_error("%s == %s is illegal!\n",
		typeStrings[rv1->type],
		typeStrings[rv2->type]);
	else{
		/*equality check with dispatching*/
		if(rv1->type == integer_m && rv2->type == integer_m)
	 		result = rv1->data.intVal != rv2->data.intVal;
	 	if(rv1->type == double_m && rv2->type == double_m)
	 		result = rv1->data.doubleVal != rv2->data.doubleVal;
	 	if(rv1->type == integer_m && rv2->type == double_m)
	 		 result = rv1->data.intVal != rv2->data.doubleVal;
	 	if(rv1->type == double_m && rv2->type == integer_m)
	 		result = rv1->data.doubleVal != rv2->data.intVal;
	 	if(rv1->type == string_m )
	 		result = strcmp(rv1->data.strVal,rv2->data.strVal); 
      	if(rv1->type == table_m)
	 		result = (rv1->data.tableVal != rv2->data.tableVal);	 
      	if(rv1->type == userfunc_m)
	 		result = rv1->data.funcVal != rv2->data.funcVal ;
      	if(rv1->type == libfunc_m){
	 		result = strcmp(rv1->data.libfuncVal, rv2->data.libfuncVal);
      }
	}
	
	if(!executionFinished && result)
		pc = instr->result->val;
}

void execute_jle(instruction *instr) {
	assert(instr->result->type == label_a);
	
	avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
	avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);
	
	unsigned char result = 0;

	if(rv1->type == undef_m || rv2->type == undef_m){
		avm_error("undef involved in equality!\n");
		executionFinished =1;
	}
	else if (rv1->type == nil_m || rv2->type == nil_m)
		result = rv1->type <= nil_m && rv2->type <= nil_m;
	else if (rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1)<=avm_tobool(rv2));
	else if (rv1->type != rv1->type)
		avm_error("%s == %s is illegal!\n",
		typeStrings[rv1->type],
		typeStrings[rv2->type]);
	else{
		/*equality check with dispatching*/
		if(rv1->type == integer_m && rv2->type == integer_m)
	 		result = rv1->data.intVal <= rv2->data.intVal;
	 	if(rv1->type == double_m && rv2->type == double_m)
	 		result = rv1->data.doubleVal <= rv2->data.doubleVal;
	 	if(rv1->type == integer_m && rv2->type == double_m)
	 		 result = rv1->data.intVal <= rv2->data.doubleVal;
	 	if(rv1->type == double_m && rv2->type == integer_m)
	 		result = rv1->data.doubleVal <= rv2->data.intVal;
	 	if(rv1->type == string_m )
	 		result = strcmp(rv1->data.strVal,rv2->data.strVal); 
      	if(rv1->type == table_m)
	 		result = (rv1->data.tableVal <= rv2->data.tableVal);	 
      	if(rv1->type == userfunc_m)
	 		result = rv1->data.funcVal == rv2->data.funcVal ;
      	if(rv1->type == libfunc_m){
	 		result = strcmp(rv1->data.libfuncVal, rv2->data.libfuncVal);
      }
	}
	if(!executionFinished && result)
		pc = instr->result->val;
}

void execute_jge(instruction *instr) {
	assert(instr->result->type == label_a);
	
	avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
	avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);
	
	unsigned char result = 0;

	if(rv1->type == undef_m || rv2->type == undef_m){
		avm_error("undef involved in equality!\n");
		executionFinished =1;
	}
	else if (rv1->type == nil_m || rv2->type == nil_m)
		result = rv1->type >= nil_m && rv2->type >= nil_m;
	else if (rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1) >=avm_tobool(rv2));
	else if (rv1->type != rv1->type)
		avm_error("%s == %s is illegal!\n",
		typeStrings[rv1->type],
		typeStrings[rv2->type]);
	else{
		/*equality check with dispatching*/
		if(rv1->type == integer_m && rv2->type == integer_m)
	 		result = rv1->data.intVal >= rv2->data.intVal;
	 	if(rv1->type == double_m && rv2->type == double_m)
	 		result = rv1->data.doubleVal >= rv2->data.doubleVal;
	 	if(rv1->type == integer_m && rv2->type == double_m)
	 		 result = rv1->data.intVal >= rv2->data.doubleVal;
	 	if(rv1->type == double_m && rv2->type == integer_m)
	 		result = rv1->data.doubleVal >= rv2->data.intVal;
	 	if(rv1->type == string_m )
	 		result = strcmp(rv1->data.strVal,rv2->data.strVal); 
      	if(rv1->type == table_m)
	 		result = (rv1->data.tableVal >= rv2->data.tableVal);	 
      	if(rv1->type == userfunc_m)
	 		result = rv1->data.funcVal >= rv2->data.funcVal ;
      	if(rv1->type == libfunc_m){
	 		result = strcmp(rv1->data.libfuncVal, rv2->data.libfuncVal);
      }
	}
	if(!executionFinished && result)
		pc = instr->result->val;
}

void execute_jlt(instruction *instr) {
	assert(instr->result->type == label_a);
	
	avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
	avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);
	
	unsigned char result = 0;
	//printf("segmentations\n");
	if(rv1->type == undef_m || rv2->type == undef_m){
		avm_error("undef involved in equality!\n");
		executionFinished =1;
	}
	else if (rv1->type == nil_m || rv2->type == nil_m)
		result = rv1->type < nil_m && rv2->type < nil_m;
	else if (rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1) < avm_tobool(rv2));
	else if (rv1->type != rv1->type)
		avm_error("%s == %s is illegal!\n",
		typeStrings[rv1->type],
		typeStrings[rv2->type]);
	else{
		/*equality check with dispatching*/
		if(rv1->type == integer_m && rv2->type == integer_m)
	 		result = rv1->data.intVal < rv2->data.intVal;
	 	if(rv1->type == double_m && rv2->type == double_m)
	 		result = rv1->data.doubleVal < rv2->data.doubleVal;
	 	if(rv1->type == integer_m && rv2->type == double_m)
	 		 result = rv1->data.intVal < rv2->data.doubleVal;
	 	if(rv1->type == double_m && rv2->type == integer_m)
	 		result = rv1->data.doubleVal < rv2->data.intVal;
	 	if(rv1->type == string_m )
	 		result = strcmp(rv1->data.strVal,rv2->data.strVal); 
      	if(rv1->type == table_m)
	 		result = (rv1->data.tableVal < rv2->data.tableVal);	 
      	if(rv1->type == userfunc_m)
	 		result = rv1->data.funcVal < rv2->data.funcVal ;
      	if(rv1->type == libfunc_m){
	 		result = strcmp(rv1->data.libfuncVal, rv2->data.libfuncVal);
      }
	}
	if(!executionFinished && result)
		pc = instr->result->val;
}

void execute_jgt(instruction *instr) {
	assert(instr->result->type == label_a);
	
	avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
	avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);
	
	unsigned char result = 0;

	if(rv1->type == undef_m || rv2->type == undef_m){
		avm_error("undef involved in equality!\n");
		executionFinished =1;
	}
	else if (rv1->type == nil_m || rv2->type == nil_m)
		result = rv1->type > nil_m && rv2->type > nil_m;
	else if (rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1)>avm_tobool(rv2));
	else if (rv1->type != rv1->type)
		avm_error("%s == %s is illegal!\n",
		typeStrings[rv1->type],
		typeStrings[rv2->type]);
	else{
		/*equality check with dispatching*/
		if(rv1->type == integer_m && rv2->type == integer_m)
	 		result = rv1->data.intVal > rv2->data.intVal;
	 	if(rv1->type == double_m && rv2->type == double_m)
	 		result = rv1->data.doubleVal > rv2->data.doubleVal;
	 	if(rv1->type == integer_m && rv2->type == double_m)
	 		 result = rv1->data.intVal > rv2->data.doubleVal;
	 	if(rv1->type == double_m && rv2->type == integer_m)
	 		result = rv1->data.doubleVal > rv2->data.intVal;
	 	if(rv1->type == string_m )
	 		result = strcmp(rv1->data.strVal,rv2->data.strVal); 
      	if(rv1->type == table_m)
	 		result = (rv1->data.tableVal > rv2->data.tableVal);	 
      	if(rv1->type == userfunc_m)
	 		result = rv1->data.funcVal > rv2->data.funcVal ;
      	if(rv1->type == libfunc_m){
	 		result = strcmp(rv1->data.libfuncVal, rv2->data.libfuncVal);
      }
	}
	if(!executionFinished && result)
		pc = instr->result->val;
}

void execute_jeq(instruction* instr) {
	assert(instr->result->type == label_a);
	
	avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
	avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);
	
	unsigned char result = 0;

	if(rv1->type == undef_m || rv2->type == undef_m){
		avm_error("undef involved in equality!\n");
		executionFinished =1;
	}
	else if (rv1->type == nil_m || rv2->type == nil_m)
		result = rv1->type == nil_m && rv2->type == nil_m;
	else if (rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1)==avm_tobool(rv2));
	else if (rv1->type != rv1->type)
		avm_error("%s == %s is illegal!\n",
		typeStrings[rv1->type],
		typeStrings[rv2->type]);
	else{
		/*equality check with dispatching*/
		if(rv1->type == integer_m && rv2->type == integer_m)
	 		result = rv1->data.intVal == rv2->data.intVal;
	 	if(rv1->type == double_m && rv2->type == double_m)
	 		result = rv1->data.doubleVal == rv2->data.doubleVal;
	 	if(rv1->type == integer_m && rv2->type == double_m)
	 		 result = rv1->data.intVal == rv2->data.doubleVal;
	 	if(rv1->type == double_m && rv2->type == integer_m)
	 		result = rv1->data.doubleVal == rv2->data.intVal;
	 	if(rv1->type == string_m )
	 		result = !strcmp(rv1->data.strVal,rv2->data.strVal); 
      	if(rv1->type == table_m)
	 		result = (rv1->data.tableVal == rv2->data.tableVal);	 
      	if(rv1->type == userfunc_m)
	 		result = rv1->data.funcVal == rv2->data.funcVal ;
      	if(rv1->type == libfunc_m){
	 		result = !strcmp(rv1->data.libfuncVal, rv2->data.libfuncVal);
      }
	}
	if(!executionFinished && result)
		pc = instr->result->val;
		
	return;
}

void execute_jump(instruction* instr) {
	assert(instr->result->val >=0 && instr->result->val < codeSize);
	if(!executionFinished)
	  pc = instr->result->val;
	return;
}
