#ifndef AVM_TABLE_H_
#define AVM_TABLE_H_
#include <stdlib.h>
#include <assert.h>

#include "avm_mem.h"
#define AVM_TABLE_HASHSIZE 211

typedef	struct avm_table_bucket{
	struct avm_Memcell*		key;
	struct avm_Memcell*		value;
	struct avm_table_bucket *next;
}avm_table_bucket;

typedef struct avm_table {
	unsigned 		refCounter;
	avm_table_bucket*	strIndexed[AVM_TABLE_HASHSIZE];
	avm_table_bucket*	numIndexed[AVM_TABLE_HASHSIZE];
	unsigned 		total;
}avm_table;

avm_table* avm_tablenew();
void avm_tabledestroy(avm_table* t);
struct avm_Memcell* avm_tablegetelem (avm_table* table,struct avm_Memcell* index);
void avm_tablesetelem(avm_table* table,struct avm_Memcell* index,struct avm_Memcell* content);

void avm_tableincrefcounter(avm_table* t);

void avm_tabledecrefcounter(avm_table* t);

void avm_tablebucketsinit(avm_table_bucket** t);

void avm_tablebucketsdestroy(avm_table_bucket** p);


#endif /*AVM_TABLE_H_*/