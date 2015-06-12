#ifndef _AVM_MEM_H_
#define _AVM_MEM_H_

#include <string.h>
#include "final_code.h"
#include "const.h"
#include "avm_table.h"

#define AVM_STACKSIZE 4096
#define AVM_STACKENV_SIZE 4

#define AVM_NUMACTUALS_OFFSET 4
#define AVM_SAVEDPC_OFFSET 3
#define AVM_SAVEDTOP_OFFSET 2
#define AVM_SAVEDTOPSP_OFFSET 1

#define AVM_WIPEOUT(m) memset(&(m),0,sizeof(m))

typedef enum avm_Memcell_t{
   integer_m,//0
   double_m, //1
   string_m, //2
   bool_m, //3
   table_m,//4
   userfunc_m,//5
   libfunc_m,//6
   nil_m,//7
   undef_m//8
} avm_memcell_t;

struct avm_table;

typedef struct avm_Memcell {
   avm_memcell_t type;
   union {
      double 		doubleVal;
      int 			intVal;
      char*		strVal;
      unsigned char boolVal;
      struct avm_table *tableVal;
      unsigned int funcVal;
      char* libfuncVal;   
   } data;
} avm_memcell;



extern avm_memcell ax, bx, cx;
extern avm_memcell retval;
extern unsigned int top, topsp;
avm_memcell stack[AVM_STACKSIZE];

void avm_initstack();
void avm_memcellclear(avm_memcell* m); 

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg);

void memclear_string (avm_memcell* m);
void memclear_table (avm_memcell* m);

//from avm_assign.c
void avm_assign(avm_memcell* lv, avm_memcell* rv);
#endif
