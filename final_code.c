#include "final_code.h"
#include "const.h"

void emit_instruction(instruction* t);
void expand_instruction();
void back_patch_return(returnlist* list, unsigned int label);
void hitError(int r) ;

extern quad* quads; /* declaration is in the quad.c */
extern unsigned int total; /* declaration is in the quad.c */
extern unsigned int currQuad; /* declaration is in the quad.c */


func* f_head = NULL;

incomplete_jump* ij_head = NULL;
unsigned int ij_total = 0;

unsigned int currinstr = 0;
unsigned int totalinstr = 0;
instruction* instructions = NULL; /* the table with instructions */


unsigned int processingQuad = 0;

//extern LocalSizeList *head_sizeList;

generator_func_t generators_t[] = {
	generate_ASSING, 
	generate_ADD, 
	generate_SUB, 
	generate_MUL, 
	generate_DIV, 
	generate_MOD, 
	generate_UMINUS, 
	generate_AND, 
	generate_OR, 
	generate_NOT, 
	generate_IF_EQ, 
	generate_IF_NOTEQ, 
	generate_IF_LESSEQ, 
	generate_IF_GREATEREQ,
	generate_IF_LESS, 
	generate_IF_GREATER,
	generate_CALL,
	generate_PARAM,
	generate_RETURN,
	generate_GETRETVAL, 
	generate_FUNCSTART,
	generate_FUNCEND,
	generate_NEWTABLE, /* TABLECREATE */
	generate_TABLEGETELEM,
	generate_TABLESETELEM,
	generate_JUMP,
	generate_NOP
};

vmarg* make_operand(expr* e) {
	vmarg* arg;

	/* check if e is null, bacaliko tropos!*/
	if(e == NULL)
		return NULL;	
	arg = new_vmarg();
	assert(arg != NULL);	
	switch(e->type)	{
		/* All those below use a variable for storage */
		case var_e:
		case tableitem_e:
		case arithexpr_e:
		case newtable_e:
		case assignexpr_e:{
			assert(e->sym != NULL);
			arg->val = e->sym->offset;
			switch(e->sym->scopeSpace) {
				case programvar: 	
					arg->type = global_a; 
					break;
				case functionlocal:	
					arg->type = local_a; 
					break;
				case formalarg:		
					arg->type = formal_a; 
					break;
				default:
					fprintf(stderr, "invalid scopeSpase %d\n", e->sym->scopeSpace);
					assert(0);
			}

			break;
		}
		/* Constants */
		case constbool_e:
		case booleanexpr_e:
			arg->val = e->boolConst; /* if 0 is false else true*/
			arg->type = bool_a;
			break;
		case conststring_e:
			arg->val = consts_newstring(e->strConst);
			arg->type = string_a;
			break;
		case constnum_e:
			arg->val = consts_newint(e->numConst);
			arg->type = integer_a;
			break;
		case nil_e:
			//arg->val = e->u.nil_val;
			arg->type = nil_a;
			break;
		/* functions */
		case programfunc_e:

			arg->type = userfunc_a;

			/*LocalSizeList *tmp=head_sizeList;
			assert(tmp != NULL);
			while(strcmp(e->sym->name,tmp->name)!=0)
			{
				tmp=tmp->next;
				if(tmp==NULL)
					break;
			}
			
			arg->val = userfunctions_add(e->sym->name,0,tmp->localSize);*/

			arg->val = e->sym->taddress; /* tha mpei sto symtable */
		
			break;
		case libraryfunc_e:
			arg->type = libfunc_a;
			arg->val = libfuncs_newused(e->sym->value.funcVal.name);
			break;
		case constlabel_e:
			arg->type = label_a;
			arg->val = e->labelConst;
			break;
		default:/*assignexpr_e,double_e,*/
			fprintf(stderr, "Invalid type of expr %d\n", e->type);
			assert(0);
	}
	return arg;
}

vmarg* new_vmarg() {
	return malloc(sizeof(vmarg));
}

