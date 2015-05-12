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
	FILE* rules;

	extern struct node* top; // for functions!
%}

%union {
	char*				stringValue;
	int					intValue;
	double				realValue;
	struct expr*		exprValue;
	struct for_t_s* 	forValue;
	struct func_t_s*	funcValue;
	struct special_t_s*	specValue;
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
%type <exprValue> call

%type <funcValue> elist
%type <funcValue> elists
%type <funcValue> methodcall
%type <funcValue> normcall
%type <funcValue> callsuffix

%type <intValue> ifprefix
%type <intValue> elseprefix
%type <intValue> whilestart
%type <intValue> whilecond
%type <intValue> M
%type <intValue> N

%type <forValue> forprefix

%type <specValue> loopstmt
%type <specValue> stmt
%type <specValue> stmts
%type <specValue> breakstmt
%type <specValue> continuestmt
%type <specValue> loopstart
%type <specValue> whilestmt
%type <specValue> ifstmt 
%type <specValue> forstmt
%type <specValue> returnstmt
%type <specValue> block

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

program:	stmts {fprintf(rules, "program -> stmts\n");}
			;

stmts:		stmts stmt 
			{
				$$ = malloc(sizeof(special_t));
				special_t* skata = $$;
				list* skata1 = $1 ? $1->breaklist : NULL;
				list* skata2 = $2 ? $2->breaklist : NULL;
				$$->breaklist = merge(
					skata1,
					skata2
				);
				$$->contlist = merge(
					$1 ? $1->contlist : NULL,
					$2 ? $2->contlist : NULL
				);

				fprintf(rules, "stmts -> stmts stmt\n");
			}
			|/* empty */ 
			{
				$$ = NULL;
				fprintf(rules, "stmts -> empty\n");
			}
			;

stmt:		expr SEMICOLON {
				$$ = NULL;
								
				patch($1);


				fprintf(rules, "stmt -> expr ;\n");
			}
			|ifstmt 
			{
				$$ = $1;
				fprintf(rules, "stmt -> ifstmt\n");
			}
			|whilestmt 
			{
				$$ = $1;
				fprintf(rules, "stmt -> whilestmt\n");
			}
			|forstmt 
			{
				$$ = $1;
				fprintf(rules, "stmt -> forstmt\n");
			}
			|returnstmt 
			{
				$$ = $1;
				fprintf(rules, "stmt -> returnstmt\n");
			}
			|breakstmt 
			{
				$$ = $1;
				fprintf(rules, "stmt -> breakstmt ;\n");
			}	
			|continuestmt 
			{
				$$ = $1;
				fprintf(rules, "stmt -> continuestmt ;\n");
			}
			|block 
			{
				$$ = $1;
				fprintf(rules, "stmt -> block\n");
			}
			|funcdef 
			{
				//$$ = $1;
				fprintf(rules, "stmt -> funcdef\n");
			}
			|SEMICOLON 
			{
				$$ = NULL;
				fprintf(rules, "stmt -> ;\n");
			}
			;

breakstmt:	BREAK SEMICOLON
			{
				$$ = malloc(sizeof(special_t));
				$$->breaklist = newlist(nextquad());
				$$->contlist = NULL;
				emit(jump, 0, 0, 0, 0, yylineno);
				fprintf(rules, "breakstmt -> BREAK ;\n");
			}
			;

continuestmt: CONTINUE SEMICOLON 
			{
				$$ = malloc(sizeof(special_t));
				$$->contlist = newlist(nextquad());
				$$->breaklist = NULL;
				emit(jump, 0, 0, 0, 0, yylineno);
				fprintf(rules, "continuestmt -> continue ;\n");
			}
			;

expr:		assignexpr {
				$$ = $1;
				fprintf(rules, "expr -> assignexpr\n");
			}
			|expr PLUS expr {
				$$ = newexpr(arithexpr_e);
				$$->sym = newtemp();
				emit(add, $1, $3, $$, 0, yylineno);

				fprintf(rules, "expr -> expr + expr\n");
			}
			|expr MINUS expr {
				$$ = newexpr(arithexpr_e);
				$$->sym = newtemp();
				emit(sub, $1, $3, $$, 0, yylineno);
				fprintf(rules, "expr -> expr - expr\n");
			}
			|expr MULTIPLIES expr {
				$$ = newexpr(arithexpr_e);
				$$->sym = newtemp();
				emit(mul, $1, $3, $$, 0, yylineno);
				fprintf(rules, "expr -> expr * expr\n");
			}
			|expr DIVIDES expr {
				$$ = newexpr(arithexpr_e);
				$$->sym = newtemp();
				emit(divi, $1, $3, $$, 0, yylineno);
				fprintf(rules, "expr -> expr / expr\n");
			}
			|expr MODULUS expr {
				$$ = newexpr(arithexpr_e);
				$$->sym = newtemp();
				emit(mod, $1, $3, $$, 0, yylineno);
				fprintf(rules, "expr -> expr mod expr\n");
			}
			|expr GREATER expr {
				assert($1!=NULL && $3!=NULL);
				$$ = newexpr(booleanexpr_e);
				$$->truelist = makelist(nextquad());
				$$->falselist = makelist(nextquad() + 1);
				emit(if_greater, $1, $3, 0, 0 ,yylineno);
				emit(jump, 0, 0, 0, 0, yylineno);

				/*$$ = newexpr(booleanexpr_e);
				$$->sym = newtemp();
				emit (if_greater, $1, $3, newexpr_constlabel(nextquad()+3), 0 ,yylineno);
				emit (assign, newexpr_constbool(0), NULL, $$, 0 , yylineno);
				emit (jump, NULL, NULL, newexpr_constlabel(nextquad()+2), 0, yylineno);
				emit (assign, newexpr_constbool(1), NULL, $$, 0, yylineno);*/
				fprintf(rules, "expr -> expr > expr\n");
			}
			|expr GREATER_EQUAL expr {
				assert($1!=NULL && $3!=NULL);

				$$ = newexpr(booleanexpr_e);
				$$->truelist = makelist(nextquad());
				$$->falselist = makelist(nextquad() + 1);
				emit(if_greatereq, $1, $3, 0, 0 ,yylineno);
				emit(jump, 0, 0, 0, 0, yylineno);
				/*
				$$ = newexpr(booleanexpr_e);
				$$->sym = newtemp();
				emit (if_greatereq, $1, $3, newexpr_constlabel(nextquad()+3), 0 ,yylineno);
				emit (assign, newexpr_constbool(0), NULL, $$, 0 , yylineno);
				emit (jump, NULL, NULL, newexpr_constlabel(nextquad()+2), 0, yylineno);
				emit (assign, newexpr_constbool(1), NULL, $$, 0, yylineno);*/
				fprintf(rules, "expr -> expr >= expr\n");
			}
			|expr LESS expr {
				assert($1!=NULL && $3!=NULL);
				$$ = newexpr(booleanexpr_e);
				$$->truelist = makelist(nextquad());
				$$->falselist = makelist(nextquad() + 1);
				emit(if_less, $1, $3, 0, 0 ,yylineno);
				emit(jump, 0, 0, 0, 0, yylineno);
				/*$$ = newexpr(booleanexpr_e);
				$$->sym = newtemp();
				emit (if_less, $1, $3, newexpr_constlabel(nextquad()+3), 0 ,yylineno);
				emit (assign, newexpr_constbool(0), NULL, $$, 0 , yylineno);
				emit (jump, NULL, NULL, newexpr_constlabel(nextquad()+2), 0, yylineno);
				emit (assign, newexpr_constbool(1), NULL, $$, 0, yylineno);*/
				fprintf(rules, "expr -> expr < expr\n");}
			|expr LESS_EQUAL expr {
				assert($1!=NULL && $3!=NULL);
				$$ = newexpr(booleanexpr_e);
				$$->truelist = makelist(nextquad());
				$$->falselist = makelist(nextquad() + 1);
				emit(if_lesseq, $1, $3, 0, 0 ,yylineno);
				emit(jump, 0, 0, 0, 0, yylineno);

				/*$$ = newexpr(booleanexpr_e);
				$$->sym = newtemp();
				emit (if_lesseq, $1, $3, newexpr_constlabel(nextquad()+3), 0 ,yylineno);
				emit (assign, newexpr_constbool(0), NULL, $$, 0 , yylineno);
				emit (jump, NULL, NULL, newexpr_constlabel(nextquad()+2), 0, yylineno);
				emit (assign, newexpr_constbool(1), NULL, $$, 0, yylineno);*/
				
				fprintf(rules, "expr -> expr <= expr\n");
			}
			|expr EQUAL expr {
				assert($1!=NULL && $3!=NULL);

				$$ = newexpr(booleanexpr_e);
				$$->truelist = makelist(nextquad());
				$$->falselist = makelist(nextquad() + 1);
				emit(if_eq, $1, $3, 0, 0 ,yylineno);
				emit(jump, 0, 0, 0, 0, yylineno);

				/*$$ = newexpr(booleanexpr_e);
				$$->sym = newtemp();
				emit (if_eq, $1, $3, newexpr_constlabel(nextquad()+3), 0 ,yylineno);
				emit (assign, newexpr_constbool(0), NULL, $$, 0 , yylineno);
				emit (jump, NULL, NULL, newexpr_constlabel(nextquad()+2), 0, yylineno);
				emit (assign, newexpr_constbool(1), NULL, $$, 0, yylineno);*/
				
				fprintf(rules, "expr -> expr == expr\n");
			}
			|expr INEQUAL expr {
				assert($1!=NULL && $3!=NULL);

				$$ = newexpr(booleanexpr_e);
				$$->truelist = makelist(nextquad());
				$$->falselist = makelist(nextquad() + 1);
				emit(if_eq, $1, $3, 0, 0 ,yylineno);
				emit(jump, 0, 0, 0, 0, yylineno);

				/*$$ = newexpr(booleanexpr_e);
				$$->sym = newtemp();
				emit (if_noteq, $1, $3, newexpr_constlabel(nextquad()+3), 0 ,yylineno);
				emit (assign, newexpr_constbool(0), NULL, $$, 0 , yylineno);
				emit (jump, NULL, NULL, newexpr_constlabel(nextquad()+2), 0, yylineno);
				emit (assign, newexpr_constbool(1), NULL, $$, 0, yylineno);*/
				
				fprintf(rules, "expr -> expr != expr\n");}
			|expr AND M expr 
			{
				backpatch($1->truelist, $3);
				//backpatch($4->truelist, nextquad());
				$$->truelist = $4->truelist;
				$$->falselist = merge($1->falselist, $4->falselist);
				/*$$ = newexpr(booleanexpr_e);
				$$->sym = newtemp();
				emit(and, $1, $3, $$, 0, yylineno);*/
				
				fprintf(rules, "expr -> expr AND expr\n");
			}
			|expr OR M expr 
			{
				backpatch($1->falselist, $3);
				$$->truelist = merge($1->truelist, $4->truelist);
				$$->falselist = $4->falselist;
				/*$$ = newexpr(booleanexpr_e);
				$$->sym = newtemp();
				emit(or, $1, $3, $$, 0, yylineno);*/
				fprintf(rules, "expr -> expr OR expr\n");
			}
			|term {
				$$ = $1;
				fprintf(rules, "expr -> term\n");
			}
			;		
			
term: 		LEFT_PARENTHESIS expr RIGHT_PARENTHESIS 
			{
				$$ = $2;
				expr* t;
				if(t = patch($2))
					$$ = t;

				fprintf(rules, "term -> (expr)\n");
			}
			|MINUS expr 
			{
				checkuminus($2);
				$$ = newexpr(arithexpr_e);
				$$->sym = newtemp();
				emit(uminus, $2, NULL, $$, 0, yylineno);

				fprintf(rules, "term -> - expr\n");
			}
			|NOT expr 
			{
				$$->truelist = $2->falselist;
				$$->falselist = $2->truelist;
				/*$$ = newexpr(booleanexpr_e);
				$$->sym = newtemp();
				emit(not, $2, NULL, $$, 0, yylineno);*/

				fprintf(rules, "term -> ! expr\n");
			}
			|INCREMENT lvalue 
			{
				expr* lvalue = $2;
				if(lvalue->type == tableitem_e) {
					$$ = emit_iftableitem(lvalue);
					emit(add, lvalue, newexpr_constnum("1"), $$, 0, yylineno);
					emit(tablesetelem, lvalue, lvalue->index, $$, 0, yylineno);
				} else {
					emit(add, lvalue, newexpr_constnum("1"), lvalue, 0, yylineno);
					$$ = newexpr(arithexpr_e);
					$$->sym = newtemp();
					emit(assign, lvalue, NULL, $$, 0, yylineno);

				}
				fprintf(rules, "term -> ++lvalue\n");
			}
			|lvalue INCREMENT 
			{
				$$ = newexpr(var_e);
				$$->sym = newtemp();

				if($1->type == tableitem_e) {
					expr* value = emit_iftableitem($1);
					emit(assign, value, NULL, $$, 0, yylineno);
					emit(add, value, newexpr_constnum("1"), value, 0, yylineno);
					emit(tablesetelem, value, $1->index, $1, 0, yylineno);
				} else {
					emit(assign, $1, NULL, $$, 0, yylineno);
					emit(add, $1, newexpr_constnum("1"), $1, 0, yylineno);
				}
				fprintf(rules, "term -> lvalue++\n");
			}
			|DECREMENT lvalue 
			{
				expr* lvalue = $2;
				if(lvalue->type == tableitem_e) {
					$$ = emit_iftableitem(lvalue);
					emit(sub, $$, newexpr_constnum("1"), $$, 0, yylineno);
					emit(tablesetelem, lvalue, lvalue->index, $$, 0, yylineno);
				} else {
					emit(sub, $2, newexpr_constnum("1"), $2, 0, yylineno);
					$$ = newexpr(arithexpr_e);
					$$->sym = newtemp();
					emit(assign, lvalue, NULL, $$, 0, yylineno);

				}
				fprintf(rules, "term -> --lvalue\n");
			}
			|lvalue DECREMENT 
			{
				$$ = newexpr(var_e);
				$$->sym = newtemp();

				if($1->type == tableitem_e) {
					expr* value = emit_iftableitem($1);
					emit(assign, value, NULL, $$, 0, yylineno);
					emit(sub, value, newexpr_constnum("1"), value, 0, yylineno);
					emit(tablesetelem, value, $1->index, $1, 0, yylineno);
				} else {
					emit(assign, $1, NULL, $$, 0, yylineno);
					emit(sub, $1, newexpr_constnum("1"), $1, 0, yylineno);
				}
				fprintf(rules, "term -> lvalue--\n");
			}
			|primary {
				$$ = $1;
				fprintf(rules, "term -> primary\n");
			}
			;

assignexpr: lvalue ASSIGN expr {
				int i;
				expr* t;
				if(t = patch($3))
					$3 = t;
				fprintf(rules, "assignexpr -> lvalue = expr\n");
				
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
					if($1->sym->value.varVal.name[0] == '_') {
						$$ = newexpr(assignexpr_e);
						$$->sym = newtemp();
						emit (assign, $1, NULL, $$, 0, yylineno);
					} else
						$$->sym = $1->sym;
					$$ = $1;
				}
			}
			;

