#include "dispatcher.h"

void execute_newtable(instruction* i){;}
void execute_tablegetelem(instruction* i){;}
void execute_tablesetelem(instruction* i){;}

execute_func_t executeFuncs[]={
	execute_assing, //0
	execute_add,
	execute_sub,
	execute_mul,
	execute_div,
	execute_mod, //5
	0,
	0,
	0,
	0,
	execute_jeq, //10
	execute_jne,
	execute_jgt,
	execute_jlt,
	execute_jge,
	execute_jle, //15
	execute_jump,
	execute_call,
	execute_funcenter,
	execute_funcexit,
	execute_newtable, //20
	execute_tablegetelem,
	execute_tablesetelem,
	execute_pusharg,
	//execute_nop //24
};

unsigned char 	executionFinished = 0;
unsigned int	pc = 0;
unsigned int	currLine = 0;
unsigned int	codeSize = 0;
instruction*	code=(instruction*) 0;

void execute_cycle(void) {
	unsigned int oldPc;
	if(executionFinished)
		return;
		
	else{
		if(pc==AVM_ENDING_PC){
			executionFinished =1;
			return;
		}
		else{
			assert(pc < AVM_ENDING_PC);
			instruction * instr = code+pc;
			//printf("AVM_ENDING_PC %d",AVM_ENDING_PC);
			//printf("opcode [%d]\n", instr->opcode);
			assert(instr->opcode>=0 && instr->opcode <= AVM_MAX_INSTRUCTIONS);
			
			if(instr->srcLine)
				currLine =  instr->srcLine;
				
				oldPc=pc;
				//printf("instr->opcode %d\n",instr->opcode);
				(*executeFuncs[instr->opcode])(instr);
				
			
			if(pc==oldPc)
				pc++;
			
		}
	}


}

