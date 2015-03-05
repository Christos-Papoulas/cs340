
%{

#include <stdlib.h>
#include <string.h>
#define YY_DECL int alpha_yylex (void* ylval)

enum types{
	IF,
	ELSE,
	WHILE,
	FOR,
	FUNCTION,
	RETURN,
	BREAK,
	CONTINUE,
	AND,
	NOT,
	OR,
	LOCAL,
	TRUE,
	FALSE,
	NIL
};


struct alphastruct {
};

typedef struct alphastruct* alpha_token_t;
FILE* out;
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

"if"		{fprintf(out, "%d: #%d \"%s\" KEYWORD IF\n", yylineno, tknum++, yytext);}
"else" 		{fprintf(out, "%d: #%d \"%s\" KEYWORD ELSE\n", yylineno, tknum++, yytext);}
"while"		{fprintf(out, "%d: #%d \"%s\" KEYWORD WHILE\n", yylineno, tknum++, yytext);}
"for" 		{fprintf(out, "%d: #%d \"%s\" KEYWORD FOR\n", yylineno, tknum++, yytext);}
"function"	{fprintf(out, "%d: #%d \"%s\" KEYWORD FUNCTION\n", yylineno, tknum++, yytext);}
"return"	{fprintf(out, "%d: #%d \"%s\" KEYWORD RETURN\n", yylineno, tknum++, yytext);}
"break" 	{fprintf(out, "%d: #%d \"%s\" KEYWORD BREAK\n", yylineno, tknum++, yytext);}
"continue"	{fprintf(out, "%d: #%d \"%s\" KEYWORD CONTINUE\n", yylineno, tknum++, yytext);}
"and" 		{fprintf(out, "%d: #%d \"%s\" KEYWORD AND\n", yylineno, tknum++, yytext);}
"not" 		{fprintf(out, "%d: #%d \"%s\" KEYWORD NOT\n", yylineno, tknum++, yytext);}
"or"		{fprintf(out, "%d: #%d \"%s\" KEYWORD OR\n", yylineno, tknum++, yytext);}
"local" 	{fprintf(out, "%d: #%d \"%s\" KEYWORD LOCAL\n", yylineno, tknum++, yytext);}
"true" 		{fprintf(out, "%d: #%d \"%s\" KEYWORD TRUE\n", yylineno, tknum++, yytext);}
"false" 	{fprintf(out, "%d: #%d \"%s\" KEYWORD FALSE\n", yylineno, tknum++, yytext);}
"nil"		{fprintf(out, "%d: #%d \"%s\" KEYWORD NIL\n", yylineno, tknum++, yytext);}

" "			{ ; }
"\n"		{; }
"\t"		{ ; }

"=" 		{fprintf(out, "%d: #%d \"%s\" OPERATOR ASSIGN\n", yylineno, tknum++, yytext);}
"+" 		{fprintf(out, "%d: #%d \"%s\" OPERATOR UNARY_PLUS\n", yylineno, tknum++, yytext);}
"-" 		{fprintf(out, "%d: #%d \"%s\" OPERATOR UNARY_MINUS\n", yylineno, tknum++, yytext);}
"*" 		{fprintf(out, "%d: #%d \"%s\" OPERATOR MULTIPLIES\n", yylineno, tknum++, yytext);}
"/" 		{fprintf(out, "%d: #%d \"%s\" OPERATOR DIVIDES\n", yylineno, tknum++, yytext);}
"%" 		{fprintf(out, "%d: #%d \"%s\" OPERATOR MODULUS\n", yylineno, tknum++, yytext);}
"==" 		{fprintf(out, "%d: #%d \"%s\" OPERATOR EQUAL\n", yylineno, tknum++, yytext);}
"!=" 		{fprintf(out, "%d: #%d \"%s\" OPERATOR INEQUAL\n", yylineno, tknum++, yytext);}
"++" 		{fprintf(out, "%d: #%d \"%s\" OPERATOR INCREMENT\n", yylineno, tknum++, yytext);}
"--"		{fprintf(out, "%d: #%d \"%s\" OPERATOR DECREMENT\n", yylineno, tknum++, yytext);}
">" 		{fprintf(out, "%d: #%d \"%s\" OPERATOR GREATER\n", yylineno, tknum++, yytext);}
"<" 		{fprintf(out, "%d: #%d \"%s\" OPERATOR LESS\n", yylineno, tknum++, yytext);}
">=" 		{fprintf(out, "%d: #%d \"%s\" OPERATOR GREATER_EQUAL\n", yylineno, tknum++, yytext);}
"<="		{fprintf(out, "%d: #%d \"%s\" OPERATOR LESS_EQUAL\n", yylineno, tknum++, yytext);}

"{" 		{fprintf(out, "%d: #%d \"%s\" DELIMITER LEFT_BRACES\n", yylineno, tknum++, yytext);}
"}" 		{fprintf(out, "%d: #%d \"%s\" DELIMITER RIGHT_BRACES\n", yylineno, tknum++, yytext);}
"[" 		{fprintf(out, "%d: #%d \"%s\" DELIMITER LEFT_BRACKETS\n", yylineno, tknum++, yytext);}
"]" 		{fprintf(out, "%d: #%d \"%s\" DELIMITER RIGHT_BRACKETS\n", yylineno, tknum++, yytext);}
"(" 		{fprintf(out, "%d: #%d \"%s\" DELIMITER LEFT_PARENTHESIS\n", yylineno, tknum++, yytext);}
")" 		{fprintf(out, "%d: #%d \"%s\" DELIMITER RIGHT_PARENTHESIS\n", yylineno, tknum++, yytext);}
";" 		{fprintf(out, "%d: #%d \"%s\" DELIMITER	SEMICOLON\n", yylineno, tknum++, yytext);}
"," 		{fprintf(out, "%d: #%d \"%s\" DELIMITER COMA\n", yylineno, tknum++, yytext);}
":" 		{fprintf(out, "%d: #%d \"%s\" DELIMITER COLON\n", yylineno, tknum++, yytext);}
"::" 		{fprintf(out, "%d: #%d \"%s\" DELIMITER DOUBLE_COLON\n", yylineno, tknum++, yytext);}
{dot} 		{fprintf(out, "%d: #%d \"%s\" DELIMITER POINT\n", yylineno, tknum++, yytext);}
".."		{fprintf(out, "%d: #%d \"%s\" DELIMITER DOUBLE_POINT\n", yylineno, tknum++, yytext);}

{id}		{fprintf(out, "%d: #%d \"%s\" ID\n", yylineno, tknum++, yytext);}
{intconst}	{fprintf(out, "%d: #%d \"%s\" INTCONST\n", yylineno, tknum++, yytext);}
{realconst} {fprintf(out, "%d: #%d \"%s\" REALCONST\n", yylineno, tknum++, yytext);}
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
						}
					}

				}

				fprintf(out,"%d: #%d \"%s\" STRING\n", yylineno, tknum++, str);
			}

.			{fprintf(stderr, "%d: #%d \"%s\" UKNOWN TOKKEN\n", yylineno, tknum++, yytext);}

%%


int main(int argc, char** argv) {
	alpha_token_t aayylval;
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

}