primary:	lvalue 
			{
				$$ = $1;
				fprintf(rules, "primary -> lvalue\n");
				
			}
			|call 
			{
				fprintf(rules, "primary -> call\n");
			}
			|objectdef {fprintf(rules, "primary -> objectdef\n");}
			|LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS 
			{
				$$ = newexpr(programfunc_e);
				$$->sym = $2->sym;
				fprintf(rules, "primary -> (funcdef)\n");
			}
			|const 
			{
				fprintf(rules, "primary -> const\n");
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

				fprintf(rules, "lvalue -> ID %s \n", yylval.stringValue);
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

				fprintf(rules, "lvalue -> LOCAL ID\n");
			}
			|DOUBLE_COLON ID 
			{
				SymbolTableEntry* tmp = lookUp(0,yylval.stringValue);
				if (!tmp) {
					fprintf (stderr, "Error at line %d: undefined reference to global variable %s \n", yylineno, yylval.stringValue);
					exit(-1);
				}
				fprintf(rules, "lvalue -> ::ID\n");
				$$ = lvalue_expr(tmp);
			}
			|member {
				fprintf(rules, "lvalue -> member\n");
				$$ = $1;
			}
			;

member:		lvalue DOT ID {
				$1->type = tableitem_e;
				$1->index = newexpr_conststring($3);
				$$ = emit_iftableitem($1);

				fprintf(rules, "member -> lvalue.id\n");
			}
			|lvalue LEFT_BRACKETS expr RIGHT_BRACKETS 
			{
				expr* t;
				if(t = patch($3))
					$3 = t;
				expr* member = newexpr(tableitem_e);
				$1->type = tableitem_e;
				member->sym = emit_iftableitem($1)->sym;
				member->index = $3;
				$$ = member;

				fprintf(rules, "member -> lvalue [expr]\n");
			}
			|call DOT ID {
				fprintf(rules, "member -> call.id\n");
			}
			|call LEFT_BRACKETS expr RIGHT_BRACKETS 
			{
				patch($3);

				fprintf(rules, "member -> call [expr]\n");
			}
			;

