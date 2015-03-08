#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEXEME 1024

#define UNKNOWN_TOKEN	-1
#define END_OF_FILE		0
#define LE 				1
#define LT				2
#define NE 				3
#define	NOT 			4
#define EQUAL 			5
#define ASSIGN 			6
#define GE 				7
#define GT 				8
#define INCR 			9
#define PLUS 			10
#define DECR 			11
#define MINUS 			12

#define LEFT_BRACES		18
#define RIGHT_BRACES	19
#define LEFT_BRACKETS	20
#define RIGHT_BRACKETS	21
#define LEFT_PARENTHESIS 22
#define RIGHT_PARENTHESIS 23
#define SEMICOLON		24
#define COMMA			25
#define MULTIPLY		26
#define MODULES			27
#define DOT				28
#define D_DOT			29
#define COLON			30
#define D_COLON			31
#define IDENTIFIER		32

#define IF 				33
#define ELSE 			34
#define WHILE 			35
#define FOR				36
#define FUNCTION		37
#define RETURN 			38
#define BREAK 			39
#define CONTINUE 		40
#define AND 			41
#define K_NOT 			42
#define OR 				43
#define LOCAL     		44
#define TRUE 			45
#define FALSE 			46
#define NIL 			47

#define INTCONST		49
#define REALCONST		50

#define DIVISION		51
#define LINE_COMMENT	52
#define MULTILINE_COMMENT 53

#define STRING 			54



char lookAhead = '\0';
int useLookAhead = 0;
FILE* inputFile = (FILE*) 0;
char lexeme[MAX_LEXEME];
unsigned curr = 0;
unsigned lineNo = 0;

void ResetLexeme () {
	curr = 0;
}

char* GetLexeme () {
	lexeme[curr] = '\0';
	return lexeme;
}

char GetNextChar () {
	if (useLookAhead) {
		useLookAhead = 0;
		return lookAhead;
	}
	else {
		assert(!feof(inputFile));
		return fgetc(inputFile);
	}
}

void Retract (char c) {
	assert(!useLookAhead);
	useLookAhead = 1;
	lookAhead = c;
}

void CheckLine (char c) {
	if (c == '\n'){
		++lineNo;
	}
}

void ExtendLexeme (char c) {
	assert(curr < MAX_LEXEME-1);
	lexeme[curr++] = c;
}

int isComment(int commNum, int sum) {
	char c;
	while(c = GetNextChar()) {
						
		if(c == EOF) {
			fprintf(stderr, "Error: %d: Unexpected EOF insteed of close comment\n", lineNo);
			return 0;
		}
		if(c == '/') {
			c= GetNextChar();
			if (c == '*')
				return isComment(++commNum, ++sum);
			else 
				Retract(c);
		}	else if(c == '*') {
			c = GetNextChar();
			if(c=='/') {
				commNum--;
				if (commNum == 0){
					return sum;
				}
			}
			else 
				Retract(c);
		}
	}
}


int state = 0;