vmarg* make_retvaloperand(vmarg* arg) {
	arg->type = retval_a;
	return arg;
}

void add_incomplete_jump(unsigned int instrNo, unsigned int iaddress) {
	incomplete_jump* new = malloc(sizeof(incomplete_jump));
	assert(new != NULL);
	
	new->instrNo = instrNo;
	new->iaddress = iaddress;
	
	new->next = ij_head;
	ij_head = new;
	
	ij_total++;
	return ;
}

void patch_incomplete_jumps() {
	incomplete_jump* x;
	for(x = ij_head; x != NULL; x = x->next) {
		if(x->iaddress == nextquad())
			instructions[x->instrNo].result->val = nextinstructionlabel(); //target code size
		else
			instructions[x->instrNo].result->val = quads[x->iaddress].taddress;
	}
	return ;
}

void generate(vmopcode op, quad* q) {
	instruction* t = malloc(sizeof(instruction));
	assert(t != NULL);

	t->opcode = op;
	t->arg1 = make_operand(q->arg1);
	t->arg2 = make_operand(q->arg2);
	t->result = make_operand(q->result);
	q->taddress = nextinstructionlabel();
	emit_instruction(t);
	
	return ;
}

unsigned int nextinstructionlabel() {
	return currinstr;
}

void generate_ADD(quad* q) {
	generate(add_v, q);
	return ;
}

void generate_SUB(quad* q) {
	generate(sub_v, q);
	return ;
}

void generate_MUL(quad* q) {
	generate(mul_v, q);
	return ;
}

void generate_DIV(quad* q) {
	generate(mul_v, q);
	return ;
}

void generate_MOD(quad* q) {
	generate(mod_v, q);
	return ;
}

void generate_NEWTABLE(quad* q) {
	generate(newtable_v, q);
	return ;
}

void generate_TABLEGETELEM(quad* q) {
	generate(tablegetelem_v, q);
	return ;
}

void generate_TABLESETELEM(quad* q) {
	generate(tablesetelem_v, q);
	return ;
}

void generate_ASSING(quad* q) {
	generate(assign_v, q);
	return ;
}

void generate_NOP(quad* q) {
	instruction* t;
	t = malloc(sizeof(instruction));
	assert( t != NULL && q != NULL);
	t->opcode = nop_v;
	t->result = NULL;
	t->arg1 = NULL;
	t->arg2 = NULL;
	
	emit_instruction(t);
	return ;
}

void generate_JUMP(quad* q) {
	generate_relational(jump_v, q);
	return ;
}

void generate_IF_EQ(quad* q) {
	generate_relational(jeq_v, q);
	return ;
}

void generate_IF_NOTEQ(quad* q) {
	generate_relational(jne_v, q);
	return ;
}

void generate_IF_GREATER(quad* q) {
	generate_relational(jgt_v, q);
	return ;
}

void generate_IF_GREATEREQ(quad* q) {
	generate_relational(jeq_v, q);
	return ;
}

void generate_IF_LESS(quad* q) {
	generate_relational(jlt_v, q);
	return ;
}

void generate_IF_LESSEQ(quad* q) {
	generate_relational(jle_v, q);
	return ;
}

vmarg* reset_operand() {
   return NULL;
}

void generate_NOT(quad* q) {
	instruction *t, *i, *j, *k ;
	
	q->taddress = nextinstructionlabel();

	/***********jeq*************/
	t = malloc(sizeof(instruction));
	t->opcode = jeq_v;

	t->arg1 = make_operand(q->arg1);
	t->arg2 = make_booloperand(t->arg2, 0);/* 0 is false */	
	t->result = new_vmarg();
	t->result->type = label_a;
	t->result->val = nextinstructionlabel() + 3;
	emit_instruction(t);

	/*********assign*************/
	k=(instruction*)malloc(sizeof(instruction));
	k->opcode=assign_v;
	k->arg1 = make_booloperand(k->arg1, 0);
	k->arg2 = reset_operand();
	k->result = make_operand(q->result);
	emit_instruction(k);
	
	/**********jump**************/
	i = malloc(sizeof(instruction));
	assert(i != NULL);
	i->opcode = jump_v;
	i->result = new_vmarg();
	i->result->type = label_a;
	i->result->val = nextinstructionlabel()+2;
	i->arg1 = NULL;
	i->arg2 = NULL;
	emit_instruction(i);
	
	/*****assign var true*******/
	j = malloc(sizeof(instruction));
	j->opcode = assign_v;
	j->arg1 = make_booloperand(t->arg1, 1); /* true */	
	j->result = make_operand(q->result);
	j->arg2 = NULL;
	emit_instruction(j);

	return ;
}