call:		call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS 
			{
				$$ = make_call($1, $3);
				fprintf(rules, "call -> call (elist)\n");
			}
			|lvalue callsuffix 
			{
				if($2 && $2->method) {
					expr* self = $1;
					if($2->name)
						self->index = newexpr_conststring($2->name);
					$1 = emit_iftableitem(self);
					$2 = add_front($2, self);
					$2->method = 0;
				}
				$$ = make_call($1, $2);
				fprintf(rules, "call -> lvalue callsuffix\n");
			}
			|LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS 
			{
				expr* func = newexpr(programfunc_e);
				func->sym = $2->sym;
				$$ = make_call(func, $5);
				fprintf(rules, "call -> (functdef) (elist)\n");
			}
			;

callsuffix:	normcall 
			{
				$$ = $1;
				fprintf(rules, "callsuffix -> normcall\n");
			}
			|methodcall 
			{
				$$ = $1;
				fprintf(rules, "callsuffix -> methodcall\n");
			}
			;

normcall:	LEFT_PARENTHESIS elist RIGHT_PARENTHESIS 
			{
				$$ = $2;
				if($$) {
					$$->method = 0;
					$$->name = NULL;
				}
				fprintf(rules, "normcall -> (elist)\n");
			}
			;

methodcall: DOUBLE_DOT ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS 
			{
				$$ = $4;
				$$->method = 1;
				$$->name = strdup($2);
				fprintf(rules, "methodcall -> ..id (elist)\n");
			} 
			;

