%{

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "parser.h"
// #define YY_DECL int alpha_yylex (void* ylval) 

enum types {
	E_IF,
	E_ELSE,
	E_WHILE,
	E_FOR,
	E_FUNCTION,
	E_RETURN,
	E_BREAK,
	E_CONTINUE,
	E_AND,
	E_NOT,
	E_OR,
	E_LOCAL,
	E_TRUE,
	E_FALSE,
	E_NIL,

	E_ASSIGN,
	E_UNARY_PLUS,
	E_UNARY_MINUS,
	E_MULTIPLIES,
	E_DIVIDES,
	E_MODULUS,
	E_EQUAL,
	E_INEQUAL,
	E_INCREMENT,
	E_DECREMENT,
	E_GREATER,
	E_LESS,
	E_GREATER_EQUAL,
	E_LESS_EQUAL,

	E_LEFT_BRACES,
	E_RIGHT_BRACES,
	E_LEFT_BRACKETS,
	E_RIGHT_BRACKETS,
	E_LEFT_PARENTHESIS,
	E_RIGHT_PARENTHESIS,
	E_SEMICOLON,
	E_COMMA,
	E_COLON,
	E_DOUBLE_COLON,
	E_DOT,
	E_DOUBLE_DOT,

	E_ID,
	E_INTCONST,
	E_REALCONST,
	E_STRING

};

FILE* out;

struct alphastruct {
	 char* cv;
	 int iv;
	 double dv;
	 enum types type;
	 int tokken_num;
	 int line;
	 struct alphastruct *next;
};
typedef struct alphastruct* alpha_token_t;

alpha_token_t head = NULL;

alpha_token_t new_node(char* cv, int iv, double dv, enum types type, int tokken_num, int line) {
	alpha_token_t node = malloc(sizeof(struct alphastruct));
	if(cv)
		node->cv = strdup(cv);
	node->iv = iv;
	node->dv = dv;
	node->type = type;
	node->tokken_num = tokken_num;
	node->line = line;
	node->next = NULL;
	return node;
}

alpha_token_t add_value(alpha_token_t* head, char* cv, int iv, double dv, enum types type, int tokken_num, int line) {
	alpha_token_t tmp;
	if (*head == NULL) {
		*head = new_node(cv, iv, dv, type, tokken_num, line);
		return *head;
	}
	for (tmp = *head; tmp->next != NULL; tmp = tmp->next) { ; }
	tmp->next = new_node(cv, iv, dv, type, tokken_num, line);
	return *head;
}

void print_tokkens(alpha_token_t head) {
	alpha_token_t tmp;
	
	if(head)
		for (tmp = head; tmp != NULL; tmp = tmp->next) {
			fprintf(stderr, "%d: #%d %s %d %lf %d\n", tmp->line, tmp->tokken_num, tmp->cv, tmp->iv, tmp->dv, tmp->type);	
		}
}

int tknum = 1;

%}


%option noyywrap 
%option yylineno 

id	 		[a-zA-Z][a-zA-Z_0-9]*
string		\"([^\"]|"\\\"")*\"
intconst	[0-9][0-9]*
dot			[\.]
realconst	[0-9][0-9]*[\.][0-9][0-9]*
lineCom		\/\/.*

%%

"/*"		{
				int isComment(int commNum, int sum) {
					char c;
					while(c=input()) {
										
						if(c == EOF) {
							fprintf(stderr, "Error: %d: Unexpected EOF insteed of close comment\n", yylineno);
							return 0;
						}
						if(c=='/') {
							c=input();
							if (c=='*')
								return isComment(++commNum, ++sum);
							else 
								unput(c);
						}	else if(c=='*') {
							c=input();
							if(c=='/') {
								commNum--;
								if (commNum==0){
									return sum;
								}
							}
							else 
								unput(c);
						}
					}
				}
				int sum;

				if(sum = isComment(1, 1)) {
					if(sum > 1){
						int i;
						for (i=1; i<sum; i++) {
							fprintf(out, "%d: MULTILINE NESTED COMMENT\n", yylineno);
						}
					}
					fprintf(out, "%d: MULTILINE COMMENT\n", yylineno);
				}

			}

