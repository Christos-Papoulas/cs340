%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "symbolTable.h"
	#include <assert.h>
	#include "quads.h"

	int yyerror (char* yaccProvidedMessage);
	int alpha_yylex ();
	int inFunction = 0;

	extern int yylineno;
	extern char* yytext;
	extern FILE* yyin;
	extern FILE* out;

	extern struct node* top; // for functions!
%}

%union {
	char*			stringValue;
	int				intValue;
	double		realValue;
	struct expr* exprValue;
}

%start program

%token <stringValue> ID
%token <stringValue> INTCONST
%token <stringValue> REALCONST
%token <stringValue> STRING 

%token <stringValue> IF 
%token <stringValue> ELSE 
%token <stringValue> WHILE
%token <stringValue> FOR
%token <stringValue> FUNCTION
%token <stringValue> RETURN 
%token <stringValue> BREAK 
%token <stringValue> CONTINUE 
%token <stringValue> AND 
%token <stringValue> NOT 
%token <stringValue> OR 
%token <stringValue> LOCAL
%token <stringValue> TRUE 
%token <stringValue> FALSE 
%token <stringValue> NIL
%expect 1
%token <stringValue> ASSIGN 
%token <stringValue> PLUS
%token <stringValue> MINUS
%token <stringValue> MULTIPLIES 
%token <stringValue> DIVIDES
%token <stringValue> MODULUS
%token <stringValue> EQUAL 
%token <stringValue> INEQUAL
%token <stringValue> INCREMENT 
%token <stringValue> DECREMENT
%token <stringValue> GREATER
%token <stringValue> LESS
%token <stringValue> GREATER_EQUAL
%token <stringValue> LESS_EQUAL

%token <stringValue> LEFT_BRACES
%token <stringValue> RIGHT_BRACES
%token <stringValue> LEFT_BRACKETS
%token <stringValue> RIGHT_BRACKETS
%token <stringValue> LEFT_PARENTHESIS
%token <stringValue> RIGHT_PARENTHESIS
%token <stringValue> SEMICOLON
%token <stringValue> COMMA
%token <stringValue> COLON
%token <stringValue> DOUBLE_COLON
%token <stringValue> DOT 
%token <stringValue> DOUBLE_DOT

%type <exprValue> lvalue
%type <exprValue> primary
%type <exprValue> assignexpr
%type <exprValue> expr
%type <exprValue> member
%type <exprValue> term
%type <exprValue> const
%type <exprValue> funcdef
%type <exprValue> funcprefix
%type <exprValue> funcname

%left ASSIGN
%left AND
%left OR
%nonassoc EQUAL INEQUAL
%nonassoc GREATER GREATER_EQUAL LESS LESS_EQUAL
%left PLUS MINUS
%left MULTIPLIES DIVIDES MODULUS
%right NOT INCREMENT DECREMENT
%left DOT DOUBLE_DOT 
%left LEFT_BRACKETS RIGHT_BRACKETS
%left LEFT_PARENTHESIS RIGHT_PARENTHESIS


%%

program:	stmts stmt {fprintf(stderr, "program -> stmts stmt\n");}
			|/* empty */ {fprintf(stderr, "program -> empty\n");}
			;

stmts:		stmts stmt {fprintf(stderr, "stmts -> stmts stmt\n");}
			|/* empty */ {fprintf(stderr, "stmts -> empty\n");}
			;

stmt:		expr SEMICOLON {fprintf(stderr, "stmt -> expr ;\n");}
			|ifstmt {fprintf(stderr, "stmt -> ifstmt\n");}
			|whilestmt {fprintf(stderr, "stmt -> whilestmt\n");}
			|forstmt {fprintf(stderr, "stmt -> forstmt\n");}
			|returnstmt {fprintf(stderr, "stmt -> returnstmt\n");}
			|BREAK SEMICOLON {fprintf(stderr, "stmt -> break ;\n");}	
			|CONTINUE SEMICOLON {fprintf(stderr, "stmt -> continue ;\n");}
			|block {fprintf(stderr, "stmt -> block\n");}
			|funcdef {fprintf(stderr, "stmt -> funcdef\n");}
			|SEMICOLON {fprintf(stderr, "stmt -> ;\n");}
			;

