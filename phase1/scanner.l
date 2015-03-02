
%{

#include <stdlib.h>
#include <string.h>
#define YY_DECL int alpha_yylex (void* ylval)
struct alphastruct {
	int type;
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

						fprintf(out, "%d: MULTILINE NESTED COMMENT\n", yylineno);
					}
					fprintf(out, "%d: MULTILINE COMMENT\n", yylineno);
				}

			}

{lineCom}	{fprintf(out, "%d: SINGLE LINE COMMENT\n", yylineno);}	

"if"		{fprintf(out, "%d: #%d \"%s\" KEYWORD\n", yylineno, tknum++, yytext);}
"else" 		{fprintf(out, "%d: #%d \"%s\" KEYWORD\n", yylineno, tknum++, yytext);}
"while"		{fprintf(out, "%d: #%d \"%s\" KEYWORD\n", yylineno, tknum++, yytext);}
"for" 		{fprintf(out, "%d: #%d \"%s\" KEYWORD\n", yylineno, tknum++, yytext);}
"function"	{fprintf(out, "%d: #%d \"%s\" KEYWORD\n", yylineno, tknum++, yytext);}
"return"	{fprintf(out, "%d: #%d \"%s\" KEYWORD\n", yylineno, tknum++, yytext);}
"break" 	{fprintf(out, "%d: #%d \"%s\" KEYWORD\n", yylineno, tknum++, yytext);}
"continue"	{fprintf(out, "%d: #%d \"%s\" KEYWORD\n", yylineno, tknum++, yytext);}
"and" 		{fprintf(out, "%d: #%d \"%s\" KEYWORD\n", yylineno, tknum++, yytext);}
"not" 		{fprintf(out, "%d: #%d \"%s\" KEYWORD\n", yylineno, tknum++, yytext);}
"or"		{fprintf(out, "%d: #%d \"%s\" KEYWORD\n", yylineno, tknum++, yytext);}
"local" 	{fprintf(out, "%d: #%d \"%s\" KEYWORD\n", yylineno, tknum++, yytext);}
"true" 		{fprintf(out, "%d: #%d \"%s\" KEYWORD\n", yylineno, tknum++, yytext);}
"false" 	{fprintf(out, "%d: #%d \"%s\" KEYWORD\n", yylineno, tknum++, yytext);}
"nil"		{fprintf(out, "%d: #%d \"%s\" KEYWORD\n", yylineno, tknum++, yytext);}

" "			{ ; }
"\n"		{
 ; }
"\t"		{ ; }

"=" 		{fprintf(out, "%d: #%d \"%s\" OPERANT\n", yylineno, tknum++, yytext);}
"+" 		{fprintf(out, "%d: #%d \"%s\" OPERANT\n", yylineno, tknum++, yytext);}
"-" 		{fprintf(out, "%d: #%d \"%s\" OPERANT\n", yylineno, tknum++, yytext);}
"*" 		{fprintf(out, "%d: #%d \"%s\" OPERANT\n", yylineno, tknum++, yytext);}
"/" 		{fprintf(out, "%d: #%d \"%s\" OPERANT\n", yylineno, tknum++, yytext);}
"%" 		{fprintf(out, "%d: #%d \"%s\" OPERANT\n", yylineno, tknum++, yytext);}
"==" 		{fprintf(out, "%d: #%d \"%s\" OPERANT\n", yylineno, tknum++, yytext);}
"!=" 		{fprintf(out, "%d: #%d \"%s\" OPERANT\n", yylineno, tknum++, yytext);}
"++" 		{fprintf(out, "%d: #%d \"%s\" OPERANT\n", yylineno, tknum++, yytext);}
"--"		{fprintf(out, "%d: #%d \"%s\" OPERANT\n", yylineno, tknum++, yytext);}
">" 		{fprintf(out, "%d: #%d \"%s\" OPERANT\n", yylineno, tknum++, yytext);}
"<" 		{fprintf(out, "%d: #%d \"%s\" OPERANT\n", yylineno, tknum++, yytext);}
">=" 		{fprintf(out, "%d: #%d \"%s\" OPERANT\n", yylineno, tknum++, yytext);}
"<="		{fprintf(out, "%d: #%d \"%s\" OPERANT\n", yylineno, tknum++, yytext);}

"{" 		{fprintf(out, "%d: #%d \"%s\" PUNCTUATION\n", yylineno, tknum++, yytext);}
"}" 		{fprintf(out, "%d: #%d \"%s\" PUNCTUATION\n", yylineno, tknum++, yytext);}
"[" 		{fprintf(out, "%d: #%d \"%s\" PUNCTUATION\n", yylineno, tknum++, yytext);}
"]" 		{fprintf(out, "%d: #%d \"%s\" PUNCTUATION\n", yylineno, tknum++, yytext);}
"(" 		{fprintf(out, "%d: #%d \"%s\" PUNCTUATION\n", yylineno, tknum++, yytext);}
")" 		{fprintf(out, "%d: #%d \"%s\" PUNCTUATION\n", yylineno, tknum++, yytext);}
";" 		{fprintf(out, "%d: #%d \"%s\" PUNCTUATION\n", yylineno, tknum++, yytext);}
"," 		{fprintf(out, "%d: #%d \"%s\" PUNCTUATION\n", yylineno, tknum++, yytext);}
":" 		{fprintf(out, "%d: #%d \"%s\" PUNCTUATION\n", yylineno, tknum++, yytext);}
"::" 		{fprintf(out, "%d: #%d \"%s\" PUNCTUATION\n", yylineno, tknum++, yytext);}
{dot} 		{fprintf(out, "%d: #%d \"%s\" PUNCTUATION\n", yylineno, tknum++, yytext);}
".."		{fprintf(out, "%d: #%d \"%s\" PUNCTUATION\n", yylineno, tknum++, yytext);}

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
