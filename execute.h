#ifndef _EXECUTE_H_
#define _EXECUTE_H_

#include "avm_mem.h"
#include "dispatcher.h"
#include "const.h"
#include "avm_string.h"

extern unsigned int totalActuals;

typedef void (*library_func_t)(void);


void execute_call(instruction *instr);
void avm_dec_top(void);
void avm_push_envvalue(unsigned int val);
void avm_callseveenvironment();
void execute_funcenter(instruction *instr);
unsigned int avm_get_envvalue(int a);
void execute_funcexit(instruction* unused);
userfunc_p* avm_getfuncinfo(unsigned int address);


void avm_calllibfunc (char *);
library_func_t avm_getlibraryfunc(char* );

avm_memcell* avm_getactual(unsigned int i);

unsigned int avm_totalactuals( );
#endif