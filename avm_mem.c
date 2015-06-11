#include "avm_mem.h"


avm_memcell ax,bx,cx;
avm_memcell retval;
unsigned int top, topsp;

typedef void (*memclear_func_t)(avm_memcell*);

memclear_func_t memclearFuncs [] = {
   0 /*int*/,
   0,/*double*/
   memclear_string,
   0 /*bool*/,
   memclear_table,
   0 /*userfunc*/,
   0 /*libfunc*/,
   0 /*nil*/ ,
   0 /*undef*/
};

void avm_initstack(){
   unsigned int i ;
   for(i=0; i<AVM_STACKSIZE; ++i){
      AVM_WIPEOUT(stack[i]);
      stack[i].type = undef_m ;
   }
}

void avm_memcellclear(avm_memcell* m){
   memclear_func_t f ;
   if(m->type != undef_m){
      f = memclearFuncs[m->type];
      
      if(f)
	 			(*f)(m);
      m->type = undef_m;
   }
   return;
}

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg){
	//printf("arg->type[%d]",arg->type);
	switch(arg->type){
	
		case global_a:{
		//	printf("AVM_STACKSIZE-1-(arg->val) %d\n",(AVM_STACKSIZE-1-(arg->val)));
			//printf("arg->val%d ",arg->val);
			return (&stack[AVM_STACKSIZE-1-(arg->val)]);
		}
		case local_a:	return (&stack[topsp-arg->val]);
		case formal_a:	return (&stack[topsp+AVM_STACKENV_SIZE+1+arg->val]);
		case retval_a: 	return (&retval);
		case integer_a:{
			///printf("mpika integer\n");
			reg->type = integer_m;
			reg->data.intVal = consts_getint(arg->val);
			//printf("aqs %d\n", reg->data.intVal);
			return reg;
		}
		case double_a:{
			reg->type = double_m;
			reg->data.doubleVal = consts_getdouble(arg->val);
			return reg;
		}
		case string_a:	{
			reg->type = string_m;
			reg->data.strVal=consts_getstring(arg->val);
			return reg;
		}
		case bool_a:{
			//printf("mpika sto bool.a\n");
			reg->type =bool_m;
			reg->data.boolVal=arg->val;
			return reg;
		}
		case nil_a:{
			reg->type = nil_m;
			return reg;
		}
		case userfunc_a:{
			//printf("gamiesai oti  \n");
			reg->type = userfunc_m;
			reg->data.funcVal=arg->val;
			return reg;
		}
		case libfunc_a:{
			//printf("gamiesai oti na nai \n");
			reg->type = libfunc_m;
			reg->data.libfuncVal = libfuncs_getused(arg->val);
			return reg;
		}
		default:{
		 //printf("arg->type [%d]\n",arg->type);
		 assert(0);
		}
	}
}

void memclear_string (avm_memcell* m){
   assert(m->data.tableVal);
   free(m->data.strVal);
   return;
}

void memclear_table (avm_memcell* m){
   assert(m->data.tableVal);
   avm_tabledecrefcounter(m->data.tableVal);
   return;
}
