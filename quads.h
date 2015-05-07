#ifndef QUADS_H_
#define QUADS_H_

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "symbolTable.h"

#define EXPAND_SIZE 1024
#define CURR_SIZE (total*sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE*sizeof(quad)+CURR_SIZE)

extern int yylineno;

typedef enum iopcode {
	assign = 0, add, sub, 
	mul, divi, mod, 
	uminus, and, or, 
	not, if_eq, if_noteq, 
	if_lesseq, if_greatereq, if_less,
	if_greater, call, param,
	ret, getretal, funcstart, 
	funcend, tablecreate, 
	tablegetelem, tablesetelem, jump
} iopcode;

typedef enum expr_t {
	var_e,
	tableitem_e,

	programfunc_e,
	libraryfunc_e, 

	arithexpr_e, 
	booleanexpr_e,
	assignexpr_e,
	newtable_e,

	constnum_e,
	constbool_e,
	conststring_e,

	constlabel_e,

	nil_e
} expr_t;

typedef struct expr {
	expr_t type;
	SymbolTableEntry* sym;
	struct expr* index;
	double numConst;
	char* strConst;
	int boolConst;
	int labelConst;
	int iaddress;
	struct expr* next;
} expr;

typedef struct quad {
	iopcode op;
	expr* result;
	expr* arg1;
	expr* arg2;
	unsigned label;
	unsigned line;
} quad;

typedef enum scopespace_t {
	programvar,
	functionlocal,
	formalarg
} scopespace_t;

typedef enum symbol_t {
	var_s,
	programfunc_s,
	libraryfunc_s
} symbol_t;

typedef struct symbol {
	symbol_t type;
	char* name;
	scopespace_t space;
	unsigned offset;
	unsigned scope;
	unsigned line;
} symbol;

expr* lvalue_expr (SymbolTableEntry* sym);
expr* newexpr (expr_t t);
expr* newexpr_conststring (char* s);
expr* newexpr_constnum (char* s);
expr* newexpr_constbool (int s);
expr* newexpr_constnil ();
expr* newexpr_constlabel (int l);

expr* emit_iftableitem (expr* e);
expr* member_item (expr* lvalue, char* name);

scopespace_t currscopespace ();
int currscopeoffset ();
void inccurrscopeoffset ();
void enterscopespace ();
void exitscopespace ();
void resetformalargsoffset ();
void resetfunctionlocaloffset ();
void restorecurrscopeoffset (int n);
void patchlabel (int quadNo, int label);


void emit (iopcode op, expr* arg1, expr* arg2, expr* result, unsigned label, unsigned line);
int nextquad ();

SymbolTableEntry* newtemp();

void printTheQuadsMyLove();

#endif