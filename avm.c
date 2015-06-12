#include "avm.h"
#include "dispatcher.h"
#include "avm_mem.h"
#include "lib_funcs.h"

unsigned int 	glbnum;

void avm_initialize() {
	avm_initstack();
	avm_registerlibfunc("print", libfunc_print);
	avm_registerlibfunc("totalarguments", libfunc_totalarguments);
	avm_registerlibfunc("type_of", libfunc_typeof);
}

void execute(){
	avm_initialize();
	
	while(!executionFinished) {
		printf("execute  one cycle\n");
	    execute_cycle();
	}
	return ;
}

// for reading from binary
int has_arg1(int opcode)
{
	if(opcode == pusharg_v || opcode == call_v || opcode == jump_v || opcode == funcenter_v || opcode == funcexit_v || opcode == newtable_v)
		return 0;
	return 1;
}

int has_arg2(int opcode)
{
	if(opcode == pusharg_v || opcode == call_v || opcode == jump_v || opcode == funcenter_v || opcode == funcexit_v  
		|| opcode == assign_v || opcode == newtable_v)
		return 0;
	return 1;
}

void vm_read_VMArg(vmarg* arg, FILE *fp) {
	fread(&(arg->type),sizeof(int),1,fp);
	fread(&(arg->val),sizeof(int),1,fp);

 	if(arg->type == global_a){
      //printf("\n\nglobal metavliti %d\n\n",arg->val);
    }
   
   	if(arg->type == global_a && arg->val > glbnum)
      glbnum = arg->val; 
      
   
}

void vm_load_instr(instruction* instr, FILE *fp) {
	/* read operation code */
	FILE* read = fopen(".readbinary.txt", "a+");
	fread(&instr->opcode,sizeof(int),1,fp);
	fprintf(read, "opcode: %d\t", instr->opcode);
	/* read result */
	instr->result = new_vmarg();
	vm_read_VMArg(instr->result,fp);
	fprintf(read, "result type[%d] val[%d]\t", instr->result->type, instr->result->val);
	/* read argument 1 */

	if(has_arg1(instr->opcode))
	{
		instr->arg1 = new_vmarg();
		vm_read_VMArg(instr->arg1,fp);
		fprintf(read, "arg1 type[%d] val[%d]\t", instr->arg1->type, instr->arg1->val);
	}
	else
		instr->arg1 = NULL;
	/*read argument 2*/
	if(has_arg2(instr->opcode))
	{
		instr->arg2 = new_vmarg();
		vm_read_VMArg(instr->arg2,fp);
		fprintf(read, "arg2 type[%d] val[%d]\t", instr->arg2->type, instr->arg2->val);
	}
	else
		instr->arg2 = NULL;
	
	fprintf(read, "\n");
	if(read!=stdout && read!=NULL) fclose(read);
	
	return;
}


void read_binary_code() {
	FILE *fp;
	int magic = 0;
	int globals = -1;
	int  strsz, i;
	char *str = (char *)malloc(10*sizeof(char));
	int num;
	userfunc* func;
	int a;
	int code_Size;
	fp =  fopen("BinaryCode.abc","rb");
	if( fp== NULL) {
		fprintf(stderr, "Error opening file\n");
		return ;
	}
	/* read magic number */
	fread(&magic,sizeof(int),1,fp);
	if(magic != make_magic_number()) {
		fprintf(stderr,"Wrong File Format : File Not Alpha Binary Code \n");
		return ;
	}
	/* read the number of instructions */
   	fread(&codeSize,sizeof(int),1,fp);
  
   	code = malloc(codeSize*sizeof(instruction));
  	/* read the instructions */
	for(i=0; i < codeSize; i++)	{
		//printf("codeSize[%d] ", codeSize);
		vm_load_instr(&code[i],fp);
	}

	top = AVM_STACKSIZE -2 - glbnum;
	
	topsp = top;
	//printf("topsp[%d]\n",topsp);
	return ;
}