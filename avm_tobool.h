#ifndef AVM_TOBOOL_H_
#define AVM_TOBOOL_H_

#include "avm_mem.h"

#include "final_code.h"


typedef unsigned char (*tobool_func_t) (avm_memcell*);

unsigned char int_tobool (avm_memcell* m);
unsigned char double_tobool (avm_memcell* m);
unsigned char string_tobool(avm_memcell* m);
unsigned char bool_tobool(avm_memcell* m);
unsigned char table_tobool(avm_memcell* m);
unsigned char userfunc_tobool(avm_memcell* m);
unsigned char libfunc_tobool(avm_memcell* m);
unsigned char nil_tobool(avm_memcell* m);
unsigned char undef_tobool(avm_memcell* m);
unsigned char avm_tobool(avm_memcell* m);

#endif 