int gettoken () {
	state = 0;
	ResetLexeme ();
	while (1) {
		if (state == -1)
			return UNKNOWN_TOKEN;
		if (feof(inputFile))
			return END_OF_FILE;
		char c = GetNextChar();
		CheckLine(c);

		switch (state) {
			case 0:
				if (c == '<') 		state = 1;
				else if (c == '!')  state = 4;
				else if (c == '=')	state = 7;
				else if (c == '>')  state = 10;
				else if (c == '+')	state = 13;
				else if (c == '-')	state = 16;
				else if (c == '.')	state = 19;
				else if (c == ':')	state = 22;
				else if(c == '/') 	state = 31;
				else if(c == '\"')  { state = 33; ExtendLexeme(c);}
				else if (isdigit(c)) {
					state = 28;
					ExtendLexeme(c);
				}
				else if (isalpha(c)) {
					state = 25;
					ExtendLexeme(c);
				}
				else if (c == '{') {
					ExtendLexeme(c);
					return LEFT_BRACES;
				}
				else if (c == '}') {
					ExtendLexeme(c);
					return RIGHT_BRACES;
				}
				else if (c == '[')	{
					ExtendLexeme(c);
					return LEFT_BRACKETS;
				}
				else if (c == ']') {
					ExtendLexeme(c);
					return RIGHT_BRACKETS;
				}
				else if (c == '(') {
					ExtendLexeme(c);
					return LEFT_PARENTHESIS;
				}
				else if (c == ')') {
					ExtendLexeme(c);
					return RIGHT_PARENTHESIS;
				}
				else if (c == ';') {
					ExtendLexeme(c);
					return SEMICOLON;
				}
				else if (c == ',') {
					ExtendLexeme(c);
					return COMMA;
				}
				else if (c == '*') {
					ExtendLexeme(c);
					return MULTIPLY;
				}
				else if (c == '%') {
					ExtendLexeme(c);
					return MODULES;
				} 
				else {
					state = -1;
					continue;
				}

				break;

			case 1:
				if (c == '=') {
					ExtendLexeme(c);
					return LE;
				}
				Retract(c);
				return LT;

			case 4:
				if (c == '=') {
					ExtendLexeme(c);
					return NE;
				}
				Retract(c);
				return NOT;

			case 7:
				if (c == '=') {
					ExtendLexeme(c);
					return EQUAL;
				}
				Retract(c);
				return ASSIGN;

			case 10:
				if (c == '=') {
					ExtendLexeme(c);
					return GE;
				}		
				Retract(c);
				return GT;

			case 13:
				if (c == '+') {
					ExtendLexeme(c);
					return INCR;
				}
				Retract(c);
				return PLUS;

			case 16:
				if (c == '-') {
					ExtendLexeme(c);
					return DECR;
				}
				Retract(c);
				return MINUS;

			case 19:
				if (c == '.') {
					ExtendLexeme(c);
					return D_DOT;
				}
				Retract(c);
				return DOT;

			case 22: 
				if (c == ':') {
					ExtendLexeme(c);
					return D_COLON;
				}
				Retract(c);
				return COLON;

			case 25:
				if (isalpha(c) || isdigit(c)) {
					state = 25;
					ExtendLexeme(c);
				} else {
					Retract(c);
					if( !strcmp(GetLexeme(), "if") ) {
						return IF;
					} else if (!strcmp(GetLexeme(), "else") ) {
						return ELSE;
					} else if (!strcmp(GetLexeme(), "while") ) {
						return WHILE;
					} else if (!strcmp(GetLexeme(), "for") ) {
						return FOR;
					} else if (!strcmp(GetLexeme(), "function") ) {
						return FUNCTION;
					} else if (!strcmp(GetLexeme(), "return") ) {
						return RETURN;
					} else if (!strcmp(GetLexeme(), "break") ) {
						return BREAK;
					} else if (!strcmp(GetLexeme(), "continue") ) {
						return CONTINUE;
					}else if (!strcmp(GetLexeme(), "and") ) {
						return AND;
					} else if (!strcmp(GetLexeme(), "not") ) {
						return K_NOT;
					} else if (!strcmp(GetLexeme(), "or") ) {
						return OR;
					} else if (!strcmp(GetLexeme(), "local") ) {
						return LOCAL;
					} else if (!strcmp(GetLexeme(), "true") ) {
						return TRUE;
					} else if (!strcmp(GetLexeme(), "false") ) {
						return FALSE;
					} else if (!strcmp(GetLexeme(), "nil") ) {
						return NIL;
					}
					return IDENTIFIER;
				}
				break;

			case 28:
				if(isdigit(c)) {
					state = 28;
					ExtendLexeme(c);
				} else if (c == '.') {
					state = 29;
					ExtendLexeme(c);
				} else {
					return INTCONST;
				}
				break;
			
			case 29:
				if(isdigit(c)) {
					ExtendLexeme(c);
					state = 29;
				} else {
					return REALCONST;
				}
				break;

			case 31:
				if(c == '/') {
					while(GetNextChar() != '\n') 
						;

					return LINE_COMMENT;
				} else if(c == '*') {
					isComment(1, 1);
					return MULTILINE_COMMENT;
				}
				else
					return DIVISION;
				break;

			case 33:
				ExtendLexeme(c);
				while((c = GetNextChar()) != '\"') {
					if(c != '\\') {
						ExtendLexeme(c);
					} else {
						c = GetNextChar();
						if (c=='a')			ExtendLexeme('\a');
						else if (c=='b')	ExtendLexeme('\b');
						else if (c=='f')	ExtendLexeme('\f');
						else if (c=='n') 	ExtendLexeme('\n');
						else if (c=='r')	ExtendLexeme('\r');
						else if (c=='t')	ExtendLexeme('\t');
						else if (c=='v')	ExtendLexeme('\v');
						else if (c=='\"')	ExtendLexeme('\"');
						else if (c=='\'')	ExtendLexeme('\'');
						else if (c=='\\')	ExtendLexeme('\\');
						else {
							fprintf(stderr, "Warning: %d: Unknown special character %c\n", lineNo, c);
							ExtendLexeme('\\');
							ExtendLexeme(c);
						}
					}
					ExtendLexeme(c);
				}
				ExtendLexeme(c);
				return STRING;
		}
	}

}