expr:		assignexpr {
				$$ = $1;
				fprintf(stderr, "expr -> assignexpr\n");
			}
			|expr PLUS expr {
				$$ = newexpr(arithexpr_e);
				$$->sym = newtemp();
				emit(add, $1, $3, $$, 0, yylineno);
				fprintf(stderr, "expr -> expr + expr\n");
			}
			|expr MINUS expr {
				$$ = newexpr(arithexpr_e);
				$$->sym = newtemp();
				emit(sub, $1, $3, $$, 0, yylineno);
				fprintf(stderr, "expr -> expr - expr\n");
			}
			|expr MULTIPLIES expr {
				$$ = newexpr(arithexpr_e);
				$$->sym = newtemp();
				emit(mul, $1, $3, $$, 0, yylineno);
				fprintf(stderr, "expr -> expr * expr\n");
			}
			|expr DIVIDES expr {
				$$ = newexpr(arithexpr_e);
				$$->sym = newtemp();
				emit(divi, $1, $3, $$, 0, yylineno);
				fprintf(stderr, "expr -> expr / expr\n");
			}
			|expr MODULUS expr {
				$$ = newexpr(arithexpr_e);
				$$->sym = newtemp();
				emit(mod, $1, $3, $$, 0, yylineno);
				fprintf(stderr, "expr -> expr mod expr\n");
			}
			|expr GREATER expr {
				assert($1!=NULL && $2!=NULL);
				$$ = newexpr(booleanexpr_e);
				$$->sym = newtemp();
				emit (if_greater, $1, $3, newexpr_constlabel(nextquad()+3), 0 ,yylineno);
				emit (assign, newexpr_constbool(0), NULL, $$, 0 , yylineno);
				emit (jump, NULL, NULL, newexpr_constlabel(nextquad()+2), 0, yylineno);
				emit (assign, newexpr_constbool(1), NULL, $$, 0, yylineno);
				fprintf(stderr, "expr -> expr > expr\n");
			}
			|expr GREATER_EQUAL expr {
				assert($1!=NULL && $2!=NULL);
				$$ = newexpr(booleanexpr_e);
				$$->sym = newtemp();
				emit (if_greatereq, $1, $3, newexpr_constlabel(nextquad()+3), 0 ,yylineno);
				emit (assign, newexpr_constbool(0), NULL, $$, 0 , yylineno);
				emit (jump, NULL, NULL, newexpr_constlabel(nextquad()+2), 0, yylineno);
				emit (assign, newexpr_constbool(1), NULL, $$, 0, yylineno);
				fprintf(stderr, "expr -> expr >= expr\n");
			}
			|expr LESS expr {
				assert($1!=NULL && $2!=NULL);
				$$ = newexpr(booleanexpr_e);
				$$->sym = newtemp();
				emit (if_less, $1, $3, newexpr_constlabel(nextquad()+3), 0 ,yylineno);
				emit (assign, newexpr_constbool(0), NULL, $$, 0 , yylineno);
				emit (jump, NULL, NULL, newexpr_constlabel(nextquad()+2), 0, yylineno);
				emit (assign, newexpr_constbool(1), NULL, $$, 0, yylineno);
				fprintf(stderr, "expr -> expr < expr\n");}
			|expr LESS_EQUAL expr {
				assert($1!=NULL && $2!=NULL);
				$$ = newexpr(booleanexpr_e);
				$$->sym = newtemp();
				emit (if_lesseq, $1, $3, newexpr_constlabel(nextquad()+3), 0 ,yylineno);
				emit (assign, newexpr_constbool(0), NULL, $$, 0 , yylineno);
				emit (jump, NULL, NULL, newexpr_constlabel(nextquad()+2), 0, yylineno);
				emit (assign, newexpr_constbool(1), NULL, $$, 0, yylineno);
				
				fprintf(stderr, "expr -> expr <= expr\n");
			}
			|expr EQUAL expr {
				assert($1!=NULL && $2!=NULL);
				$$ = newexpr(booleanexpr_e);
				$$->sym = newtemp();
				emit (if_eq, $1, $3, newexpr_constlabel(nextquad()+3), 0 ,yylineno);
				emit (assign, newexpr_constbool(0), NULL, $$, 0 , yylineno);
				emit (jump, NULL, NULL, newexpr_constlabel(nextquad()+2), 0, yylineno);
				emit (assign, newexpr_constbool(1), NULL, $$, 0, yylineno);
				
				fprintf(stderr, "expr -> expr == expr\n");
			}
			|expr INEQUAL expr {
				assert($1!=NULL && $2!=NULL);
				$$ = newexpr(booleanexpr_e);
				$$->sym = newtemp();
				emit (if_noteq, $1, $3, newexpr_constlabel(nextquad()+3), 0 ,yylineno);
				emit (assign, newexpr_constbool(0), NULL, $$, 0 , yylineno);
				emit (jump, NULL, NULL, newexpr_constlabel(nextquad()+2), 0, yylineno);
				emit (assign, newexpr_constbool(1), NULL, $$, 0, yylineno);
				
				fprintf(stderr, "expr -> expr != expr\n");}
			|expr AND expr {fprintf(stderr, "expr -> expr AND expr\n");}
			|expr OR expr {fprintf(stderr, "expr -> expr OR expr\n");}
			|term {
				$$ = $1;
				fprintf(stderr, "expr -> term\n");
			}
			;		
			
