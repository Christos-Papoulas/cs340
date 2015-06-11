#include "avm_string.h"

typedef char* (*tostring_func_t)(avm_memcell*);

tostring_func_t tostringFuncs[] = {
   integer_tostring,
   double_tostring,
   string_tostring,
   bool_tostring,
   table_tostring,
   userfunc_tostring,
   libfunc_tostring,
   nil_tostring,
   undef_tostring
};

char* avm_tostring(avm_memcell* m) {	
	assert(m->type >= 0 && m->type <= undef_m);
	return (*tostringFuncs[m->type])(m);
}

char* integer_tostring(avm_memcell* m) {
	assert(m && m->type == integer_m);
	char* buf =malloc(11*sizeof(char));
	//char buf[11];
	sprintf(buf,"%d",(int)m->data.intVal);
   	return buf;
}
char* double_tostring(avm_memcell* m) {	
	assert(m && m->type == double_m);
	char* buf= malloc(11*sizeof(char));
	sprintf(buf,"%lf",m->data.doubleVal);
	return buf;
}
char* string_tostring(avm_memcell* m) {
	
	assert(m && m->type == string_m);
	char* buf;
	buf = strdup(m->data.strVal);
	return buf;
}
char* bool_tostring(avm_memcell* m) {

	assert(m && m->type == bool_m);
	if(m->data.boolVal == 0)
		return "false";
	else return "true";
}
char* userfunc_tostring(avm_memcell* m) {
	assert(m && m->type == userfunc_m);
	char *buf=malloc(50*sizeof(char));
	sprintf(buf,"%d",m->data.funcVal);
	return buf;
}
char* libfunc_tostring(avm_memcell* m) {
	assert(m && m->type == libfunc_m);
	char *buf;
	buf=strdup(m->data.libfuncVal);
	return buf;
}

char* nil_tostring(avm_memcell* m) {	
	assert(m && m->type == nil_m);
	return "nil";
}

char* undef_tostring(avm_memcell* m) {
	assert(m && m->type == undef_m);
	return "undef";
}


char* table_tostring(avm_memcell* m) {
	assert(m && m->type == table_m);
	/* den thelei sympliroma */
}