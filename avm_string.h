#ifndef _AVM_STRING_H_
#define _AVM_STRING_H_

#include "avm_mem.h"

char* avm_tostring(avm_memcell* );

char* integer_tostring(avm_memcell* );
char* double_tostring(avm_memcell* );
char* string_tostring(avm_memcell* );
char* bool_tostring(avm_memcell* );
char* userfunc_tostring(avm_memcell* );
char* libfunc_tostring(avm_memcell* );
char* nil_tostring(avm_memcell* );
char* undef_tostring(avm_memcell* );
char* table_tostring(avm_memcell* );
#endif