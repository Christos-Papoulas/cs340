%{
	#include <stdio.h>
	int yyerror (char* yaccProvidedMessage);
	int alpha_yylex ();

	extern int yylineno;
	extern char* yytext;
	extern FILE* yyin;
	extern FILE* out;

%}

%union {
		char*			stringValue;
		int				intValue;
		double			realValue;
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

%left ASSIGN
%right PLUS MINUS
%left MULTIPLIES DIVIDES
%left MODULUS
%nonassoc GREATER GREATER_EQUAL LESS LESS_EQUAL
%nonassoc EQUAL INEQUAL
%right INCREMENT DECREMENT


%%

program:	stmts stmt {fprintf(stderr, "program -> stmts stmt\n");}
			|/* empty */ {fprintf(stderr, "program -> empty\n");}
			;

stmts:		stmts stmt {fprintf(stderr, "stmts -> stmts stmt\n");}
			|/* empty */ {fprintf(stderr, "stmts -> empty\n");}
			;

stmt:		expr SEMICOLON {fprintf(stderr, "stmt -> expr ;\n");}
			//|ifstmt {fprintf(stderr, "stmt -> ifstmt\n");}
			//|whilestmt {fprintf(stderr, "stmt -> whilestmt\n");}
			//|forstmt {fprintf(stderr, "stmt -> forstmt\n");}
			//|returnstmt {fprintf(stderr, "stmt -> returnstmt\n");}
			|BREAK SEMICOLON {fprintf(stderr, "stmt -> break ;\n");}	
			|CONTINUE SEMICOLON {fprintf(stderr, "stmt -> continue ;\n");}
			//|block {fprintf(stderr, "stmt -> block\n");}
			//|funcdef {fprintf(stderr, "stmt -> funcdef\n");}
			|SEMICOLON {fprintf(stderr, "stmt -> ;\n");}
			;

expr:		assignexpr {fprintf(stderr, "expr -> assignexpr\n");}
			|expr PLUS expr {fprintf(stderr, "expr -> expr + expr\n");}
			|expr MINUS expr {fprintf(stderr, "expr -> expr - expr\n");}
			|expr MULTIPLIES expr {fprintf(stderr, "expr -> expr * expr\n");}
			|expr DIVIDES expr {fprintf(stderr, "expr -> expr / expr\n");}
			|expr MODULUS expr {fprintf(stderr, "expr -> expr mod expr\n");}
			|expr GREATER expr {fprintf(stderr, "expr -> expr > expr\n");}
			|expr GREATER_EQUAL expr {fprintf(stderr, "expr -> expr >= expr\n");}
			|expr LESS expr {fprintf(stderr, "expr -> expr < expr\n");}
			|expr LESS_EQUAL expr {fprintf(stderr, "expr -> expr <= expr\n");}
			|expr EQUAL expr {fprintf(stderr, "expr -> expr == expr\n");}
			|expr INEQUAL expr {fprintf(stderr, "expr -> expr != expr\n");}

			|term {fprintf(stderr, "expr -> term\n");}
			;
/*
op:			
			|AND {fprintf(stderr, "op -> and\n");}
			|OR {fprintf(stderr, "op -> or\n");}*/
			
term: 		LEFT_PARENTHESIS expr RIGHT_PARENTHESIS {fprintf(stderr, "term -> (expr)\n");}
			|MINUS expr {fprintf(stderr, "term -> - expr\n");}
			|NOT expr {fprintf(stderr, "term -> (expr)\n");}
			|INCREMENT lvalue {fprintf(stderr, "term -> ++lvalue\n");}
			|lvalue INCREMENT {fprintf(stderr, "term -> lvalue++\n");}
			|DECREMENT lvalue {fprintf(stderr, "term -> --lvalue\n");}
			|lvalue DECREMENT {fprintf(stderr, "term -> lvalue--\n");}
			|primary {fprintf(stderr, "term -> primary\n");}
			;

assignexpr: lvalue ASSIGN expr {fprintf(stderr, "assignexpr -> lvalue = expr\n");}
			;

lvalue:		ID {fprintf(stderr, "lvalue -> ID\n");}
			;


primary:	lvalue {fprintf(stderr, "primary -> lvalue\n");}
			|const {fprintf(stderr, "primary -> const\n");}
			;

const: 		INTCONST {fprintf(stderr, "const -> intconst\n");}
			|STRING {fprintf(stderr, "const -> string\n");}
			|NIL {fprintf(stderr, "const -> nil\n");}
			|TRUE {fprintf(stderr, "const -> true\n");}
			|FALSE {fprintf(stderr, "const -> false\n");}
			;

%%

int yyerror (char* yaccProvidedMessage) {
	fprintf(stderr, "%s: at line %d, before token %s\n", yaccProvidedMessage, yylineno, yytext);
	fprintf(stderr, "INPUT NOT VALID\n");
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

	yyparse();
	return 0;
}