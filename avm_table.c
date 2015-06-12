#include "avm_table.h"

void avm_tablebucketsdestroy(avm_table_bucket** p){
	unsigned int i = 0;
	avm_table_bucket* b;
	avm_table_bucket* del;
	for(i = 0; i < AVM_TABLE_HASHSIZE; i++){
		for (b=*p; b;) {
			del=b;
			b=b->next;
			avm_memcellclear(del->key);
			avm_memcellclear(del->value);
			free(del);		
		}
		p[i] = ((avm_table_bucket*) 0);
	}	
}

void avm_tableincrefcounter(avm_table* t) { t->refCounter++; }

void avm_tabledestroy(avm_table* t) {
	avm_tablebucketsdestroy(t->strIndexed);
	avm_tablebucketsdestroy(t->numIndexed);
	free(t);
}

void avm_tabledecrefcounter(avm_table* t) { 
	assert(t->refCounter>0);
	if(!t->refCounter--){
		printf("paw na kanw free");
		avm_tabledestroy(t);
	}
}

void avm_tablebucketsinit(avm_table_bucket** t){
    unsigned int i=0;
    for(; i< AVM_TABLE_HASHSIZE; i++)
      t[i] = (avm_table_bucket*)0;

   return;
}

avm_table* avm_tablenew(void){

	avm_table* t =(avm_table*)malloc(sizeof(avm_table));
	AVM_WIPEOUT(*t);
	t->refCounter=t->total=0;
	avm_tablebucketsinit(t->numIndexed);
	avm_tablebucketsinit(t->strIndexed);
	
	return t;
}

