/* escape.c */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "util.h"
#include "errormsg.h"
#include "symbol.h"
#include "absyn.h"
#include "types.h"
#include "env.h"
#include "escape.h"
#include "absyn.h"
#include "helper.h"

typedef struct escapeEntry_ *escapeEntry;
struct escapeEntry_ {
	int depth;
    bool* escape;
};

static escapeEntry EscapeEntry(int d, bool* e){
	escapeEntry entry = checked_malloc(sizeof(*entry));
	entry->depth = d;
	entry->escape = e;
	return entry;
}

static void traverseExp(S_table table, int depth, A_exp a);
static void traverseDec(S_table table, int depth, A_dec d);
static void traverseVar(S_table table, int depth, A_var v);

static void 
traverseExp(S_table table, int depth, A_exp a){
	switch(a->kind){
		case A_varExp: {
			A_var var = a->u.var;
			return traverseVar(table, depth, var);
		}
		case A_nilExp: 
		case A_intExp: 
		case A_stringExp: 
			return;
		case A_callExp:{
			A_expList exps = get_callexp_args(a);
			while(exps){
				A_exp param = exps->head;
				traverseExp(table, depth, param);
				exps = exps->tail;
			}
			return;			
		}
	    case A_opExp:{ 
			A_exp left = get_opexp_left(a); 
			traverseExp(table, depth, left);
			A_exp right = get_opexp_right(a);
			traverseExp(table, depth, right);
			return;
		}
		case A_recordExp: {
			A_efieldList fields = get_recordexp_fields(a);
			while(fields){
				traverseExp(table, depth, fields->head->exp);
				fields=fields->tail;
			}
			return;
		}
		case A_seqExp:{
			A_expList seq = get_seqexp_seq(a);
			while(seq){
				A_exp ex = seq->head;
				traverseExp(table, depth, ex);
				seq=seq->tail;
			}
			return;
		}
		case A_assignExp:{
			A_var var = get_assexp_var(a); 
			traverseVar(table, depth, var);
			A_exp ex = get_assexp_exp(a);
			traverseExp(table, depth, ex);
			return ;
		} 
		case A_ifExp:{
			A_exp test = get_ifexp_test(a); 
			traverseExp(table, depth, test);
			A_exp then = get_ifexp_then(a);
			traverseExp(table, depth, then);
			A_exp elsee = get_ifexp_else(a);
			traverseExp(table, depth, elsee);
			return;
		}
	    case A_whileExp:{
			A_exp test = get_whileexp_test(a);
			traverseExp(table, depth, test);
			A_exp body = get_whileexp_body(a);
			traverseExp(table, depth, body);
			return;

		}
		case A_forExp:{
			traverseExp(table, depth, get_forexp_lo(a));
			traverseExp(table, depth, get_forexp_hi(a));

			S_symbol var = get_forexp_var(a); 
			A_exp body = get_forexp_body(a);
			S_beginScope(table);
			a->u.forr.escape = FALSE;
			S_enter(table, var, EscapeEntry(depth,&(a->u.forr.escape)));
			traverseExp(table, depth, body);
			S_endScope(table);
			return;
		}
		case A_breakExp: {
			return;
		}
		case A_letExp:{
			A_exp body = get_letexp_body(a);

			S_beginScope(table); 
			A_decList decs=get_letexp_decs(a);
			while(decs){
				A_dec dec = decs->head;
				traverseDec(table, depth, dec);
				decs=decs->tail;
			}
			traverseExp(table, depth, body);
			S_endScope(table);
			return;
		}
		case A_arrayExp:{
			A_exp size = get_arrayexp_size(a);
			traverseExp(table, depth, size);
			A_exp init = get_arrayexp_init(a);
			traverseExp(table, depth, init);
			return;
		}
		assert(0);
	}
}

static void 
traverseDec(S_table table, int depth, A_dec d){
	switch(d->kind){
		case A_typeDec:
			return;
		case A_functionDec:{		
			for(A_fundecList funcs=get_funcdec_list(d); funcs; funcs=funcs->tail){
				A_fundec func = funcs->head;				
				
				S_beginScope(table);
				A_fieldList params = func->params; 
				A_fieldList ls=params;
		 		while(ls){
					A_field param = ls->head;
					S_enter(table, param->name, EscapeEntry(depth+1, &param->escape));
					param->escape = FALSE;
					ls=ls->tail;
				 }
				A_exp body = func->body;
				traverseExp(table, depth+1, body);
				S_endScope(table);
			}
			return;
		}		
		case A_varDec:{
			S_symbol var = get_vardec_var(d);
			A_exp init = get_vardec_init(d);
			d->u.var.escape = FALSE;
			S_enter(table, var, EscapeEntry(depth, &d->u.var.escape));			
			traverseExp(table, depth, init);
			return;
		}
	}
}

static void 
traverseVar(S_table table, int depth, A_var v){
	switch(v->kind){
		case A_simpleVar:{
			S_symbol simple = get_simplevar_sym(v);
			escapeEntry esc = S_look(table, simple);
			if(esc && depth > esc->depth){
				*esc->escape = TRUE;
			}
			return;
		}
		case A_fieldVar:{
			A_var var = get_fieldvar_var(v); 			
			return traverseVar(table, depth, var);
		}
		case A_subscriptVar:{
			A_var var = get_subvar_var(v);
			traverseVar(table, depth, var);
			A_exp ex = get_subvar_exp(v);
			traverseExp(table, depth, ex);
			return;
		}
	}
}

void Esc_findEscape(A_exp exp){
	S_table table = S_empty();
	traverseExp(table, 0, exp);
}
