#include "const.h"

unsigned int *intConsts = 0;
unsigned int totalIntConsts = 0;
unsigned int currIntConsts = 0;

float *doubleConsts = 0;
unsigned int totalDoubleConsts = 0;
unsigned int currDoubleConsts = 0;

char **stringConsts = NULL;
strings_p *head_stringConsts  = NULL;

unsigned int currStringConsts = 0;
char **namedLibfuncs = NULL;
unsigned int totalStringConsts = 0;
strings_p *head_namedLibfuncs = NULL;
unsigned int currNamedLibfuncs = 0;
userfunc_p *userFuncs = NULL;
userfunc_p *head_userFuncs = NULL;
unsigned int currUserFuncs = 0;
unsigned int totalNamedLibfuncs = 0;
unsigned int totalUserFuncs = 0;



unsigned int userfunctions_add(char *id,unsigned int address,unsigned int localvar){
	userfunc_p *new_node = malloc(sizeof(struct userfunc));
	
	new_node->id=strdup(id);
	new_node->address=address;
	new_node->localSize=localvar;
	new_node->next=NULL;

	if(head_userFuncs == NULL){
		head_userFuncs = new_node;		
	}
	else{
		userfunc_p *tmp=head_userFuncs;
		while(tmp->next!=NULL){
			tmp=tmp->next;
		}
		tmp->next=new_node;
	}
	
	currUserFuncs++;
	return(currUserFuncs-1);	
}


static void expand_int(void){
	int * new;
	assert(totalIntConsts==currIntConsts);
	new = (int *)malloc(NEW_SIZE_INT);   
	if(intConsts)
	{     memcpy(new,intConsts,CURR_SIZE_INT);
      	free(intConsts);
	}
   	intConsts = new;
   	totalIntConsts += EXPAND_SIZE_CONST;
  	return;
}


unsigned int consts_newint(int n)
{ 
	int *new = (int *)malloc(sizeof(int));   
	if(currIntConsts == totalIntConsts){
      		expand_int();
   	}
   	new = intConsts+currIntConsts++;
   	*new = n;
   	return(currIntConsts-1);
}


static void expand_double(void){
	float *new;
	assert(totalDoubleConsts==currDoubleConsts);
  	new = (float *)malloc(NEW_SIZE_DOUBLE);
 	if(doubleConsts){
 	   	memcpy(new,doubleConsts,CURR_SIZE_DOUBLE);     
 		free(doubleConsts);
  	}  
	doubleConsts = new;
   	totalDoubleConsts += EXPAND_SIZE_CONST;
   	return;
}

unsigned int consts_newdouble(float d){
	float *new = (float *)malloc(sizeof(float));
	if(currDoubleConsts == totalDoubleConsts){
      		expand_double();
  	}
	new = doubleConsts+currDoubleConsts++;
	*new = d;
	return(currDoubleConsts-1);
}


unsigned int consts_newstring(char *s){
	strings_p *new_node=malloc(sizeof(strings_p));
	
	new_node->str=strdup(s);
	new_node->next=NULL;
	
	if(head_stringConsts==NULL){
		head_stringConsts=new_node;
		
	}
	else{
		strings_p *tmp=head_stringConsts;
		while(tmp->next!=NULL){
			tmp=tmp->next;
		}
		tmp->next=new_node;
	}
	currStringConsts++;
	return(currStringConsts-1);
}

unsigned int libfuncs_newused(const char *s){
	strings_p *new_node=malloc(sizeof(new_node));
	new_node->str=strdup(s);
	new_node->next=NULL;
	
	if(head_namedLibfuncs==NULL){
		head_namedLibfuncs=new_node;
	}
	else{
		strings_p *tmp=head_namedLibfuncs;
		while(tmp->next!=NULL){
			tmp=tmp->next;
		}
		tmp->next=new_node;
	}
	currNamedLibfuncs++;
	return(currNamedLibfuncs-1);
}


int consts_getint (unsigned int index){   
	return(intConsts[index]);
}


double consts_getdouble (unsigned int index){
   return(doubleConsts[index]);
}

char *consts_getstring (unsigned int index){
   strings_p *tmp = head_stringConsts;
   size_t i=0;
   
   for(i=0; i<index; i++){
      tmp=tmp->next;
   }
   return(tmp->str);
}


char *libfuncs_getused (unsigned int index){
   strings_p *tmp = head_namedLibfuncs;
   size_t i=0;
   
   for(i=0; i<index; i++){
      tmp=tmp->next;
   }
   return(tmp->str);
}

userfunc_p* getserfunction2(unsigned int address){
  
  userfunc_p *tmp = head_userFuncs;
 
   
   while (tmp){
 
      if (tmp->address==address)
      return tmp;

      tmp=tmp->next;
   }
   return(NULL);
}


userfunc_p* getuserfunction(unsigned int index){
   userfunc_p *tmp = head_userFuncs;
   size_t i=0;
   
   for(i=0; i<index; i++){
      tmp=tmp->next;
   }
   return(tmp);
}

void print_userf(){
	userfunc_p *new_node=head_userFuncs;
	strings_p *tmp = head_stringConsts;
	
	while(new_node!=NULL){
		
		printf("%s %d %d\n",   new_node->id,new_node->address,new_node->localSize);
		new_node=new_node->next;
	}
	while(tmp!=NULL){
		printf("%s\n",tmp->str);
		tmp=tmp->next;
	}
}
