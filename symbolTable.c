#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "symbolTable.h"

#define LIB_FUNC_NUM 12

int HASH_SIZE = 13;
int scope = 0;
size_t funcNum = 0;
SymbolTableList* stl = NULL;


struct node* top = NULL; 

const char* libfuncs_t[] = {
 "print",
 "input",
 "objectmemberkeys",
 "objecttotalmembers",
 "objectcopy",
 "totalarguments",
 "argument",
 "typeof",
 "strtonum",
 "sqrt",
 "cos",
 "sin",
};

void init() {
	int i;
	assert (stl == NULL);
	stl = malloc (sizeof (SymbolTableList));
	stl->scope = 0;
	stl->st = malloc (sizeof(SymbolTableEntry*)*HASH_SIZE);
	stl->next = NULL;
	for (i=0; i<HASH_SIZE; i++) {
		stl->st[i] = malloc(sizeof(SymbolTableEntry));
		stl->st[i]->next = NULL;
		stl->st[i]->hasData = 0;
	}
	for (i = 0; i < 12; i++) {
		insertTo(0, libfuncs_t[i], E_LIBFUNC, 0);
	}
}



unsigned long hash(const char *str) {
	size_t len = strlen(str);
   unsigned long hash, i;
    for(hash = i = 0; i < len; ++i)
    {
        hash += str[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

unsigned long hashFunction(const char *str) {
	return hash(str) % HASH_SIZE;
}


SymbolTableEntry* insertToHashTable(SymbolTableList* h, int scope, const char* name, enum SymbolTableType t, int line) {
	int key = hashFunction(name);
	SymbolTableEntry* tmp;
	if(!h->st[key]){
		h->st[key] = malloc(sizeof(SymbolTableEntry));
		h->st[key]->hasData = 0;
	}
	if(!h->st[key]->hasData) {
		h->st[key]->isActive = 1;
		h->st[key]->hasData = 1;
		h->st[key]->type = t;
		h->st[key]->next = NULL;
		switch (t) {
			case E_GLOBAL:
			case E_LOCAL:
			case E_FORMAL:
				h->st[key]->value.varVal.name = strdup(name);
				h->st[key]->value.varVal.scope = scope;
				h->st[key]->value.varVal.line = line;
				break;
			case E_USERFUNC:
			case E_LIBFUNC:
				h->st[key]->value.funcVal.name = strdup(name);
				h->st[key]->value.funcVal.scope = scope;
				h->st[key]->value.funcVal.line = line;
				break;
			default: 
				assert(0);
		}
		assert(h->st[key]->type == t);
		assert(h->st[key]->isActive);
		return h->st[key];
	}

	// collision!
	for (tmp=h->st[key]; ; tmp = tmp->next) {
		if (!tmp->next) {
			tmp->next = malloc(sizeof(SymbolTableEntry));
			tmp->next->isActive = 1;
			tmp->next->hasData = 1;
			tmp->next->type = t;
			tmp->next->next = NULL;
			switch (t) {
				case E_GLOBAL:
				case E_LOCAL:
				case E_FORMAL:
					tmp->next->value.varVal.name = strdup(name);
					tmp->next->value.varVal.scope = scope;
					tmp->next->value.varVal.line = line;
					break;
				case E_USERFUNC:
				case E_LIBFUNC:
					tmp->next->value.funcVal.name = strdup(name);
					tmp->next->value.funcVal.scope = scope;
					tmp->next->value.funcVal.line = line;
					break;
				default: 
					assert(0);
			}
			assert(tmp->next->type == t);
			assert(tmp->next->isActive);
			return tmp->next;
		}
	}
}

SymbolTableEntry* insertTo(int scope, const char* name, enum SymbolTableType t, int line) {
	assert (stl != NULL);
	SymbolTableList* l_tmp;
	int s, i;
	for (l_tmp = stl, s = 1; s <= scope; s++) {
		if (!l_tmp->next) {
			l_tmp->next = malloc(sizeof(SymbolTableList));
			l_tmp->next->st = NULL;
			l_tmp->next->next = NULL;
			l_tmp->next->scope = s;
		}
		l_tmp = l_tmp->next;
	}

	if(!l_tmp->st) {
		l_tmp->st =  malloc (sizeof(SymbolTableEntry*)*HASH_SIZE);
		for (i=0; i<HASH_SIZE; i++) {
			l_tmp->st[i] = malloc(sizeof(SymbolTableEntry));
			l_tmp->st[i]->next = NULL;
			l_tmp->st[i]->hasData = 0;
		}
	}
	return insertToHashTable(l_tmp, scope, name, t, line);
}

SymbolTableEntry* insert(int scope, const char* name, int line, enum SymbolTableType t) {
	return insertTo(scope, name, t, line);;
}

void printSymbolTable() {
	int i;
	FILE* symtable;
	symtable = fopen("symtable.log", "w");
	SymbolTableList* h;
	SymbolTableEntry* tmp;
	for (h = stl; h; h = h->next) {
		fprintf(symtable, "-------------- scope: %d --------------\n", h->scope);
		fprintf(symtable, "Active\ttype\tName\tscope\tline\t\n");
		for (i=0; i<HASH_SIZE; i++) {
			if(!h->st) break;
			if(h->st[i]->hasData) {
				fprintf(symtable, "%d\t", h->st[i]->isActive);
				switch (h->st[i]->type) {
					case E_GLOBAL:
						fprintf(symtable, "gl\t");
						fprintf(symtable, "%s\t%d\t%d\t\t\t",h->st[i]->value.varVal.name,
						h->st[i]->value.varVal.scope,
						h->st[i]->value.varVal.line);
						break;
					case E_LOCAL:
						fprintf(symtable, "lo\t");
						fprintf(symtable, "%s\t%d\t%d\t\t\t",h->st[i]->value.varVal.name,
						h->st[i]->value.varVal.scope,
						h->st[i]->value.varVal.line);
						break;
					case E_FORMAL:
						fprintf(symtable, "fo\t");
						fprintf(symtable, "%s\t%d\t%d\t\t\t",h->st[i]->value.varVal.name,
						h->st[i]->value.varVal.scope,
						h->st[i]->value.varVal.line);
						break;
					case E_USERFUNC:
						fprintf(symtable, "uf\t");
						fprintf(symtable, "%s\t%d\t%d\t\t\t", h->st[i]->value.funcVal.name,
						h->st[i]->value.funcVal.scope,
						h->st[i]->value.funcVal.line);
						break;
					case E_LIBFUNC:
						fprintf(symtable, "lf\t");
						fprintf(symtable, "%s\t%d\t%d\t\t\t", h->st[i]->value.funcVal.name,
						h->st[i]->value.funcVal.scope,
						h->st[i]->value.funcVal.line);
						break;
					default: 
						assert(0);

				}
				
				fprintf(symtable, "\n");
			}

			for (tmp = h->st[i]->next; tmp; tmp = tmp->next) {
				if(tmp->hasData) {
					fprintf(symtable, "%d\t", tmp->isActive);
					switch (tmp->type) {
						case E_GLOBAL:
							fprintf(symtable, "gl\t");
							fprintf(symtable, "%s\t%d\t%d\t\t\t",tmp->value.varVal.name,
							tmp->value.varVal.scope,
							tmp->value.varVal.line);
							break;
						case E_LOCAL:
							fprintf(symtable, "lo\t");
							fprintf(symtable, "%s\t%d\t%d\t\t\t",tmp->value.varVal.name,
							tmp->value.varVal.scope,
							tmp->value.varVal.line);
							break;
						case E_FORMAL:
							fprintf(symtable, "fo\t");
							fprintf(symtable, "%s\t%d\t%d\t\t\t",tmp->value.varVal.name,
							tmp->value.varVal.scope,
							tmp->value.varVal.line);
							break;
						case E_USERFUNC:
							fprintf(symtable, "uf\t");
							fprintf(symtable, "%s\t%d\t%d\t\t\t", tmp->value.funcVal.name,
							tmp->value.funcVal.scope,
							tmp->value.funcVal.line);
							break;
						case E_LIBFUNC:
							fprintf(symtable, "lf\t");
							fprintf(symtable, "%s\t%d\t%d\t\t\t", tmp->value.funcVal.name,
							tmp->value.funcVal.scope,
							tmp->value.funcVal.line);
							break;
						default: 
							assert(0);

					}
					fprintf(symtable, "\n");
				}
			}
		}
	}
}

SymbolTableEntry* lookUp(int scope, const char* name) {
	assert (stl != NULL);
	SymbolTableList* l_tmp;
	SymbolTableEntry* h_tmp;
	int s, i;
	int key = hashFunction(name);
	for (l_tmp = stl, s = 0; ; s++) {
		if(s == scope)
			break;
		l_tmp = l_tmp->next;
		if (!l_tmp) 
			return NULL;

	}
	assert (scope == l_tmp->scope);
	for (h_tmp = l_tmp->st[key]; h_tmp; h_tmp = h_tmp->next) {
		if (!h_tmp->hasData) 
			return NULL;
		switch (h_tmp->type) {
			case E_GLOBAL:
			case E_LOCAL:
			case E_FORMAL:
				if (!strcmp(h_tmp->value.varVal.name, name)) 
					return h_tmp;
				break;
			case E_USERFUNC:
			case E_LIBFUNC:
				if (!strcmp(h_tmp->value.funcVal.name, name)) 
					return h_tmp;
				break;
			default: 
				assert(0);
		}
	}
	return NULL;
}

int isLibraryFunction (const char* name) {
	int i;
	for (i=0; i<LIB_FUNC_NUM; i++) {
		if (!strcmp(name,libfuncs_t[i])) {
			return 1;
		}
	}
	return 0;
}

int getScope() {
	return scope;
}

void scopeUp() {
	scope++;
}

void scopeDown() {
	scope--;
	assert (scope>=0);
}

void deactivateScope (int scope) {
	assert(scope != 0);
	assert (stl != NULL);
	SymbolTableList* l_tmp;
	SymbolTableEntry* h_tmp;
	int s, i;

	for (l_tmp = stl, s = 0; ; s++) {
		if(s == scope || l_tmp)
			break;

		l_tmp = l_tmp->next;
		
	}

	if (l_tmp && s != 0) {
		for (i=0; i<HASH_SIZE; i++) {
			l_tmp->st[i]->isActive = 0;
			for (h_tmp = l_tmp->st[i]->next; h_tmp; h_tmp = h_tmp->next) {
				h_tmp->isActive = 0;
			}
		}
	}
}


void push(int data) {
    if (top == NULL) {
        top =(struct node *)malloc(sizeof(struct node));
        top->ptr = NULL;
        top->scope = data;
        return ;
    } 

    struct node *temp =(struct node *)malloc(sizeof(struct node));
    temp->ptr = top;
    temp->scope = data;
    top = temp; 
}

/* Pop Operation on stack */
int pop()
{
    struct node* top1 = top;
 	int scope = top1->scope;
    if (top1 == NULL) {
        top = NULL;
        return -1;
    } else
        top1 = top1->ptr;
    if(top) 
    	free(top);
    top = top1;
    return scope;
}	

int top_e() {
	if(top)
    	return top->scope;

	return -1;
}

int findn(size_t num) {
    int n;
    for(n = 0; num; n++, num /= 10)
    	;
    return n;
}

char* getAFunctionName() {
	char* str = malloc(sizeof(char)*(3+findn(funcNum)));

	sprintf(str, "_f%u\0", funcNum++);

	return str;
}