term: LEFT_PARENTHESIS expr RIGHT_PARENTHESIS {fprintf(stderr, "term -> (expr)\n");}
			|MINUS expr {fprintf(stderr, "term -> - expr\n");}
			|NOT expr {fprintf(stderr, "term -> (expr)\n");}
			|INCREMENT lvalue {fprintf(stderr, "term -> ++lvalue\n");}
			|lvalue INCREMENT {fprintf(stderr, "term -> lvalue++\n");}
			|DECREMENT lvalue {fprintf(stderr, "term -> --lvalue\n");}
			|lvalue DECREMENT {fprintf(stderr, "term -> lvalue--\n");}
			|primary {
				$$ = $1;
				fprintf(stderr, "term -> primary\n");
			}
			;

assignexpr: lvalue ASSIGN expr {
				int i;
				
				fprintf(stderr, "assignexpr -> lvalue = expr\n");
				
				if ($1 && $1->sym->type == E_USERFUNC) {
					if (isLibraryFunction($1->sym->value.funcVal.name)) {
						fprintf (stderr, "Error at line %d: cannot overwrite libfunc: %s\n", yylineno, $1->sym->value.funcVal.name);
						exit(-1);
					}
				}

				for (i=0; i <= getScope() && $1; i++) {
					SymbolTableEntry* tmp = lookUp(i,$1->sym->value.varVal.name);
					if ( tmp && tmp->type == E_USERFUNC) {
						fprintf (stderr, "Error at line %d: cannot redifine user function: %s\n", yylineno, $1);
						exit(-1);
					}
					
				}

				if ($1->type == tableitem_e) {
					emit (tablesetelem, $1, $1->index, $3, 0, yylineno);
					$$ = emit_iftableitem ($1);
					$$->type = assignexpr_e;
				} else {
					emit (assign, $3, NULL, $1, 0, yylineno);
					$$ = newexpr(assignexpr_e);
					$$->sym = newtemp();
					emit (assign, $1, NULL, $$, 0, yylineno);
				}


			}
			;

primary:	lvalue 
			{
				$$ = $1;
				fprintf(stderr, "primary -> lvalue\n");
				
			}
			|call {fprintf(stderr, "primary -> call\n");}
			|objectdef {fprintf(stderr, "primary -> objectdef\n");}
			|LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS {fprintf(stderr, "primary -> (funcdef)\n");}
			|const 
			{
				fprintf(stderr, "primary -> const\n");
				$$ = $1;
			}
			;

