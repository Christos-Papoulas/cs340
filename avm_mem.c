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
   for(i = 0; i < AVM_STACKSIZE; ++i){
      AVM_WIPEOUT(stack[i]);
      stack[i].type = undef_m;
      assert(stack[i].type == undef_m);
   }
}

void avm_memcellclear(avm_memcell* m){
   memclear_func_t f ;

   if(m->type != undef_m && m->type != 4094){
      f = memclearFuncs[m->type];
      
      if(f)
	 	(*f)(m);
      m->type = undef_m;
   }
   return;
}

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg){
	switch(arg->type){
	
		case global_a:
			return (&stack[AVM_STACKSIZE-1-(arg->val)]);
		
		case local_a:	return (&stack[topsp-arg->val]);
		case formal_a:
			return &stack[topsp + AVM_STACKENV_SIZE + 1 + arg->val];

		case retval_a: 	
			return (&retval);
		case integer_a:
			reg->type = integer_m;
			reg->data.intVal = consts_getint(arg->val);
			return reg;
		
		case double_a:
			reg->type = double_m;
			reg->data.doubleVal = consts_getdouble(arg->val);
			return reg;
		
		case string_a:	
			reg->type = string_m;
			reg->data.strVal = (char*)consts_getstring(arg->val);
			return reg;
		
		case bool_a:
			reg->type =bool_m;
			reg->data.boolVal=arg->val;
			return reg;
		
		case nil_a:
			reg->type = nil_m;
			return reg;
		
		case userfunc_a:
			reg->type = userfunc_m;
			reg->data.funcVal=arg->val;
			return reg;
		
		case libfunc_a:
			reg->type = libfunc_m;
			reg->data.libfuncVal = (char*)libfuncs_getused(arg->val);
			return reg;
		
		default:
			assert(0);
		
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