void generate_OR(quad* q)
{
	instruction* t;
	t=malloc(sizeof(instruction));
        q->taddress = nextinstructionlabel();
	
	t->opcode = jeq_v;

	t->arg1 = make_operand(q->arg1);
    	t->arg2 = make_booloperand(t->arg2, 1);

	t->result = new_vmarg();
        t->result->type = label_a;
        t->result->val = nextinstructionlabel() + 4;
        emit_instruction(t);
	
	
	t->arg1=make_operand(q->arg2);
	t->result->val = nextinstructionlabel() + 3;
        emit_instruction(t);

	t->opcode = assign_v;
		
	t->arg1 = make_booloperand(t->arg1, 0);

	t->arg2=reset_operand();

	t->result=make_operand(q->result);
	emit_instruction(t);

	t->opcode = jump_v;	
	t->arg1=reset_operand();
	t->arg2=reset_operand();
	
	
	t->result->type=label_a;
	t->result->val = nextinstructionlabel() + 2;
	emit_instruction(t);
	
	t->opcode = assign_v;
    	t->arg1 = make_booloperand(t->arg1, 1);

	t->arg2=reset_operand();

        t->result=make_operand(q->result);
        emit_instruction(t);
	
	return ;
}


void generate_AND(quad* q) {
	instruction* t;
	t=malloc(sizeof(instruction));
	
    q->taddress = nextinstructionlabel();

    t->opcode = jeq_v;

    t->arg1 = make_operand(q->arg1);
	t->arg2 = make_booloperand(t->arg2, 0);

    t->result = new_vmarg();
    t->result->type = label_a;
    t->result->val = nextinstructionlabel() + 4;
    emit_instruction(t);


    t->arg1 = make_operand(q->arg2);
    t->result->val = nextinstructionlabel() + 3;
    emit_instruction(t);

    t->opcode = assign_v;

	t->arg1 = make_booloperand(t->arg1, 1);
    t->arg2=NULL;
    t->result = make_operand(q->result);
    emit_instruction(t);

    t->opcode = jump_v;
	t->arg1=NULL;
    t->arg2=NULL;

    t->result->type=label_a;
    t->result->val = nextinstructionlabel() + 2;
    emit_instruction(t);

    t->opcode = assign_v;
    t->arg1 = make_booloperand(t->arg1, 0);
    t->arg2=NULL;

	t->result = make_operand(q->result);
    emit_instruction(t);

	return ;
}

void generate_PARAM(quad* q) {
	instruction* t;
	q->taddress = nextinstructionlabel();
	t = malloc(sizeof(instruction));
	assert(t != NULL);
	t->opcode = pusharg_v;
	t->result = make_operand(q->result);
	t->arg2 = NULL;
	t->arg1 = NULL;
	
	emit_instruction(t);
	return ;
}

void generate_CALL(quad* q) {
	instruction* t;
	t= malloc(sizeof(instruction));
	assert(t != NULL);
	q->taddress= nextinstructionlabel();
	t->opcode = call_v;
	t->arg1 = NULL;
	t->arg2 = NULL;
	t->result = make_operand(q->result);
	emit_instruction(t);
	return ;
}

