#ifndef FINAL_CODE_H_
#define FINAL_CODE_H_
#include "quads.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define EXPAND_SIZE_INSTRUCTION		1024
#define CURR_SIZE_INSTRUCTION		(totalinstr * sizeof(instruction))
#define NEW_SIZE_INSTRUCTION		(EXPAND_SIZE_INSTRUCTION * sizeof(instruction)+currinstr)


typedef enum vmarg_T
{
	label_a		, //0
	global_a	, //1
	formal_a	, //2
	local_a		, //3
	integer_a	, //4
	double_a	, //5
	string_a	, //6
	bool_a		, //7
	nil_a		, //8
	userfunc_a	, //9
	libfunc_a	, //10
	retval_a	, //11
} vmarg_t;

typedef enum VMopcode
{
	assign_v, //0
	add_v, //1
	sub_v, //2
	mul_v, //3
	div_v, //4
	mod_v, //5
	uminus_v, //6
	and_v, //7
	or_v, //8
	not_v, //9
	jeq_v, //10
	jne_v, //11
	jgt_v, //12
	jlt_v, //13
	jge_v, //14
	jle_v, //15
	jump_v, //16
	call_v, //17
	funcenter_v, //18
	funcexit_v, //19
	newtable_v, //20
	tablegetelem_v, //21
	tablesetelem_v, //22
	pusharg_v,/*einai i param*/ //23
	nop_v, //24
} vmopcode;

typedef struct vMarg
{
	vmarg_t type;
	int val;
} vmarg;

typedef struct Instruction
{
	vmopcode	opcode;
	vmarg*		result;
	vmarg*		arg1;
	vmarg*		arg2;
	int	srcLine;
} instruction;

typedef struct Userfunc
{
	int address;
	int localSize;
	char* id;
} userfunc;

typedef struct Incomplete_Jump
{
	int instrNo; /* The jump instruction number. */
	int iaddress; /* The i-code jump-target address */
	struct Incomplete_Jump* next; /* A trivial linked list */
} incomplete_jump;

typedef struct return_list
{
	int label; /* to label pou einai i entoli */
	struct return_list *next;
} returnlist;

typedef struct functionlist
{
	SymbolTableEntry *sym;
	struct functionlist* next;
	returnlist* rl_head;
} func;


void make_generate( );
void print_instructions_txt( );

void generate(vmopcode op, quad* q);
void generate_relational(vmopcode op, quad* q);

void generate_ADD(quad* q);
void generate_SUB(quad* q);
void generate_MUL(quad* q);
void generate_DIV(quad* q);
void generate_MOD(quad* q);
void generate_UMINUS(quad* q);
void generate_AND(quad* q);
void generate_NEWTABLE(quad* q); /* TABLECREATE */
void generate_TABLEGETELEM(quad* q);
void generate_TABLESETELEM(quad* q);
void generate_ASSING(quad* q);
void generate_NOP(quad* q);
void generate_JUMP(quad* q);
void generate_IF_EQ(quad* q);
void generate_IF_NOTEQ(quad* q);
void generate_IF_GREATER(quad* q);
void generate_IF_GREATEREQ(quad* q);
void generate_IF_LESS(quad* q);
void generate_IF_LESSEQ(quad* q);
void generate_NOT(quad* q);
void generate_OR(quad* q);
void generate_PARAM(quad* q);
void generate_CALL(quad* q);
void generate_GETRETVAL(quad* q);
void generate_FUNCSTART(quad* q);
void generate_RETURN(quad* q);
void generate_FUNCEND(quad* q);

typedef void (*generator_func_t)(quad*);

vmarg* new_vmarg();

vmarg* make_operand(expr* e);

vmarg* make_booloperand(vmarg* arg, unsigned int tf);

vmarg* make_retvaloperand(vmarg* arg);

void append_list(func* fsym, unsigned int label);


func* pop_func();
func* top_func();
void push_func(SymbolTableEntry*  );

unsigned int nextinstructionlabel();
unsigned int currprocessedquad();
#endif