elist:		expr elists 
			{
				$$ = malloc(sizeof(func_t));
				$$->expr = $1;
				$$->next = $2;
				expr* t;
				if(t = patch($1))
					$$->expr = t;

				fprintf(rules, "elist -> expr elists\n");
			}
			|/*empt*/
			{
				$$ = NULL;
				fprintf(rules, "elist -> empty\n");
			}
			;

elists:		COMMA expr elists 
			{
				$$ = malloc(sizeof(func_t));
				$$->expr = $2;
				$$->next = $3;	
				expr* t;
				if(t = patch($2))
					$$->expr = t;

				fprintf(rules, "elists -> ,expr elists\n");
			}
			|/*empty*/ 
			{
				$$ = NULL;
				fprintf(rules, "elists -> empty\n");
			}
			;

objectdef:	LEFT_BRACKETS elist RIGHT_BRACKETS {fprintf(rules, "objectdef -> 	[elist]\n");}
			|LEFT_BRACKETS indexed RIGHT_BRACKETS {fprintf(rules, "objectdef -> [indexed]\n");}
			;

indexed:	indexedelem indexeds {fprintf(rules, "indexed -> indexedelem\n");}
			;

indexeds: 	COMMA indexed {fprintf(rules, "indexeds -> ,indexed\n");}
			|/*empty*/ {fprintf(rules, "indexeds -> empty\n");}
			;

