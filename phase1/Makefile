all: Lex
	@echo "run ./alpha inputfile (optional outfile)"

Lex: scanner.l
	flex --outfile=alpha.c scanner.l
	bison --yacc --defines --output=parser.c parser.y -v
	gcc -o alpha alpha.c parser.c -g

bonus: lexeme.c
	gcc -o lexeme lexeme.c
	
clean: 
	rm -rfv alpha alpha.c lex.log *.output parser.c parser.h


	