int main(int argc, char** argv) {
	if (argc > 1) {
		if (!(inputFile =fopen(argv[1], "r"))) {
			fprintf(stderr, "Can't read the file\n");
			return 1;
		}
	} else
		inputFile = stdin;
	int tkn = 0;
	while(1) {
		int s = gettoken () ;
		switch (s) {
			case END_OF_FILE:
				return ;
			case LT:
				fprintf(stdout, "%d: #%d \"<\" OPERATOR LESS_THAN\n", lineNo, tkn++);
				break;
			case LE:
				fprintf(stdout, "%d: #%d \"<=\" OPERATOR LESS_EQUAL\n", lineNo, tkn++);
				break;
			case NE:
				fprintf(stdout, "%d: #%d \"!=\" OPERATOR NOT_EQUAL\n", lineNo, tkn++);
				break;
			case NOT:
				fprintf(stdout, "%d: #%d \"!\" OPERATOR NOT\n", lineNo, tkn++);
				break;
			case EQUAL:
				fprintf(stdout, "%d: #%d \"==\" OPERATOR EQUAL\n", lineNo, tkn++);
				break;
			case ASSIGN:
				fprintf(stdout, "%d: #%d \"=\" OPERATOR ASSIGN\n", lineNo, tkn++);
				break;
			case GE:
				fprintf(stdout, "%d: #%d \">=\" OPERATOR GREATER_EQUAL\n", lineNo, tkn++);
				break;
			case GT:
				fprintf(stdout, "%d: #%d \">\" OPERATOR GREATER_THAN\n", lineNo, tkn++);
				break;
			case INCR:
				fprintf(stdout, "%d: #%d \"++\" OPERATOR INCREMENT\n", lineNo, tkn++);
				break;
			case PLUS:
				fprintf(stdout, "%d: #%d \"+\" OPERATOR PLUS\n", lineNo, tkn++);
				break;
			case DECR:
				fprintf(stdout, "%d: #%d \"--\" OPERATOR DECREMENT\n", lineNo, tkn++);
				break;
			case MINUS:
				fprintf(stdout, "%d: #%d \"-\" OPERATOR MINUS\n", lineNo, tkn++);
				break;
			case LEFT_BRACES:
				fprintf(stdout, "%d: #%d \"{\" DELIMITER LEFT_BRACES\n", lineNo, tkn++);
				break;
			case RIGHT_BRACES:
				fprintf(stdout, "%d: #%d \"}\" DELIMITER RIGHT_BRACES\n", lineNo, tkn++);
				break;
			case LEFT_BRACKETS:
				fprintf(stdout, "%d: #%d \"[\" DELIMITER LEFT_BRACKETS\n", lineNo, tkn++);
				break;
			case RIGHT_BRACKETS:
				fprintf(stdout, "%d: #%d \"]\" DELIMITER RIGHT_BRACKETS\n", lineNo, tkn++);
				break;
			case LEFT_PARENTHESIS:
				fprintf(stdout, "%d: #%d \"(\" DELIMITER LEFT_PARENTHESIS\n", lineNo, tkn++);
				break;
			case RIGHT_PARENTHESIS:
				fprintf(stdout, "%d: #%d \")\" DELIMITER RIGHT_PARENTHESIS\n", lineNo, tkn++);
				break;
			case SEMICOLON:
				fprintf(stdout, "%d: #%d \";\" DELIMITER SEMICOLON\n", lineNo, tkn++);
				break;
			case MULTIPLY:
				fprintf(stdout, "%d: #%d \"*\" OPERATOR MULTIPLY\n", lineNo, tkn++);
				break;
			case MODULES:
				fprintf(stdout, "%d: #%d \"\%\" OPERATOR MODULES\n", lineNo, tkn++);
				break;		

			case DOT:
				fprintf(stdout, "%d: #%d \".\" DELIMITER DOT\n", lineNo, tkn++);
				break;	
			case D_DOT:
				fprintf(stdout, "%d: #%d \"..\" DELIMITER DOUBLE_DOT\n", lineNo, tkn++);
				break;	
			case COLON:
				fprintf(stdout, "%d: #%d \":\" DELIMITER COLON\n", lineNo, tkn++);
				break;	
			case D_COLON:
				fprintf(stdout, "%d: #%d \"::\" DELIMITER DOUBLE_COLON\n", lineNo, tkn++);
				break;

			case IF:
				fprintf(stdout, "%d: #%d \"if\" KEYWORD IF\n", lineNo, tkn++);
				break;
			case ELSE:
				fprintf(stdout, "%d: #%d \"else\" KEYWORD ELSE\n", lineNo, tkn++);
				break;
			case WHILE:
				fprintf(stdout, "%d: #%d \"while\" KEYWORD WHILE\n", lineNo, tkn++);
				break;
			case FOR:
				fprintf(stdout, "%d: #%d \"for\" KEYWORD FOR\n", lineNo, tkn++);
				break;
			case FUNCTION:
				fprintf(stdout, "%d: #%d \"function\" KEYWORD FUNCTION\n", lineNo, tkn++);
				break;
			case RETURN:
				fprintf(stdout, "%d: #%d \"return\" KEYWORD RETURN\n", lineNo, tkn++);
				break;
			case BREAK:
				fprintf(stdout, "%d: #%d \"break\" KEYWORD BREAK\n", lineNo, tkn++);
				break;
			case CONTINUE:
				fprintf(stdout, "%d: #%d \"continue\" KEYWORD CONTINUE\n", lineNo, tkn++);
				break;
			case AND:
				fprintf(stdout, "%d: #%d \"and\" KEYWORD AND\n", lineNo, tkn++);
				break;
			case K_NOT:
				fprintf(stdout, "%d: #%d \"not\" KEYWORD NOT\n", lineNo, tkn++);
				break;
			case OR:
				fprintf(stdout, "%d: #%d \"or\" KEYWORD OR\n", lineNo, tkn++);
				break;
			case LOCAL:
				fprintf(stdout, "%d: #%d \"local\" KEYWORD LOCAL\n", lineNo, tkn++);
				break;
			case TRUE:
				fprintf(stdout, "%d: #%d \"true\" KEYWORD TRUE\n", lineNo, tkn++);
				break;
			case FALSE:
				fprintf(stdout, "%d: #%d \"false\" KEYWORD FALSE\n", lineNo, tkn++);
				break;
			case NIL:
				fprintf(stdout, "%d: #%d \"nil\" KEYWORD NIL\n", lineNo, tkn++);
				break;

			case IDENTIFIER:
				fprintf(stdout, "%d: #%d IDENTIFIER %s\n", lineNo, tkn++, GetLexeme());
				break;

			case INTCONST:
				fprintf(stdout, "%d: #%d INTCONST %s\n", lineNo, tkn++, GetLexeme());
				break;
			case REALCONST:
				fprintf(stdout, "%d: #%d REALCONST %s\n", lineNo, tkn++, GetLexeme());
				break;

			case DIVISION: 
				fprintf(stdout, "%d: #%d \"/\" OPERATOR DIVISION\n", lineNo, tkn++);
				break;

			case LINE_COMMENT:
				fprintf(stdout, "%d: SINGLE LINE COMMENT\n", lineNo);
				break;

			case MULTILINE_COMMENT:
				fprintf(stdout, "%d: MULTILINE COMMENT\n", lineNo);
				break;

			case STRING: 
				fprintf(stdout, "%d: STRING %s\n", lineNo, GetLexeme());
				break;

		}
	}
	return  0;
}