{lineCom}	{fprintf(out, "%d: SINGLE LINE COMMENT\n", yylineno);}	

"if"		{
				fprintf(out, "%d: #%d \"%s\" KEYWORD IF\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_IF, tknum-1, yylineno);
				assert(head != NULL);
				return IF;
			}

"else" 		{
				fprintf(out, "%d: #%d \"%s\" KEYWORD ELSE\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_ELSE, tknum-1, yylineno);
				assert(head != NULL);
				return ELSE;
			}

"while"		{
				fprintf(out, "%d: #%d \"%s\" KEYWORD WHILE\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_WHILE, tknum-1, yylineno);
				assert(head != NULL);
				return WHILE;
			}

"for" 		{
				fprintf(out, "%d: #%d \"%s\" KEYWORD FOR\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_FOR, tknum-1, yylineno);
				assert(head != NULL);
				return FOR;
			}

"function"	{
				fprintf(out, "%d: #%d \"%s\" KEYWORD FUNCTION\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_FUNCTION, tknum-1, yylineno);
				assert(head != NULL);
				return FUNCTION;
			}

"return"	{
				fprintf(out, "%d: #%d \"%s\" KEYWORD RETURN\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_RETURN, tknum-1, yylineno);
				assert(head != NULL);
				return RETURN;
			}

"break" 	{
				fprintf(out, "%d: #%d \"%s\" KEYWORD BREAK\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_BREAK, tknum-1, yylineno);
				assert(head != NULL);
				return BREAK;
			}

"continue"	{
				fprintf(out, "%d: #%d \"%s\" KEYWORD CONTINUE\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_CONTINUE, tknum-1, yylineno);
				assert(head != NULL);
				return CONTINUE;
			}

"and" 		{
				fprintf(out, "%d: #%d \"%s\" KEYWORD AND\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_AND, tknum-1, yylineno);
				assert(head != NULL);
				return AND;
			}

"not" 		{
				fprintf(out, "%d: #%d \"%s\" KEYWORD NOT\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_NOT, tknum-1, yylineno);
				assert(head != NULL);
				return NOT;
			}

"or"		{
				fprintf(out, "%d: #%d \"%s\" KEYWORD OR\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_OR, tknum-1, yylineno);
				assert(head != NULL);
				return OR;
			}

"local" 	{
				fprintf(out, "%d: #%d \"%s\" KEYWORD LOCAL\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_LOCAL, tknum-1, yylineno);
				assert(head != NULL);
				return LOCAL;
			}

"true" 		{
				fprintf(out, "%d: #%d \"%s\" KEYWORD TRUE\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_TRUE, tknum-1, yylineno);
				assert(head != NULL);
				return TRUE;
			}

"false" 	{
				fprintf(out, "%d: #%d \"%s\" KEYWORD FALSE\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_FALSE, tknum-1, yylineno);
				assert(head != NULL);
				return FALSE;
			}

"nil"		{
				fprintf(out, "%d: #%d \"%s\" KEYWORD NIL\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_NIL, tknum-1, yylineno);
				assert(head != NULL);
				return NIL;
			}

" "			{ ; }
"\n"		{ ; }
"\t"		{ ; }

"=" 		{
				fprintf(out, "%d: #%d \"%s\" OPERATOR ASSIGN\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_ASSIGN, tknum-1, yylineno);
				assert(head != NULL);
				return ASSIGN;
			}

"+" 		{
				fprintf(out, "%d: #%d \"%s\" OPERATOR UNARY_PLUS\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_UNARY_PLUS, tknum-1, yylineno);
				assert(head != NULL);
				return PLUS;
			}

"-" 		{
				fprintf(out, "%d: #%d \"%s\" OPERATOR UNARY_MINUS\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_UNARY_MINUS, tknum-1, yylineno);
				assert(head != NULL);
				return MINUS;
			}

"*" 		{
				fprintf(out, "%d: #%d \"%s\" OPERATOR MULTIPLIES\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_MULTIPLIES, tknum-1, yylineno);
				assert(head != NULL);
				return MULTIPLIES;
			}

"/" 		{
				fprintf(out, "%d: #%d \"%s\" OPERATOR DIVIDES\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_DIVIDES, tknum-1, yylineno);
				assert(head != NULL);
				return DIVIDES;
			}

"%" 		{
				fprintf(out, "%d: #%d \"%s\" OPERATOR MODULUS\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_MODULUS, tknum-1, yylineno);
				assert(head != NULL);
				return MODULUS;
			}

"==" 		{
				fprintf(out, "%d: #%d \"%s\" OPERATOR EQUAL\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_EQUAL, tknum-1, yylineno);
				assert(head != NULL);
				return EQUAL;
			}

"!=" 		{
				fprintf(out, "%d: #%d \"%s\" OPERATOR INEQUAL\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_INEQUAL, tknum-1, yylineno);
				assert(head != NULL);
				return INEQUAL;
			}

"++" 		{	
				fprintf(out, "%d: #%d \"%s\" OPERATOR INCREMENT\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_INCREMENT, tknum-1, yylineno);
				assert(head != NULL);
				return INCREMENT;
			}

"--"		{
				fprintf(out, "%d: #%d \"%s\" OPERATOR DECREMENT\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_DECREMENT, tknum-1, yylineno);
				assert(head != NULL);
				return DECREMENT;
			}

">" 		{
				fprintf(out, "%d: #%d \"%s\" OPERATOR GREATER\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_GREATER, tknum-1, yylineno);
				assert(head != NULL);
				return GREATER;
			}

"<" 		{
				fprintf(out, "%d: #%d \"%s\" OPERATOR LESS\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_LESS, tknum-1, yylineno);
				assert(head != NULL);
				return LESS;
			}

">=" 		{
				fprintf(out, "%d: #%d \"%s\" OPERATOR GREATER_EQUAL\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_GREATER_EQUAL, tknum-1, yylineno);
				assert(head != NULL);
				return GREATER_EQUAL;
			}

"<="		{
				fprintf(out, "%d: #%d \"%s\" OPERATOR LESS_EQUAL\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_LESS_EQUAL, tknum-1, yylineno);
				assert(head != NULL);
				return LESS_EQUAL;
			}

"{" 		{
				fprintf(out, "%d: #%d \"%s\" DELIMITER LEFT_BRACES\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_LEFT_BRACES, tknum-1, yylineno);
				assert(head != NULL);
				return LEFT_BRACES;
			}

"}" 		{
				fprintf(out, "%d: #%d \"%s\" DELIMITER RIGHT_BRACES\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_RIGHT_BRACES, tknum-1, yylineno);
				assert(head != NULL);
				return RIGHT_BRACES;
			}

"[" 		{
				fprintf(out, "%d: #%d \"%s\" DELIMITER LEFT_BRACKETS\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_LEFT_BRACKETS, tknum-1, yylineno);
				assert(head != NULL);
				return LEFT_BRACKETS;
			}

"]" 		{	
				fprintf(out, "%d: #%d \"%s\" DELIMITER RIGHT_BRACKETS\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_RIGHT_BRACKETS, tknum-1, yylineno);
				assert(head != NULL);
				return RIGHT_BRACKETS;
			}

"(" 		{
				fprintf(out, "%d: #%d \"%s\" DELIMITER LEFT_PARENTHESIS\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_LEFT_PARENTHESIS, tknum-1, yylineno);
				assert(head != NULL);
				return LEFT_PARENTHESIS;
			}

")" 		{	
				fprintf(out, "%d: #%d \"%s\" DELIMITER RIGHT_PARENTHESIS\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_RIGHT_PARENTHESIS, tknum-1, yylineno);
				assert(head != NULL);
				return RIGHT_PARENTHESIS;

			}

";" 		{
				fprintf(out, "%d: #%d \"%s\" DELIMITER SEMICOLON\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_SEMICOLON, tknum-1, yylineno);
				assert(head != NULL);
				return SEMICOLON;
			}

"," 		{
				fprintf(out, "%d: #%d \"%s\" DELIMITER COMMA\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_COMMA, tknum-1, yylineno);
				assert(head != NULL);
				return COMMA;
			}

":" 		{
				fprintf(out, "%d: #%d \"%s\" DELIMITER COLON\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_COLON, tknum-1, yylineno);
				assert(head != NULL);
				return COLON;
			}

"::" 		{
				fprintf(out, "%d: #%d \"%s\" DELIMITER DOUBLE_COLON\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_DOUBLE_COLON, tknum-1, yylineno);
				assert(head != NULL);
				return DOUBLE_COLON;
			}

{dot} 		{
				fprintf(out, "%d: #%d \"%s\" DELIMITER DOT\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_DOT, tknum-1, yylineno);
				assert(head != NULL);
				return DOT;
			}

".."		{	
				fprintf(out, "%d: #%d \"%s\" DELIMITER DOUBLE_DOT\n", yylineno, tknum++, yytext);
				add_value(&head, NULL, 0, 0, E_DOUBLE_DOT, tknum-1, yylineno);
				assert(head != NULL);
				return DOUBLE_DOT;
			}

{id}		{
				fprintf(out, "%d: #%d \"%s\" ID\n", yylineno, tknum++, yytext);
				add_value(&head, yytext, 0, 0, E_ID, tknum-1, yylineno);
				assert(head != NULL);
				yylval.stringValue = strdup(yytext);
				return ID;
			}

{intconst}	{
				fprintf(out, "%d: #%d \"%s\" INTCONST %d\n", yylineno, tknum++, yytext, atoi(yytext));
				add_value(&head, NULL, atoi(yytext), 0, E_INTCONST, tknum-1, yylineno);
				assert(head != NULL);
				return INTCONST;
			}

{realconst} {
				fprintf(out, "%d: #%d \"%s\" REALCONST %f\n", yylineno, tknum++, yytext, atof(yytext));
				add_value(&head, NULL,0, atof(yytext), E_REALCONST, tknum-1, yylineno);
				assert(head != NULL);
				return REALCONST;			}

{string} 	{
				char* str = malloc(sizeof(char)*strlen(yytext));
				int i=0;
				int j=0;
				if (yytext[strlen(yytext)-2]=='\\') {
					fprintf(stderr, "Error: %d: quotes of string do not close %s\n", yylineno, yytext);
					return ;
				}
				for (i=1; i<(strlen(yytext)-1); i++){
					if (yytext[i]!='\\'){
						str[j++]=yytext[i];
					}
					else {
						i++;
						if (yytext[i]=='a')			str[j++]='\a';
						else if (yytext[i]=='b')	str[j++]='\b';
						else if (yytext[i]=='f')	str[j++]='\f';
						else if (yytext[i]=='n') 	str[j++]='\n';
						else if (yytext[i]=='r')	str[j++]='\r';
						else if (yytext[i]=='t')	str[j++]='\t';
						else if (yytext[i]=='v')	str[j++]='\v';
						else if (yytext[i]=='\"')	str[j++]='\"';
						else if (yytext[i]=='\'')	str[j++]='\'';
						else if (yytext[i]=='\\')	str[j++]='\\';
						else {
							fprintf(stderr, "Warning: %d: Unknown special character %c\n", yylineno, yytext[i]);
							str[j++]='\\';
							str[j++]=yytext[i];
						}
					}

				}

				fprintf(out,"%d: #%d \"%s\" STRING\n", yylineno, tknum++, str);
				add_value(&head, str, 0, 0, E_INTCONST, tknum-1, yylineno);
				assert(head != NULL);
				return STRING;
			}

.			{fprintf(stderr, "%d: #%d \"%s\" UKNOWN TOKKEN\n", yylineno, tknum++, yytext);}

%%

/*
int main(int argc, char** argv) {
	alpha_token_t aayylval = NULL;
	if (argc > 1) {
		if (!(yyin =fopen(argv[1], "r"))) {
			fprintf(stderr, "Can't read the file\n");
			return 1;
		}
	} else
		yyin = stdin;
	if (argc == 3) {
		out=fopen(argv[2], "w");
	} else 
		out = stdout;
	alpha_yylex(aayylval); 
	//print_tokkens(head);
	return 0;
} 
*/