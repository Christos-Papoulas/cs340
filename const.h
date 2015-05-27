#ifndef CONST_H_
#define CONST_H_

#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>

#define EXPAND_SIZE_CONST 1024

#define CURR_SIZE_INT (totalIntConsts*sizeof(int))

#define NEW_SIZE_INT (EXPAND_SIZE_CONST*sizeof(int)+CURR_SIZE_INT)

#define CURR_SIZE_DOUBLE (totalDoubleConsts*sizeof(double))

#define NEW_SIZE_DOUBLE (EXPAND_SIZE_CONST*sizeof(double)+CURR_SIZE_DOUBLE)

typedef struct userfunc{
   unsigned int address;
   unsigned int localSize;
   char *id;
   struct userfunc *next; 
}userfunc_p; 

typedef struct strings{
   char *str;
   struct strings *next;
}strings_p;

extern unsigned int *intConsts;
extern unsigned int totalIntConsts;
extern unsigned int currIntConsts;

extern float *doubleConsts;
extern unsigned int totalDoubleConsts;
extern unsigned int currDoubleConsts;

extern char **stringConsts;
extern strings_p *head_stringConsts;
extern unsigned int currStringConsts;

extern char **namedLibfuncs;
extern unsigned int totalStringConsts;
extern strings_p *head_namedLibfuncs;

extern unsigned int currNamedLibfuncs;
extern userfunc_p *userFuncs;
extern userfunc_p *head_userFuncs;

extern unsigned int currUserFuncs;
extern unsigned int totalNamedLibfuncs;
extern unsigned int totalUserFuncs;

unsigned int userfunctions_add(char *,unsigned int ,unsigned int); 

unsigned int consts_newstring(char *); 

unsigned int consts_newdouble(float); 

unsigned int consts_newint(int); 

unsigned int libfuncs_newused (const char *); 

int consts_getint(unsigned int); 

double consts_getdouble (unsigned int); 

char *consts_getstring (unsigned int); 

char *libfuncs_getused (unsigned int);
userfunc_p* getserfunction2(unsigned int address);

userfunc_p* getuserfunction(unsigned int);
void print_userf();
#endif