indexedelem:LEFT_BRACES expr 
			{
				patch($2);

			}COLON expr RIGHT_BRACES 
			{
				patch($5);

				fprintf(rules, "indexdelem -> {expr : expr}\n");
			}
			;

block:		LEFT_BRACES
			{
				scopeUp();
			} 
			stmts RIGHT_BRACES
			{
				deactivateScope (getScope());
				scopeDown();
				$$ = $3;
				fprintf(rules, "block -> [stmts] \n");
			}
			;

funcdef:	funcprefix funcargs funcbody
			{
				exitscopespace();
				//$1->totallocals = functionLocalOffset;
				//functionLocalOffset = pop (functionLocalsStack);
				$$ = $1;
				emit (funcend, NULL, NULL, ($1), 0, yylineno);
				fprintf(rules, "funcdef -> funcprefix funcargs funcbody \n");
			}
			;

funcargs:	LEFT_PARENTHESIS {scopeUp();} idlist RIGHT_PARENTHESIS 
			{
				enterscopespace();
				resetfunctionlocaloffset();
				fprintf(rules, "funcargs -> (idlist)\n");
			}
			;

funcbody:	funcblock
			{
				exitscopespace();
				fprintf(rules, "funcbody -> funcblock\n");
			}
			;

funcprefix: 	FUNCTION funcname {
				$$ = $2;
				$$->iaddress = nextquad();
				emit(funcstart, NULL, NULL, $$, 0, yylineno);
				//push(functionLocalsStack, functionLocalOffset);
				enterscopespace();
				resetformalargsoffset();
				fprintf(rules, "funcprefix -> FUNCTION funcname\n");
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
				
				fprintf(rules, "funcname -> ID \n");

			} 
			|/*empty*/
			{
				$$ = newexpr(programfunc_e);
				$$->sym = insert(getScope(), getAFunctionName(), yylineno, E_USERFUNC);

				fprintf(rules, "funcname -> empty \n");

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
				fprintf(rules, "funcblock -> [stmts] \n");
			}
			;

