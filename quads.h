#ifndef QUADS_H_
#define QUADS_H_

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "symbolTable.h"

#define EXPAND_SIZE 1024
#define CURR_SIZE (total*sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE*sizeof(quad)+CURR_SIZE)


typedef enum iopcode {
	assign, add, sub, 
	mul, divi, mod, 
	uminus, and, or, 
	not, if_eq, if_noteq, 
	if_lesseq, if_greatereq, if_less,
	if_greater, call, param,
	ret, getretal, funcstart, 
	funcend, tablecreate, 
	tablegetelem, tablesetelem
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

	nil_e
} expr_t;

typedef struct expr {
	expr_t type;
	SymbolTableEntry* sym;
	struct expr* index;
	double numConst;
	double strConst;
	unsigned char boolConst;
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

#endif