#ifndef _DISPATCHER_H_
#define _DISPATCHER_H_

#include "final_code.h"

#define AVM_MAX_INSTRUCTIONS nop_v
#define AVM_ENDING_PC codeSize

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

extern unsigned int	pc;
extern unsigned char 	executionFinished;
extern unsigned int	currLine;
extern unsigned int	codeSize;
extern instruction*	code;

typedef void (*execute_func_t)(instruction *);

void execute_assing(instruction*);
void execute_add(instruction*);
void execute_sub(instruction*);
void execute_mul(instruction*);
void execute_div(instruction*);
void execute_mod(instruction*);
void execute_jeq(instruction*);
void execute_jne(instruction*);
void execute_jle(instruction*);
void execute_jge(instruction*);
void execute_jlt(instruction*);
void execute_jgt(instruction*);
void execute_jump(instruction*);
void execute_call(instruction*);
void execute_pusharg(instruction*);
void execute_funcenter(instruction*);
void execute_funcexit(instruction*);
void execute_newtable(instruction*);
void execute_tablegetelem(instruction*);
void execute_tablesetelem(instruction*);
void execute_nop(instruction*);

void execute_cycle(void);

#endif