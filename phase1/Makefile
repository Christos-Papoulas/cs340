all: Lex
	@echo "run ./alpha inputfile (optional outfile)"

Lex: scanner.l
	flex --outfile=alpha.c scanner.l
	gcc -o alpha alpha.c -g

bonus: lexeme.c
	gcc -o lexeme lexeme.c
	
clean: 
	rm -rfv alpha alpha.c
	