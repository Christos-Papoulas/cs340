#include "quads.h"

quad* quads = NULL;
int total = 0;
int currQuad = 0;
int  tmpNum = 0;
FILE* quads_fp = NULL;

int programVarOffset = 0;
int functionLocalOffset = 0;
int formalArgOffset = 0;
int scopeSpaceCounter = 0;

int loopcounter = 0;

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
	int l = currQuad;
	quad* p = quads + currQuad++;
	p->op = op;
	p->arg1 = arg1;
	p->arg2 = arg2;
	p->result = result;
	p->label = l;
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
	if(!(&quads[quadNo])->result)
		(&quads[quadNo])->result = newexpr_constlabel(label);
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

expr* newexpr_constnum_i (int i) {
	expr* e = newexpr (constnum_e);
	e->numConst = i;
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
expr* emit_arithm(iopcode code, expr* arg1, expr* arg2) {
	expr* new = newexpr(arithexpr_e);
	new->sym = newtemp();
	emit(code, arg1, arg2, new, 0, yylineno); 
	return new;
}

expr* emit_relop(iopcode code, expr* arg1, expr* arg2) {
	assert(arg1 !=NULL && arg2 !=NULL);
	expr* new = newexpr(booleanexpr_e);
	new->truelist = makelist(nextquad());
	new->falselist = makelist(nextquad() + 1);
	emit(code, arg1, arg2, 0, 0 ,yylineno);
	emit(jump, 0, 0, 0, 0, yylineno);
	return new;
}

list* makelist(int l) {
	list* n = malloc(sizeof(list));
	n->label = l;
	return n;
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
	return insert(getScope(), str, yylineno, getScope() == 0 ? E_GLOBAL : E_LOCAL);
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
	"ret", "getretval", "funcstart", 
	"funcend", "tablecreate", 
	"tablegetelem", "tablesetelem", "jump"
};

void printOperation(iopcode op) {
	fprintf(quads_fp, "%s\t", opstrings[op]);
}


expr* make_call(expr* lvalue, func_t* elist) {
	expr* func = emit_iftableitem(lvalue),
		  *result;
	func_t* tmp;
	int count = 0, i;
	for(tmp = elist; tmp; tmp = tmp->next, count++)
		;
	func_t** reversed_elist = malloc(sizeof(func_t)*count);

	for(tmp = elist, i = 0; tmp; tmp = tmp->next, i++)
		reversed_elist[i] = tmp;

	for(i = count -1 ; i >= 0; i--) 
		emit(param, NULL, NULL, reversed_elist[i]->expr, 0, yylineno);
	
	emit(call, NULL, NULL, func, 0, yylineno);
	result = newexpr(var_e);
	result->sym = newtemp();
	emit(getretval, NULL, NULL, result, 0, yylineno);
	return result;
}

func_t* add_front(func_t* f, expr* e) {
	func_t* new = malloc(sizeof(func_t));
	new->expr = e;
	new->next = f;
	return new;
}

void checkuminus(expr* e) {
	if(e->type == constnum_e|| e->type == conststring_e||
		e->type == nil_e|| e->type == newtable_e||
		e->type == programfunc_e|| e->type == libraryfunc_e||
		e->type == booleanexpr_e) {
		fprintf(stderr, "Error at line: %d: Illegal expr to unary -", yylineno );
	}

}

list* newlist(int l) {
	list* new = malloc(sizeof(list));
	assert(new);

	new->label = l;
	new->next = NULL;

	return new;
}

list* merge(list* a, list* b) {
	list*  tmp = NULL;
	if(!a) {
		return b;
	}
	if(!b){
		return a;
	}
	for(tmp = a; tmp->next; tmp = tmp->next)
		;
	tmp->next = b;
	return a;
}

void backpatch(list* bl, int label) {
	list* t;
	for(t = bl; t; t = t->next)
		(&quads[t->label])->result = newexpr_constlabel(label);
}

expr * patch(expr* e){
	expr * new = NULL;
	backpatch(e->falselist, nextquad());
	backpatch(e->truelist, nextquad() + 2);
	if(e->type == booleanexpr_e){
		new = newexpr(var_e);
		new->sym = newtemp();
		emit(assign, newexpr_constbool(0), 0, new, 0, yylineno);
		emit(jump, 0, 0, newexpr_constlabel(nextquad() + 2), 0, yylineno);
		emit(assign, newexpr_constbool(1), 0, new, 0, yylineno);
	}
	return new;
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
			fprintf(quads_fp, "%s#\t", arg->sym->value.varVal.name);
			break;
		case programfunc_e:
		case libraryfunc_e:
			fprintf(quads_fp, "%s*\t", arg->sym->value.funcVal.name);
			break;
		case constnum_e:
			fprintf(quads_fp, "%lf\t", arg->numConst);
			break;
		case constbool_e:
			fprintf(quads_fp, "%s\t", arg->boolConst == 0 ? "false" : "true");
			break;
		case conststring_e:
			fprintf(quads_fp, "%s\t", arg->strConst);
			break;
		case constlabel_e:
			fprintf(quads_fp, "%d\t", arg->labelConst);
			break;
		case nil_e:
			fprintf(quads_fp, "%s\t", "nil");
			break;
		default: 
			assert(0);
			break;
	}
}
void printTheQuads(){
	int i;
	putchar('\n');
	quads_fp = fopen("quads.txt", "w");
	for (i=0; i < currQuad; i++) {
		fprintf(quads_fp, "%d: ", i);
		printOperation((&quads[i])->op);
		fprintf(quads_fp, "r:");
		printArguments ((&quads[i])->result);
		fprintf(quads_fp, "a1:");
		printArguments ((&quads[i])->arg1);
		fprintf(quads_fp, "a2:");
		printArguments ((&quads[i])->arg2);
		fprintf(quads_fp, "\n");
	}
	fclose(quads_fp);
}