lvalue:		ID 
			{
				SymbolTableEntry* tmp = lookUp(getScope(),yylval.stringValue);
				
				SymbolTableEntry* newvar = NULL;

				int i;
				int toBeInserted = 1;
				int localvar = 0;

				if (top_e() != -1) {
					SymbolTableEntry* lvar = lookUp(getScope(), yylval.stringValue);
					if (lvar && lvar->isActive) {
						localvar = 1;
					}
					for (i=1; i<top_e(); i++){ 
						SymbolTableEntry* tmp = lookUp(i, yylval.stringValue);
						if (tmp && !localvar) {
							fprintf(stderr, "Error at line %d: cannot access var: %s\n", yylineno, yylval.stringValue);
							exit (-1);
						}
					}
				}

				for (i=0; i<=getScope(); i++) {
					SymbolTableEntry* tmp1 = lookUp(i, yylval.stringValue);
					if (tmp1 && tmp1->isActive && (tmp1->type==E_USERFUNC)) {
						toBeInserted = 0;
					}
				}
				// $$ = strdup(yylval.stringValue);
				if (!isLibraryFunction(yylval.stringValue) && toBeInserted) {
					if (!tmp) {
						newvar = insert(getScope(), yylval.stringValue, yylineno, getScope() == 0 ? E_GLOBAL : E_LOCAL);
					} else if (!tmp->isActive) {
						newvar = insert(getScope(), yylval.stringValue, yylineno, getScope() == 0 ? E_GLOBAL : E_LOCAL);
					}
				}

				if (newvar) {
					$$ = lvalue_expr(newvar);
				} else 
					$$ = lvalue_expr(tmp);

				fprintf(stderr, "lvalue -> ID %s \n", yylval.stringValue);
			}
			|LOCAL ID 
			{
				SymbolTableEntry* tmp = lookUp(getScope(), yylval.stringValue);
				SymbolTableEntry* newvar = NULL;

				if (isLibraryFunction(yylval.stringValue) && getScope() != 0) {
					fprintf (stderr, "Error at line %d: try to shadow libfunc: %s\n", yylineno, yylval.stringValue);
					exit(-1);
				}
				if (!tmp) {
					newvar = insert(getScope(), yylval.stringValue, yylineno, getScope() == 0 ? E_GLOBAL : E_LOCAL);
				}else if (tmp->type == E_LIBFUNC && getScope() != 0) {
					fprintf (stderr, "Error at line %d: cannot redifine library function %s \n", yylineno, yylval.stringValue);
					exit(-1);
				}

				if (newvar) {
					$$ = lvalue_expr(newvar);
				} else 
					$$ = lvalue_expr(tmp);

				fprintf(stderr, "lvalue -> LOCAL ID\n");
			}
			|DOUBLE_COLON ID 
			{
				SymbolTableEntry* tmp = lookUp(0,yylval.stringValue);
				if (!tmp) {
					fprintf (stderr, "Error at line %d: undefined reference to global variable %s \n", yylineno, yylval.stringValue);
					exit(-1);
				}
				fprintf(stderr, "lvalue -> ::ID\n");
				$$ = lvalue_expr(tmp);
			}
			|member {
				fprintf(stderr, "lvalue -> member\n");
				$$ = $1;
			}
			;

member:		lvalue DOT ID {

				$$ = member_item ($1, $3);

				fprintf(stderr, "member -> lvalue.id\n");
			}
			|lvalue LEFT_BRACKETS expr RIGHT_BRACKETS 
			{
				expr* member = newexpr(tableitem_e);
				$1->type = tableitem_e;
				member->sym = emit_iftableitem($1)->sym;
				member->index = $3;
				$$ = member;
				fprintf(stderr, "member -> lvalue [expr]\n");
			}
			|call DOT ID {fprintf(stderr, "member -> call.id\n");}
			|call LEFT_BRACKETS expr RIGHT_BRACKETS {fprintf(stderr, "member -> call [expr]\n");}
			;

call:		call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS {fprintf(stderr, "call -> call (elist)\n");}
			|lvalue callsuffix {fprintf(stderr, "call -> lvalue callsuffix\n");}
			|LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS {fprintf(stderr, "call -> (functdef) (elist)\n");}
			;

