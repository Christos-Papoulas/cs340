
#include "execute.h"


library_func_t libfuncs[] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0
};

char *strlibfuncs[] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0
};

unsigned int totalActuals = 0;

void execute_call(instruction *instr) {
	avm_memcell* func = avm_translate_operand(instr->result,&ax);
	assert(func);
	avm_callseveenvironment();
	
	switch(func->type) {
		case userfunc_m:
			pc=func->data.funcVal;
			assert(pc<AVM_ENDING_PC);
			assert(code[pc].opcode==funcenter_v);
			break;
		
		case string_m: 	
			avm_calllibfunc(func->data.strVal); 
			break;

		case libfunc_m:	
			avm_calllibfunc(func->data.libfuncVal);
			break;

		default:
			avm_error("call: cannot bind %s to fuction!\n", avm_tostring(func));
			executionFinished=1;
			break;
	}
}

void avm_dec_top(void) {
	if(!top) {
		avm_error("stack overflow\n");
		executionFinished=1;
	} else
		top--;
}

void avm_push_envvalue(unsigned int val){
	stack[top].type			= integer_m;
	stack[top].data.intVal	= val;
	avm_dec_top();
}

void avm_callseveenvironment() {
	avm_push_envvalue(totalActuals);
	avm_push_envvalue(pc+1);
	avm_push_envvalue(top+totalActuals+2);
	avm_push_envvalue(topsp);
}

void execute_funcenter(instruction *instr) {
	avm_memcell* func=avm_translate_operand(instr->result, &ax);
	assert(func);
	assert(pc==func->data.funcVal);
	
	/* callee actions here */
	totalActuals=0;
 
	userfunc_p* funcInfo = avm_getfuncinfo(pc);
	  
	topsp = top;
	if(funcInfo)
		top = top - funcInfo->localSize; 
	//printf("top [%d]\n",top);
	//printf("localSize [%d]\n\n",funcInfo->localSize);
}

unsigned int avm_get_envvalue(int a) {
 	assert(stack[a].type == integer_m);

   	unsigned int val = (int)stack[a].data.intVal; 
   	assert(stack[a].data.intVal == (int)val);
   	
   	return val;
}

void execute_funcexit(instruction* unused){
	unsigned oldTop = top;
	top 	= avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
	pc  	= avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
	topsp	= avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
	
	while(oldTop++ <= top)
		avm_memcellclear(&stack[oldTop]);
}

userfunc_p* avm_getfuncinfo(unsigned int address) {
	userfunc_p* k;
	//userfunc_p

	k=getserfunction2(address);
	if (k){
	  // printf("found k\n");
	  return k;
	}
	return NULL;
}

void avm_calllibfunc (char *id) {
	library_func_t f = avm_getlibraryfunc(id);
	
	if(!f) {
		avm_error("unsupported lib func %s called!\n",id);
		executionFinished = 1;
	} else {
		topsp=top;
		totalActuals=0;
		
		(*f)();
		
		if(!executionFinished)
			execute_funcexit((instruction*)0);
	}
}

library_func_t avm_getlibraryfunc(char* id) {
	int i;
 	for(i=0;i<3;i++)
  	if(!strcmp(id,strlibfuncs[i]))
 			return(libfuncs[i]);
	 		
   return((library_func_t)0);
}

/* for push arg*/
void execute_pusharg(instruction* i) {
	avm_memcell* arg = avm_translate_operand(i->result,&ax);
	assert(arg);
  	
	avm_assign(&stack[top],arg);
	totalActuals++;
	avm_dec_top();
	return;	
}

/* for lib functions */
void avm_registerlibfunc(char *id, library_func_t addr) {
   int i;

   for(i=0; i<12; i++)
      if(libfuncs[i]==0){
	 	libfuncs[i] = addr;
	 	strlibfuncs[i] = strdup(id);
	 	return;
      }

   return;
}

avm_memcell* avm_getactual(unsigned int i){
	assert(i < avm_totalactuals());
	return (&stack[topsp +AVM_STACKENV_SIZE+1+i]);
}

unsigned int avm_totalactuals(void) {
	return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}