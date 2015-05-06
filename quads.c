#include "quads.h"

quad* quads = NULL;
int total = 0;
int currQuad = 0;
int  tmpNum = 0;


int programVarOffset = 0;
int functionLocalOffset = 0;
int formalArgOffset = 0;
int scopeSpaceCounter = 0;


void expand () {
	assert (total == currQuad);
	quad* p = (quad*) malloc (NEW_SIZE);
	if (quads) {
		memcpy (p, quads, CURR_SIZE);
		free (quads);
	}
	quads = p;
	total += EXPAND_SIZE;
}

void emit (iopcode op, expr* arg1, expr* arg2, expr* result, unsigned label, unsigned line) {
	if (currQuad == total) 
		expand ();

	quad* p = quads + currQuad++;
	p->op = op;
	p->arg1 = arg1;
	p->arg2 = arg2;
	p->result = result;
	p->label = label;
	p->line = line;
}

scopespace_t currscopespace () {
	if (scopeSpaceCounter == 1)
		return programvar;
	else if (scopeSpaceCounter % 2 == 0)
		return formalarg;
	else
		return functionlocal;
}

int currscopeoffset () {
	switch (currscopespace()) {
		case programvar: return programVarOffset;
		case functionlocal: return functionLocalOffset;
		case formalarg: return formalArgOffset;
		default: assert (0);
	}
}

void inccurrscopeoffset () {
	switch (currscopespace()) {
		case programvar: 
			++programVarOffset;
			break;
		case functionlocal:
			++functionLocalOffset;
			break;
		case formalarg:
			++formalArgOffset;
			break;
		default:
			assert(0);
	}
}

void enterscopespace () {
	++scopeSpaceCounter;
}

void exitscopespace () {
	assert (scopeSpaceCounter>0);
	--scopeSpaceCounter;
}

void resetformalargsoffset () {
	formalArgOffset = 0;
}

void resetfunctionlocaloffset () {
	functionLocalOffset = 0;
}

void restorecurrscopeoffset (int n) {
	switch (currscopespace()){
		case programvar: 
			programVarOffset = n;
			break;
		case functionlocal: 
			functionLocalOffset = n;
			break;
		case formalarg: 
			formalArgOffset = n;
			break;
		default: assert (0);
	}
}

void patchlabel (int quadNo, int label) {
	assert (quadNo < currQuad);
	(&quads[quadNo])->label = label;
}

expr* lvalue_expr (SymbolTableEntry* sym) {
	assert (sym);
	expr* e = (expr*) malloc(sizeof(expr));
	memset (e, 0, sizeof(expr));

	e->next = NULL;
	e->sym = sym;

	switch (sym->type) {
		case E_GLOBAL:
		case E_LOCAL:
		case E_FORMAL:
			e->type = var_e;
			break;
		case E_USERFUNC:
			e->type = programfunc_e;
			break;
		case E_LIBFUNC:
			e->type = libraryfunc_e;			
			break;
		default: 
			assert(0);
	}
	return e;
}

expr* newexpr (expr_t t) {
	expr* e = (expr*) malloc(sizeof(expr));
	memset (e, 0, sizeof(expr));
	e->type = t;
	return e;
}

expr* newexpr_conststring (char* s) {
	expr* e = newexpr (conststring_e);
	e->strConst = strdup(s);
	return e;
}

expr* newexpr_constnum (char* s) {
	expr* e = newexpr (constnum_e);
	e->numConst = atof(s);
	return e;
}

expr* newexpr_constbool (int s) {
	expr* e = newexpr (constbool_e);
	e->boolConst = s;
	return e;
}

expr* newexpr_constnil () {
	expr* e = newexpr (nil_e);
	return e;
}

expr* newexpr_constlabel (int l) {
	expr* e = newexpr (constlabel_e);
	e->labelConst = l;
	return e;
}

expr* emit_iftableitem (expr* e) {
	if (e->type != tableitem_e)
		return e;
	else {
		expr* result = newexpr (var_e);
		result->sym = newtemp();
		emit (tablegetelem, e, e->index, result, 0, yylineno);
		return result;
	}
}

expr* member_item (expr* lvalue, char* name) {
	lvalue = emit_iftableitem(lvalue);
	expr* item = newexpr (tableitem_e);
	item->sym = lvalue->sym;
	item->index = newexpr_conststring(name);
}

SymbolTableEntry* newtemp () {
	char* str = malloc(sizeof(char)*(3+findn(tmpNum)));

	sprintf(str, "_t%d\0", tmpNum++);
	SymbolTableEntry* sym = lookUp (getScope(), str);
	if (sym) {
		if (!sym->isActive) {
			sym->isActive = 1;
		}
		return sym;
	}
	tmpNum--;
	return (insert(getScope(), str, yylineno, getScope() == 0 ? E_GLOBAL : E_LOCAL));
}

int nextquad () {
	return currQuad;
}

char* opstrings[] = {
	"assign", "add", "sub", 
	"mul", "div", "mod", 
	"uminus", "and", "or", 
	"not", "if_eq", "if_noteq", 
	"if_lesseq", "if_greatereq", "if_less",
	"if_greater", "call", "param",
	"ret", "getretal", "funcstart", 
	"funcend", "tablecreate", 
	"tablegetelem", "tablesetelem", "jump"
};

void printOperation(iopcode op) {
	fprintf(stdout, "%s\t", opstrings[op]);
}

void printArguments (expr* arg) {
	if(arg == NULL)
		return ;
	switch(arg->type){
		case var_e:
		case arithexpr_e:
		case booleanexpr_e:
		case assignexpr_e:
		case newtable_e:
		case tableitem_e:
			fprintf(stdout, "%s#\t", arg->sym->value.varVal.name);
			break;
			//fprintf(stderr, "%s\n", );
		case programfunc_e:
		case libraryfunc_e:
			fprintf(stdout, "%s*\t", arg->sym->value.funcVal.name);
			break;
		case constnum_e:
			fprintf(stdout, "%lf\t", arg->numConst);
			break;
		case constbool_e:
			fprintf(stdout, "%s\t", arg->boolConst == 0 ? "false" : "true");
			break;
		case conststring_e:
			fprintf(stdout, "%s\t", arg->strConst);
			break;
		case constlabel_e:
			fprintf(stdout, "%d\t", arg->labelConst);
			break;
		case nil_e:
			fprintf(stdout, "%s\t", "nil");
			break;
		default: 
			assert(0);
			break;
	}
}
void printTheQuadsMyLove(){
	int i;
	for (i=0; i < currQuad; i++) {
		fprintf(stdout, "%d: ", i);
		printOperation((&quads[i])->op);
		fprintf(stdout, "r:");
		printArguments ((&quads[i])->result);
		fprintf(stdout, "a1:");
		printArguments ((&quads[i])->arg1);
		fprintf(stdout, "a2:");
		printArguments ((&quads[i])->arg2);
		putchar('\n');
	}
}

