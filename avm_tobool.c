#include "avm_tobool.h"

char* typeStrings[]={
	"number",
	"string",
	"bool",
	"table",
	"userfunc",
	"libfunc",
	"nil",
	"undef"
};

unsigned char int_tobool (avm_memcell* m) {
   return(m->data.intVal != 0);
}

unsigned char double_tobool (avm_memcell* m) {
   return(m->data.doubleVal != 0);
}

unsigned char string_tobool(avm_memcell* m) {
	return (m->data.strVal[0] != 0);
}

unsigned char bool_tobool(avm_memcell* m) {
	return (m->data.boolVal);
}

unsigned char table_tobool(avm_memcell* m) {
	return 1;
}

unsigned char userfunc_tobool(avm_memcell* m) {
	return 1;
}

unsigned char libfunc_tobool(avm_memcell* m) {
	return 1;
}

unsigned char nil_tobool(avm_memcell* m) {	
	return 0;
}

unsigned char undef_tobool(avm_memcell* m) {
	assert(0);
	return 0;
}

tobool_func_t toboolFuncs[]= {
	int_tobool,
	double_tobool,
	string_tobool,
	bool_tobool,
	table_tobool,
	userfunc_tobool,
	libfunc_tobool,
	nil_tobool,
	undef_tobool
};

unsigned char avm_tobool(avm_memcell* m) {
	assert(m->type >=0 && m->type < undef_m);
	return (*toboolFuncs[m->type])(m);
}
