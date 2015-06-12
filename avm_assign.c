#include <assert.h>
#include "avm_mem.h"
#include "avm_table.h"
#include "avm_error.h"

extern struct avm_Memcell ax,bx,cx;
extern struct avm_Memcell	retval;
extern unsigned top,topsp;

void avm_assign(avm_memcell* lv, avm_memcell* rv) {
   if(lv->type == table_m && rv->type == table_m &&
      lv->data.tableVal == rv->data.tableVal)
      return;

   if(rv->type == undef_m) {
      avm_warning("Runtime exception: assigning from \'undef\' content");
   }
   
   avm_memcellclear(lv);
   memcpy(lv,rv,sizeof(avm_memcell));
   
   assert(lv->type != undef_m);
   
   if(lv->type == string_m) {
      lv->data.strVal = strdup(rv->data.strVal);
   } else if(lv->type == table_m) {
      avm_tableincrefcounter(lv->data.tableVal);
   } 

   return;
}

void execute_assing(instruction* instr) {
   avm_memcell* lv = avm_translate_operand(instr->result,(avm_memcell*)0);
   avm_memcell* rv = avm_translate_operand(instr->arg1,&ax);

   assert(lv && (&stack[top] < lv && &stack[AVM_STACKSIZE-1] >= lv || 1 ||
      lv == &retval || lv == &ax || lv == &bx
   ));
   assert(rv);

   avm_assign(lv,rv);

   return;
}