callsuffix:	normcall {fprintf(stderr, "callsuffix -> normcall\n");}
			|methodcall {fprintf(stderr, "callsuffix -> methodcall\n");}
			;

normcall:	LEFT_PARENTHESIS elist RIGHT_PARENTHESIS {fprintf(stderr, "normcall -> (elist)\n");}
			;

methodcall: DOUBLE_DOT ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS {fprintf(stderr, "methodcall -> ..id (elist)\n");} 
			;

elist:		expr elists {fprintf(stderr, "elist -> expr elists\n");}
			|/*empt*/
			;

elists:		COMMA expr elists {fprintf(stderr, "elists -> ,expr elists\n");}
			|/*empty*/ {fprintf(stderr, "elists -> empty\n");}
			;

objectdef:	LEFT_BRACKETS elist RIGHT_BRACKETS {fprintf(stderr, "objectdef -> 	[elist]\n");}
			|LEFT_BRACKETS indexed RIGHT_BRACKETS {fprintf(stderr, "objectdef -> [indexed]\n");}
			;

indexed:	indexedelem indexeds {fprintf(stderr, "indexed -> indexedelem\n");}
			;

indexeds: 	COMMA indexed {fprintf(stderr, "indexeds -> ,indexed\n");}
			|/*empty*/ {fprintf(stderr, "indexeds -> empty\n");}
			;

indexedelem:LEFT_BRACES expr COLON expr RIGHT_BRACES {fprintf(stderr, "indexdelem -> {expr : expr}\n");}
			;

block:		LEFT_BRACES
			{
				scopeUp();
			} 
			stmts RIGHT_BRACES
			{
				deactivateScope (getScope());
				scopeDown();
				fprintf(stderr, "block -> [stmts] \n");
			}
			;

funcdef:	funcprefix funcargs funcbody
			{
				exitscopespace();
				//$1->totallocals = functionLocalOffset;
				//functionLocalOffset = pop (functionLocalsStack);
				$$ = $1;
				emit (funcend, NULL, NULL, ($1), 0, yylineno);
				fprintf(stderr, "funcdef -> funcprefix funcargs funcbody \n");
			}
			;

funcargs:	LEFT_PARENTHESIS {scopeUp();} idlist RIGHT_PARENTHESIS 
			{
				enterscopespace();
				resetfunctionlocaloffset();
				fprintf(stderr, "funcargs -> (idlist)\n");
			}
			;

funcbody:	funcblock
			{
				exitscopespace();
				fprintf(stderr, "funcbody -> funcblock\n");
			}
			;

funcprefix: 	FUNCTION funcname {
				$$ = $2;
				$$->iaddress = nextquad();
				emit(funcstart, NULL, NULL, $$, 0, yylineno);
				//push(functionLocalsStack, functionLocalOffset);
				enterscopespace();
				resetformalargsoffset();
				fprintf(stderr, "funcprefix -> FUNCTION funcname\n");
			}
			;

funcname:	ID 
			{
				SymbolTableEntry* tmp = lookUp(getScope(), yylval.stringValue);
				SymbolTableEntry* new = NULL;
				if (isLibraryFunction(yylval.stringValue)) {
					fprintf (stderr, "Error at line %d: cannot overwrite libfunc: %s\n", yylineno, yylval.stringValue);
					exit(-1);
				}
				if (!tmp) {
					new = insert(getScope(), yylval.stringValue, yylineno, E_USERFUNC);
				} else if (!tmp->isActive) {
					new = insert(getScope(), yylval.stringValue, yylineno, E_USERFUNC);
				} else {

					fprintf (stderr, "Error at line %d: cannot redifine var: %s\n", yylineno, yylval.stringValue);
					exit(-1);
				}
				assert (new);
				$$ = newexpr(programfunc_e);
				$$->sym = new;
				
				fprintf(stderr, "funcname -> ID \n");

			} 
			|/*empty*/
			{
				$$ = newexpr(programfunc_e);
				$$->sym = insert(getScope(), getAFunctionName(), yylineno, E_USERFUNC);

				fprintf(stderr, "funcname -> empty \n");

			}
			;


