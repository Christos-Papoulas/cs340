all: 
	@echo "run ./alpha inputfile (optional outfile)"
	flex --outfile=alpha.c scanner.l
	bison --yacc --defines --output=parser.c parser.y -v
	gcc -o alpha alpha.c parser.c symbolTable.c -g

bonus: lex/lexeme.c
	gcc -o lexeme lex/lexeme.c
	
clean: 
	rm -rfv alpha alpha.c lex.log *.output parser.c parser.h


	