void generate_GETRETVAL(quad* q) {	
	instruction* t;

	t = malloc(sizeof(instruction));
	assert(t != NULL);
        q->taddress= nextinstructionlabel();
	
	t->opcode = assign_v;
	t->result = make_operand(q->result);
	t->arg1 = new_vmarg();
	t->arg1 = make_retvaloperand(t->arg1);
	t->arg2 = NULL;
	
	emit_instruction(t);

	return ;
}

void generate_FUNCSTART(quad* q) {
	instruction *t;
	
	assert(q->result!=NULL);
	SymbolTableEntry *f = q->result->sym;	 	
	assert(f != NULL);
	
	t = malloc(sizeof(instruction));
	assert(t != NULL);
	
	f->taddress=nextinstructionlabel();		
	
	q->taddress= nextinstructionlabel();

//  @todo uncommend	
	// LocalSizeList *tmp = head_sizeList;
	
 //    while(strcmp(f.value.funcVal.name,tmp->name) != 0) {
 //    	tmp=tmp->next;
 //        if(tmp==NULL)
 //        	break;
 //    }	
 //    assert(tmp != NULL);
	// userfunctions_add(f->name,f->taddress,tmp->localSize);

	t->opcode=funcenter_v;

	t->result=make_operand(q->result);

	emit_instruction(t);
	push_func(f);
	return ;
}

void generate_RETURN(quad* q) {
	instruction *t;
	func* fsym;
	t=malloc(sizeof(instruction));
	q->taddress=nextinstructionlabel();
	/******* assign *******/
	t->opcode=assign_v;
	t->result = new_vmarg();
	t->result->type = retval_a;

	t->arg1=make_operand(q->arg1);
	t->arg2 = NULL;
	emit_instruction(t);
	
	fsym=top_func();
	append_list(fsym, nextinstructionlabel());
	/********* jump **********/
	t->opcode=jump_v;
	t->arg1=NULL;
	t->arg2=NULL;
	t->result->type=label_a;
	t->result->val = -1;
	emit_instruction(t);
	return ;
}

void generate_FUNCEND(quad* q) {
	instruction *t;
	func* fsym;
	t=malloc(sizeof(instruction));
	
	fsym =pop_func();
	if(fsym)
		back_patch_return(fsym->rl_head, nextinstructionlabel());

	q->taddress=nextinstructionlabel();
	t->opcode=funcexit_v;	

	t->result=make_operand(q->result);
	emit_instruction(t);
	
	return ;
}

void generate_UMINUS(quad* q) {
	instruction* t;
	
	t = malloc(sizeof(instruction));
	assert(t != NULL);
	
	t->opcode = mul_v;
	
	t->result = make_operand(q->result);
	
	t->arg1 = make_operand(q->arg2);
	
	t->arg2 = make_operand(newexpr_constnum_i(-1));

	emit_instruction(t);
	return ;
}

void generate_relational(vmopcode op, quad* q) {
	instruction* t = malloc(sizeof(instruction));
	assert(t != NULL);
	t->opcode = op;

	t->arg1 = make_operand(q->arg1);
	t->arg2 = make_operand(q->arg2);
	
	t->result = new_vmarg();
	assert(t->result != NULL);
	t->result->type = label_a;
	if(q->label < currprocessedquad())
		t->result->val = (quads + q->label)->taddress;
	else
		add_incomplete_jump(nextinstructionlabel(), q->label);
	q->taddress = nextinstructionlabel();
	emit_instruction(t);
	return ;
}

vmarg* make_booloperand(vmarg* arg, unsigned int tf) {
	arg = new_vmarg();
	arg->type = bool_a;
	arg->val = tf;
	return arg;
}

unsigned int currprocessedquad() {
	return processingQuad;
}


void emit_instruction(instruction* t) {
	instruction* new ;
	assert(t != NULL);
	new = malloc(sizeof(instruction));
	assert(new != NULL);
	
	if(currinstr == totalinstr)
		expand_instruction();

	new = instructions + currinstr++;  
	new->opcode = t->opcode;
	
	new->arg1 = new_vmarg();
	assert(new->arg1 != NULL);
	new->arg1 = t->arg1;
	
	new->arg2 = new_vmarg();
	assert(new->arg2 != NULL);
	new->arg2 = t->arg2;
	
	new->result = new_vmarg();
	assert(new->result != NULL);
	new->result = t->result;
	
	new->srcLine = t->srcLine;
	return ;
}

