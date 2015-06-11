#include <assert.h>
#include "avm_arithm.h"
#include "avm_mem.h"

extern struct avm_Memcell ax,bx,cx;
extern struct avm_Memcell	retval;
extern unsigned top,topsp;

typedef double(*arithmetic_func_t)(double x, double y);

double add_impl(double x, double y){
	return x+y;
}

double sub_impl(double x, double y){
	return x-y;
}

double mul_impl(double x, double y){
	return x*y;
}

double div_impl(double x, double y){
	assert(y);
	return x/y;
}

double mod_impl(double x, double y){
	return (((unsigned)x)%((unsigned)y));
}

arithmetic_func_t arithmeticFuncs [] = {
   add_impl,
   sub_impl,
   mul_impl,
   div_impl,
   mod_impl
};

void execute_arithmetic(instruction* instr) {
	avm_memcell* lv  = (avm_memcell*)avm_translate_operand(instr->result,(avm_memcell*)0);
	avm_memcell* rv1 = (avm_memcell*)avm_translate_operand(instr->arg1, &ax);
	avm_memcell* rv2 = (avm_memcell*)avm_translate_operand(instr->arg2, &bx);
	
	assert(lv && (&stack[top] <= lv && &stack[AVM_STACKSIZE] > lv || lv == &retval) );
  	assert(rv1 && rv2);

	if(rv1->type != integer_m || rv2->type != integer_m){
		avm_error("not a number in arithmetic!\n");
	} else {
		arithmetic_func_t op=arithmeticFuncs[instr->opcode-add_v];
		avm_memcellclear(lv);
		lv->type		= integer_m;
		lv->data.intVal	= (*op)(rv1->data.intVal, rv2->data.intVal);
	}
}