const: 		INTCONST {
				$$ = newexpr_constnum(yytext);
				fprintf(rules, "const -> intconst\n");
			}
			|REALCONST {
				$$ = newexpr_constnum(yytext);
				fprintf(rules, "const -> realconst\n");
			}
			|STRING {
				$$ = newexpr_conststring(yytext);
				fprintf(rules, "const -> string\n");
			}
			|NIL {
				$$ = newexpr_constnil ();
				fprintf(rules, "const -> nil\n");
			}
			|TRUE {
				$$ = newexpr_constbool (1);
				fprintf(rules, "const -> true\n");
			}
			|FALSE {
				$$ = newexpr_constbool (0);
				fprintf(rules, "const -> false\n");
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
				fprintf(rules, "idlist -> ID ids\n"); 

			}
			|/*empty*/ {fprintf(rules, "idlist -> empty\n");}
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
				fprintf(rules, "ids -> COMMA ID ids\n");
			}
			|/*empty*/ {fprintf(rules, "ids -> empty\n");}
			;

ifstmt:		ifprefix stmt 
			{
				patchlabel($1, nextquad());
				fprintf(rules, "ifstmt -> ifprefix stmt\n");
				$$ = $2;
			}
			| ifprefix stmt elseprefix stmt
			{
				patchlabel($1, $3 + 1);
				patchlabel($3, nextquad());

				$$ = malloc(sizeof(special_t));
				$$->breaklist = merge(
					$2 ? $2->breaklist : NULL,
					$4 ? $4->breaklist : NULL
				);
				$$->contlist = merge(
					$2 ? $2->contlist : NULL, 
					$4 ? $4->contlist : NULL
				);

				fprintf(rules, "ifstmt -> ifprefix stmt elseprefix stmt\n");
			}
			;

elseprefix:	ELSE 
			{
				$$ = nextquad();
				emit(jump, 0, 0, 0, 0, yylineno);

				fprintf(rules, "elseprefix -> ELSE \n");
			}
			;

