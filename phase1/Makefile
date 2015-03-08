all: Lex
	@echo "run ./alpha inputfile (optional outfile)"

Lex: scanner.l
	flex --outfile=alpha.c scanner.l
	gcc -o alpha alpha.c -g

clean: 
	rm -rfv alpha alpha.c
	