funcblock: 	LEFT_BRACES 
			{
				push(getScope());
			}
			stmts RIGHT_BRACES 
			{
				deactivateScope (getScope());
				scopeDown();
				pop();
				fprintf(stderr, "funcblock -> [stmts] \n");
			}
			;

const: 		INTCONST {
				$$ = newexpr_constnum(yytext);
				fprintf(stderr, "const -> intconst\n");
			}
			|STRING {
				$$ = newexpr_conststring(yytext);
				fprintf(stderr, "const -> string\n");
			}
			|NIL {
				$$ = newexpr_constnil ();
				fprintf(stderr, "const -> nil\n");
			}
			|TRUE {
				$$ = newexpr_constbool (1);
				fprintf(stderr, "const -> true\n");
			}
			|FALSE {
				$$ = newexpr_constbool (0);
				fprintf(stderr, "const -> false\n");
			}
			;

idlist:		ID 
			{
				SymbolTableEntry* t = insert(getScope(), yylval.stringValue, yylineno, E_FORMAL);
				if(isLibraryFunction(yylval.stringValue)){
					fprintf (stderr, "Error at line %d: formal shadows libfunc: %s\n", yylineno, yylval.stringValue);
					exit(-1);
				}
			} ids 
			{
				fprintf(stderr, "idlist -> ID ids\n"); 

			}
			|/*empty*/ {fprintf(stderr, "idlist -> empty\n");}
			;

ids:		COMMA ID 
			{
				SymbolTableEntry* tmp = lookUp(getScope(),yylval.stringValue);
				if(isLibraryFunction(yylval.stringValue)){
					fprintf (stderr, "Error at line %d: formal shadows libfunc: %s\n", yylineno, yylval.stringValue);
					exit(-1);
				}
				if(tmp && tmp->isActive){
					fprintf (stderr, "Error at line %d: formal redeclaration of var: %s\n", yylineno, yylval.stringValue);
					exit(-1);
				}
				SymbolTableEntry* t = insert(getScope(), yylval.stringValue, yylineno, E_FORMAL);
				assert(t);
			}
			ids
			{
				fprintf(stderr, "ids -> COMMA ID ids\n");
			}
			|/*empty*/ {fprintf(stderr, "ids -> empty\n");}
			;

ifstmt:		ifprefix stmt {fprintf(stderr, "ifstmt -> ifprefix stmt\n");}
			| ifprefix stmt ELSE stmt{fprintf(stderr, "ifstmt -> ifprefix stmt ELSE stmt\n");}
			;

ifprefix:	IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS{fprintf(stderr, "ifprefix -> IF (expr)\n");}
			;

whilestmt:	WHILE LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt {fprintf(stderr, "whilestmt -> WHILE (expr) stmt\n");}
			;

forstmt:	FOR LEFT_PARENTHESIS elist SEMICOLON expr SEMICOLON elist RIGHT_PARENTHESIS stmt {fprintf(stderr, "forstmt -> FOR (elist; expr; elist) stmt\n");}
			;

returnstmt: RETURN expr SEMICOLON{fprintf(stderr, "returnstmt -> return expr;\n");}
			|RETURN SEMICOLON{fprintf(stderr, "returnstmt -> return; \n");}
			;
%%

int yyerror (char* yaccProvidedMessage) {
	fprintf(stderr, "%s: at line %d, before token %s\n", yaccProvidedMessage, yylineno, yytext);
	fprintf(stderr, "INPUT NOT VALID\n");
	//exit(-1);
}

int main (int argc, char** argv) {
	out = fopen("lex.log", "w");
	if (argc > 1) {
		if (!(yyin = fopen(argv[1], "r"))) {
			fprintf(stderr, "Cannot read file: %s \n", argv[1]);
			return 1;
		}

	}else 
		yyin = stdin;
	init();
	yyparse();
	printSymbolTable();
	printTheQuadsMyLove();
	return 0;
}