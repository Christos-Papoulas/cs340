#all: 
#	@echo "run ./alpha inputfile (optional outfile)"
#	flex --outfile=alpha.c scanner.l
#	bison --yacc --defines --output=parser.c parser.y -v
#	gcc -o alpha alpha.c parser.c symbolTable.c quads.c final_code.c const.c avm.c avm_mem.c -g

#bonus: lex/lexeme.c
#	gcc -o lexeme lex/lexeme.c
	

syntax.out: parser.o scanner.o symbolTable.o quads.o final_code.o const.o avm.o avm_mem.o avm_table.o dispatcher.o avm_assign.o execute.o avm_error.o avm_string.o avm_arithm.o avm_tobool.o avm_jmp.o lib_funcs.o
	@echo 'linking files --> syntax.out'
	gcc -o alpha parser.o scanner.o symbolTable.o quads.o final_code.o const.o avm.o avm_mem.o avm_table.o dispatcher.o avm_assign.o execute.o avm_error.o avm_string.o avm_arithm.o avm_tobool.o avm_jmp.o lib_funcs.o -g 

parser.o: parser.y quads.h symbolTable.h
	@echo 'yaccing parser.y --> parser.c'
	bison -v --yacc --defines --output=parser.c parser.y 
	gcc  -c -g parser.c

scanner.o: scanner.l 
	@echo 'flexing scanner.l --> scanner.c'
	flex --outfile=scanner.c scanner.l
	bison -v --yacc --defines --output=parser.c parser.y 
	@echo 'compiling scanner.c --> scanner.o'
	gcc  -c -g scanner.c 

symbolTable.o: symbolTable.c symbolTable.h
	@echo 'compiling symtable.c --> symtable.o'
	gcc  -c -g symbolTable.c

quads.o: quads.c quads.h
	@echo 'compiling quads.c --> quads.o'
	gcc  -c -g quads.c

final_code.o: final_code.c final_code.h
	@echo 'compiling final_code.c --> final_code.o'
	gcc  -c -g final_code.c

const.o: const.c const.h
	@echo 'compiling const.c --> const.o'
	gcc  -c -g const.c

avm.o: avm.c avm.h
	@echo 'compiling avm.c --> avm.o'
	gcc  -c -g avm.c

avm_mem.o: avm_mem.c avm_mem.h final_code.h
	@echo 'compiling avm_mem.c --> avm_mem.o'
	gcc  -c -g avm_mem.c

avm_table.o: avm_table.c avm_table.h avm_mem.h
	@echo 'compiling avm_table.c --> avm_table.o'
	gcc  -c -g avm_table.c

dispatcher.o: dispatcher.c dispatcher.h final_code.h
	@echo 'compiling dispatcher.c --> dispatcher.o'
	gcc  -c -g dispatcher.c

avm_assign.o: avm_assign.c 
	@echo 'compiling avm_assign.c --> avm_assign.o'
	gcc  -c -g avm_assign.c

execute.o: execute.c dispatcher.h
	@echo 'compiling execute.c --> execute.o'
	gcc  -c -g execute.c

avm_error.o: avm_error.c avm_error.h
	@echo 'compiling avm_error.c --> avm_error.o'
	gcc  -c -g avm_error.c

avm_string.o: avm_string.c avm_string.h
	@echo 'compiling avm_string.c --> avm_string.o'
	gcc  -c -g avm_string.c

avm_arithm.o: avm_arithm.c avm_arithm.h
	@echo 'compiling avm_arithm.c --> avm_arithm.o'
	gcc  -c -g avm_arithm.c
	
avm_tobool.o: avm_tobool.c avm_tobool.h
	@echo 'compiling avm_tobool.c --> avm_tobool.o'
	gcc  -c -g avm_tobool.c

avm_jmp.o: avm_jmp.c avm_jmp.h
	@echo 'compiling avm_jmp.c --> avm_jmp.o'
	gcc  -c -g avm_jmp.c

lib_funcs.o: lib_funcs.c lib_funcs.h
	@echo 'compiling lib_funcs.c --> lib_funcs.o'
	gcc  -c -g lib_funcs.c

all: syntax.out

clean: 
	rm -rfv *.o alpha alpha.c lex.log rules.log symtable.log *.output parser.c parser.h