ifprefix:	IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS
			{
				expr* t;
				if(t = patch($3))
					$3 = t;
				emit(if_eq, $3, newexpr_constbool(1), newexpr_constlabel(nextquad()+2), 0 ,yylineno);
				$$ = nextquad();
				emit(jump, 0, 0, 0, 0, yylineno);

				fprintf(rules, "ifprefix -> IF (expr)\n");
			}
			;

whilestmt:	whilestart whilecond loopstmt 
			{
				list* tmp;
				if($3){
					for(tmp = $3->breaklist; tmp; tmp = tmp->next) {
						patchlabel(tmp->label, nextquad() + 1);
					}
					for(tmp = $3->contlist; tmp; tmp = tmp->next) {
						patchlabel(tmp->label, $1);
					}
				}

				emit(jump, 0, 0, newexpr_constlabel($1), 0, yylineno);

				patchlabel($2, nextquad());
				
				$$ = $3;

				fprintf(rules, "whilestmt -> whilestart whilecond loopstmt\n");
			}
			;

whilestart: WHILE 
			{
				$$ = nextquad();
				fprintf(rules, "whilestart -> WHILE\n");
			}
			;

whilecond:	LEFT_PARENTHESIS expr RIGHT_PARENTHESIS
			{
				expr* t;
				if(t= patch($2))
					$2 = t;
				
				emit(if_eq, $2, newexpr_constbool(1), newexpr_constlabel(nextquad()+2), 0 ,yylineno);
				$$ = nextquad();
				emit(jump, 0, 0, 0, 0, yylineno);

				fprintf(rules, "whilecond -> ( expr )\n");
			}
			;

loopstmt:	loopstart stmt loopend 
			{
				$$ = $2;
				fprintf(rules, "loopstmt -> loopstart stmt loopend\n");
			}
			;

loopstart:	/* empty */
			{
				loopcounter++;
				fprintf(rules, "loopstart -> empty\n");
			}
			;

loopend:	/* empty */
			{
				loopcounter--;
				fprintf(rules, "loopend -> empty\n");
			}
			;

forstmt:	forprefix N elist RIGHT_PARENTHESIS N loopstmt N
			{
				list* tmp;
				for(tmp = $6->breaklist; tmp; tmp = tmp->next) {
					patchlabel(tmp->label, nextquad());
				}
				for(tmp = $6->contlist; tmp; tmp = tmp->next) {
					patchlabel(tmp->label, $2 + 1);
				}

				patchlabel($1->enter, $5 + 1);
				patchlabel($2, nextquad());
				patchlabel($5, $1->test);
				patchlabel($7, $2 + 1);

				$$ = $6;
				fprintf(rules, "forstmt -> forprefix N elist) N stmt N\n");
			}
			;

forprefix:	FOR LEFT_PARENTHESIS elist SEMICOLON M expr SEMICOLON
			{
				$$ = malloc(sizeof(for_t));
				$$->test = $5;
				$$->enter = nextquad();

				patch($6);

				fprintf(rules, "forprefix -> FOR (elist; expr;\n");
			}

M:			/* empty */ 
			{
				$$ = nextquad();
				fprintf(rules, "M -> empty\n");
			}
			;

N:			/* empty */ 
			{
				$$ = nextquad();
				emit(jump, 0, 0, 0, 0, yylineno);

				fprintf(rules, "N -> empty\n");
			}
			;


returnstmt: RETURN expr SEMICOLON
			{
				patch($2);

				fprintf(rules, "returnstmt -> return expr;\n");
			}
			|RETURN SEMICOLON{fprintf(rules, "returnstmt -> return; \n");}
			;
%%

int yyerror (char* yaccProvidedMessage) {
	fprintf(stderr, "%s: at line %d, before token %s\n", yaccProvidedMessage, yylineno, yytext);
	fprintf(stderr, "INPUT NOT VALID\n");
	//exit(-1);
}

int main (int argc, char** argv) {
	out = fopen("lex.log", "w");
	rules = fopen("rules.log", "w");
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