void expand_instruction() {
	assert(currinstr == totalinstr);
	instruction *p = malloc(NEW_SIZE_INSTRUCTION);
	if(instructions) {
		memcpy(p, instructions, CURR_SIZE_INSTRUCTION);
		if(instructions) {
			printf("make free the instruction table and maybe this goes to segmetation fault!!!\n");
			free(instructions);
		} else {
			fprintf(stderr, "instructions table is null in function expand\n");
			exit(-1);
		}
	}
	instructions = (instruction*) p;
	totalinstr =totalinstr + EXPAND_SIZE_INSTRUCTION;
	return;
}

void make_generate(void) {
	for(processingQuad = 0; processingQuad < currQuad; processingQuad++)
		(*generators_t[quads[processingQuad].op])(quads + processingQuad);

	patch_incomplete_jumps();
	return ;
}

/* Ektypwnei ton kwdika se morfi pou katalabainoume kai goustaroume */
void print_instructions_txt() {
	unsigned int currPrintInstr;
	size_t i;
	instruction* p; /* tmp instruction for travarse the table  */
	FILE* instr_fp = fopen("Instructions.txt", "w");
	assert(instr_fp != NULL);
	
	for(currPrintInstr = 0, p = instructions; currPrintInstr < currinstr; currPrintInstr++, p += 1)
	{
		fprintf(instr_fp, "%d: ", currPrintInstr);
		
		/*fprintf(instr_fp, "%d ", p->opcode);*/
		/***************OPCODE***************/
		switch(p->opcode)
		{
			case assign_v:
				fprintf(instr_fp, "%s\t", "assign");
				break;
			case add_v:
				fprintf(instr_fp, "%s\t", "add");
				break;
			case sub_v:
				fprintf(instr_fp, "%s\t", "sub");
				break;
			case mul_v:
				fprintf(instr_fp, "%s\t", "mul");
				break;
			case div_v:
				fprintf(instr_fp, "%s\t", "div");
				break;
			case mod_v:
				fprintf(instr_fp, "%s\t", "mod");
				break;
			case uminus_v:
				fprintf(instr_fp, "%s\t", "uminus");
				break;
			case and_v:
				fprintf(instr_fp, "%s\t", "and");
				break;
			case or:
				fprintf(instr_fp, "%s\t", "or");
				break; 
			case not_v:
				fprintf(instr_fp, "%s\t", "not");
				break;
			case jeq_v:
				fprintf(instr_fp, "%s\t", "jeq");
				break;
			case jne_v:
				fprintf(instr_fp, "%s\t", "jne");
				break;
			case jgt_v:
				fprintf(instr_fp, "%s\t", "jqt");
				break;
			case jlt_v:
				fprintf(instr_fp, "%s\t", "jlt");
				break;
			case jge_v:
				fprintf(instr_fp, "%s\t", "jge");
				break;
			case jle_v:
				fprintf(instr_fp, "%s\t", "jle");
				break;
			case call_v:
				fprintf(instr_fp, "%s\t", "call");
				break;
			case funcenter_v:
				fprintf(instr_fp, "%s\t", "funcenter");
				break;
			case funcexit_v:
				fprintf(instr_fp, "%s\t", "funcexit");
				break;
			case newtable_v:
				fprintf(instr_fp, "%s\t", "newtable");
				break;
			case tablegetelem_v:
				fprintf(instr_fp, "%s\t", "tablegetelem");
				break;
			case tablesetelem_v:
				fprintf(instr_fp, "%s\t", "tablesetelem");
				break;
			case pusharg_v:
				fprintf(instr_fp, "%s\t", "pusharg");
				break;
			case nop_v:
				fprintf(instr_fp, "%s\t", "nop");
				break;
			case jump_v:
				fprintf(instr_fp, "%s\t", "jump");
				break;
			default:
				fprintf(stderr, "Unknown instruction commant!!\n");
				assert(0);
				break;
		}
		/********RESULT*************/
		if(p->result)
		{
			switch(p->result->type)
			{
				case label_a:
					fprintf(instr_fp, "(res)label-%d-\t", p->result->val);
					break;
				case global_a:
					fprintf(instr_fp, "(res)global-%d-\t", p->result->val);
					break;
				case formal_a:
					fprintf(instr_fp, "(res)formal-%d-\t", p->result->val);
					break;
				case local_a:
					fprintf(instr_fp, "(res)local-%d-\t", p->result->val);
					break;
				case integer_a:
					fprintf(instr_fp, "(res)integer-%d-\t", p->result->val);
					break;
				case double_a:
					fprintf(instr_fp, "(res)double-%d-\t", p->result->val);
					break;
				case string_a:
					fprintf(instr_fp, "(res)string-%d-\t", p->result->val);
					break;
				case bool_a:
					fprintf(instr_fp, "(res)bool-%d-\t", p->result->val);
					break;
				case nil_a:
					fprintf(instr_fp, "(res)nil-%d-\t", p->result->val);
					break;
				case userfunc_a:
					fprintf(instr_fp, "(res)userfunc-%d-\t", p->result->val);
					break;
				case libfunc_a:
					fprintf(instr_fp, "(res)libfunc-%d-\t", p->result->val);
					break;
				case retval_a:
					fprintf(instr_fp, "(res)retval-%d-\t", p->result->val);
					break;
				default:
					fprintf(stderr, "Unknown instruction result!!\n");
					assert(0);
					break;
			}
		}/*endif*/
		/********arg1*************/
		if(p->arg1)
		{
			switch(p->arg1->type)
			{
				case label_a:
					fprintf(instr_fp, "(arg1)label-%d-\t", p->arg1->val);
					break;
				case global_a:
					fprintf(instr_fp, "(arg1)global-%d-\t", p->arg1->val);
					break;
				case formal_a:
					fprintf(instr_fp, "(arg1)formal-%d-\t", p->arg1->val);
					break;
				case local_a:
					fprintf(instr_fp, "(arg1)local-%d-\t", p->arg1->val);
					break;
				case integer_a:
					fprintf(instr_fp, "(arg1)integer-%d-\t", p->arg1->val);
					break;
				case double_a:
					fprintf(instr_fp, "(arg1)double-%d-\t", p->arg1->val);
					break;
				case string_a:
					fprintf(instr_fp, "(arg1)string-%d-\t", p->arg1->val);
					break;
				case bool_a:
					fprintf(instr_fp, "(arg1)bool-%d-\t", p->arg1->val);
					break;
				case nil_a:
					fprintf(instr_fp, "(arg1)nil-%d-\t", p->arg1->val);
					break;
				case userfunc_a:
					fprintf(instr_fp, "(arg1)userfunc-%d-\t", p->arg1->val);
					break;
				case libfunc_a:
					fprintf(instr_fp, "(arg1)libfunc-%d-\t", p->arg1->val);
					break;
				case retval_a:
					fprintf(instr_fp, "(arg1)retval-%d-\t", p->arg1->val);
					break;
				default:
					fprintf(stderr, "(arg1)Unknown instruction arg1!!\n");
					assert(0);
					break;
			}
			}/*endif*/
			/********arg2*************/
			if(p->arg2)
			{
			switch(p->arg2->type)
			{
				case label_a:
					fprintf(instr_fp, "(arg2)label-%d-\t", p->arg2->val);
					break;
				case global_a:
					fprintf(instr_fp, "(arg2)global-%d-\t", p->arg2->val);
					break;
				case formal_a:
					fprintf(instr_fp, "(arg2)formal-%d-\t", p->arg2->val);
					break;
				case local_a:
					fprintf(instr_fp, "(arg2)local-%d-\t", p->arg2->val);
					break;
				case integer_a:
					fprintf(instr_fp, "(arg2)integer-%d-\t", p->arg2->val);
					break;
				case double_a:
					fprintf(instr_fp, "(arg2)double-%d-\t", p->arg2->val);
					break;
				case string_a:
					fprintf(instr_fp, "(arg2)string-%d-\t", p->arg2->val);
					break;
				case bool_a:
					fprintf(instr_fp, "(arg2)bool-%d-\t", p->arg2->val);
					break;
				case nil_a:
					fprintf(instr_fp, "(arg2)nil-%d-\t", p->arg2->val);
					break;
				case userfunc_a:
					fprintf(instr_fp, "(arg2)userfunc-%d-\t", p->arg2->val);
					break;
				case libfunc_a:
					fprintf(instr_fp, "(arg2)libfunc-%d-\t", p->arg2->val);
					break;
				case retval_a:
					fprintf(instr_fp, "(arg2)retval-%d-\t", p->arg2->val);
					break;
				default:
					fprintf(stderr, "(arg2)Unknown instruction arg2!!\n");
					assert(0);
					break;
			}
		}/*endif*/
		fprintf(instr_fp, "%c", '\n');
	}
	
	fprintf(instr_fp, "Integer table: %d\n", currIntConsts);
	for(i = 0; i < currIntConsts; i++)
	{	
		fprintf(instr_fp, "%d ", consts_getint(i));
		if(i % 6 == 0 && i != 0) 
		{
			fprintf(instr_fp, "\n");
		}
	}
	fprintf(instr_fp, "\n");
	fprintf(instr_fp, "Double table: %d\n", currDoubleConsts);
	for(i = 0; i < currDoubleConsts; i++)
	{	
		fprintf(instr_fp, "%lf ", consts_getdouble(i));
		if(i % 6 == 0 && i != 0) 
		{
			fprintf(instr_fp, "\n");
		}
	}
	fprintf(instr_fp, "\n");
	fprintf(instr_fp, "String table: %d\n", currStringConsts);
	for(i = 0; i < currStringConsts; i++)
	{	
		fprintf(instr_fp, "%s ", consts_getstring(i));
		if(i % 6 == 0 && i != 0) 
		{
			fprintf(instr_fp, "\n");
		}
	}
	fprintf(instr_fp, "\n");
	fprintf(instr_fp, "User Function table: %d\n", currUserFuncs);
	for(i = 0; i < currUserFuncs; i++)
	{	
		userfunc_p* f = getuserfunction(i);
		fprintf(instr_fp, "%s ", f->id);
		if(i % 6 == 0 && i != 0) 
		{
			fprintf(instr_fp, "\n");
		}
	}
	fprintf(instr_fp, "\n");
	fprintf(instr_fp, "Library Function table: %d\n", currNamedLibfuncs);
	for(i = 0; i < currNamedLibfuncs; i++)
	{	
		fprintf(instr_fp, "%s ", libfuncs_getused(i));
		if(i % 6 == 0 && i != 0) 
		{
			fprintf(instr_fp, "\n");
		}
	}
	return ;
}

