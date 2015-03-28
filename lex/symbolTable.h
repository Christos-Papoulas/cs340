#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

typedef struct Variable {
	const char *name;
	unsigned int scope;
	unsigned int line;
} Variable;

typedef struct Function {
	const char *name;
	//List of arguments
	unsigned int scope;
	unsigned int line;
} Function;

enum SymbolTableType {
	E_GLOBAL,  
	E_LOCAL, 
	E_FORMAL,
	E_USERFUNC, 
	E_LIBFUNC
};

typedef struct SymbolTableEntry_s {
	int isActive;
	int hasData;
	union {
		Variable varVal;
		Function funcVal;
	} value;
	enum SymbolTableType type;
	struct SymbolTableEntry_s* next;
} SymbolTableEntry;

typedef struct SymbolTableList_s {
	int scope;
	SymbolTableEntry** st;
	struct SymbolTableList_s* next;
} SymbolTableList;

void init();

unsigned long hashFunction(const char *str);

void insertTo(int scope, const char* name, enum SymbolTableType t, int line);

void insert(int scope, const char* name, int line, enum SymbolTableType t);

void printSymbolTable();

SymbolTableEntry* lookUp(int scope, char* name);

int isLibraryFunction (char* name);

int getScope();
void scopeUp();
void scopeDown();

void deactivateScope (int scope);
#endif