void print_binary_code()
{
	unsigned int currPrintInstr;
	instruction* p; /* tmp instruction for travarse the table  */
	FILE* bin = NULL;
	int r;
	size_t i;
	int magic = make_magic_number(); 
	bin = fopen("BinaryCode.abc", "wb");
	if(!bin) {
		fprintf(stderr, "Program can not write in binaryCode\n");
		assert(0);
	}

	/*write magic numbe: 2611*/
	fwrite(&magic, sizeof(int), 1, bin);

	fwrite(&currinstr, sizeof(unsigned int), 1, bin); //print the number of instructions	
	for(currPrintInstr = 0, p = instructions; currPrintInstr < currinstr; currPrintInstr++, p += 1)	{
		/****Print OPCODE****/
		r = fwrite(&(p->opcode),sizeof(int),1,bin);
		hitError(r);
		
		/****Print result***/
		if (p->result)
		{
			r = fwrite(&(p->result->type),sizeof(int),1,bin); //type
			hitError(r);
			
			r = fwrite(&(p->result->val),sizeof(int),1,bin); //val
			hitError(r);
		}
		/***Print arg1****/
		if(p->arg1)
		{
			r = fwrite(&(p->arg1->type),sizeof(int),1,bin); //type
			hitError(r);
		
			r = fwrite(&(p->arg1->val),sizeof(int),1,bin); //val
			hitError(r);
		}
		/***Print arg2****/
		if(p->arg2)
		{
			r = fwrite(&(p->arg2->type),sizeof(int),1,bin); //type
			hitError(r);
		
			r = fwrite(&(p->arg2->val),sizeof(int),1,bin); //val
			hitError(r);
		}
	}
	/*print int table: */
	r = fwrite(&currIntConsts, sizeof(unsigned int), 1, bin);
	hitError(r);
	
	for(i = 0; i < currIntConsts; i++)
	{
		int x = consts_getint(i);
		r = fwrite(&x, sizeof(int), 1, bin);
		hitError(r);
	}
	
	/* print double table: */
	fwrite(&currDoubleConsts, sizeof(unsigned int), 1, bin);
	hitError(r);
	
	for(i = 0; i < currDoubleConsts; i++)
	{
		double d = consts_getdouble(i);
		r = fwrite(&d, sizeof(int), 1, bin);
		hitError(r);
	}
	/* print string table: */
	r = fwrite(&currStringConsts, sizeof(unsigned int), 1, bin);
	hitError(r);
	
	for(i = 0; i < currStringConsts; i++)
	{
		char* s = consts_getstring(i);
		r = fwrite(&s, sizeof(int), 1, bin);
		hitError(r);
	}
	/* print user function table: */
	r = fwrite(&currUserFuncs, sizeof(int), 1, bin);
	hitError(r);
	for(i = 0; i < currUserFuncs; i++)
	{	
		userfunc_p* f = getuserfunction(i);
		r = fwrite(&(f->id), sizeof(int), 1, bin);
		hitError(r);
	}
	r = fwrite(&currNamedLibfuncs, sizeof(int), 1, bin);
	hitError(r);
	fprintf(stdout, "Library Function table: %d\n", currNamedLibfuncs);
	for(i = 0; i < currNamedLibfuncs; i++)
	{	
		fprintf(stdout, "%s ", libfuncs_getused(i));
		if(i % 6 == 0 && i != 0) {
			fprintf(stdout, "\n");
		}
	}
	if(bin) 
		fclose(bin);
}

void hitError(int r) {
	if (r!=1) {
		fprintf(stderr, "Error in binaryCode File\n");
		assert(0);
	}
}

int make_magic_number() {
	int magic = 0;
	int i, j;
	char* p[] = {"papoulas", "kirikoss", "giorgose"};
	for(i = 0; i < 3; i++)
		for(j = 0; j < 8; j++)
			magic += p[i][j];
			
	return magic;
}

void push_func(SymbolTableEntry* f) {
	func* new = malloc(sizeof(func));
	assert(new != NULL);
	new->sym = f;
	new->rl_head = NULL;
	
	new->next = f_head;
	f_head = new;
}

func* pop_func() {
	func* del;
	del = f_head;
	f_head = f_head->next;
	return del;
}

func* top_func() {
	return f_head;
}

void append_list(func* fsym, unsigned int label) {
	returnlist* new;
	new = malloc(sizeof(returnlist));
	assert(new != NULL);
	new->label = label;
	//@todo uncommend
	//new->next = fsym->rl_head;
	//fsym->rl_head = new;
}

void back_patch_return(returnlist* list, unsigned int label) {
	returnlist* tmp;
	for(tmp = list; tmp != NULL; tmp = tmp->next)
		(instructions + tmp->label)->result->val = label;
}

