#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "util.h"
#include "errormsg.h"
#include "symbol.h"
#include "absyn.h"
#include "types.h"
#include "helper.h"
#include "env.h"
#include "semant.h"

/*Lab4: Your implementation of lab4*/

typedef void* Tr_exp;
struct expty 
{
	Tr_exp exp; 
	Ty_ty ty;
};

//In Lab4, the first argument exp should always be **NULL**.
struct expty expTy(Tr_exp exp, Ty_ty ty)
{
	struct expty e;

	e.exp = exp;
	e.ty = ty;

	return e;
}

/* my code */
S_symbol syms[1000];
int s_pos = 0;

void syms_reset()
{
	s_pos = 0;
}

int syms_push(S_symbol s)
{
	int i;
	for (i=0;i<s_pos;i++){
		if(syms[i]==s){
			return 0;
		}
	}
	syms[s_pos] = s;
	s_pos++;
	return 1;
}

Ty_ty actrulyTy(Ty_ty t)
{
    if(t==NULL){
		return NULL;
	}
	while(t!=NULL && t->kind==Ty_name){
		t = t->u.name.ty;
	}
	return t;
}

int isTyequTy(const Ty_ty s1 , const Ty_ty s2)
{
	assert(s1&&s2);
    Ty_ty tmp1 = actrulyTy(s1) ;
    Ty_ty tmp2 = actrulyTy(s2) ;
	if (tmp1==tmp2){
		return 1;
	}else{
		if ((tmp1->kind==Ty_record&&tmp2->kind==Ty_nil)||(tmp1->kind==Ty_nil&&tmp2->kind==Ty_record)){
			return 1;
		}else{
			return 0;
		}
	}
}

struct expty transVar(S_table venv, S_table tenv, A_var v)
{
	switch(v->kind){
		case A_simpleVar:{
			E_enventry tmp = (E_enventry)S_look(venv,v->u.simple);
			if(tmp!=NULL && tmp->kind==E_varEntry){
				return expTy(NULL,actrulyTy(tmp->u.var.ty));
			}
			EM_error(v->pos,"undefined variable %s\n",S_name(v->u.simple));
			return expTy(NULL,Ty_Int());
		}
		case A_fieldVar:{
			EM_error(v->pos,"in a fv");
			// EM_error(v->pos,"ufvar:%d %s",v->u.field.var->kind,S_name(v->u.field.sym));
			struct expty tmpty = transVar(venv,tenv,v->u.field.var);
			if (tmpty.ty->kind!=Ty_record){
				EM_error(v->pos,"not a record type");
				return expTy(NULL,Ty_Int());
			}
			// EM_error(v->pos,"%d....",tmpty.ty->kind);
			Ty_fieldList flist = (tmpty.ty)->u.record;
			if(!flist){
				EM_error(v->pos,"flist null");
			}
			while(flist){
				// EM_error(v->pos,"info:%s %s",S_name(flist->head->name),S_name(v->u.field.sym));
				if(flist->head->name==v->u.field.sym){
					// EM_error(v->pos,"last info:%s:%d",S_name(flist->head->name),flist->head->ty->kind);
					return expTy(NULL,actrulyTy(flist->head->ty));
				}
				flist = flist->tail;
			}
			EM_error(v->pos,"field %s doesn't exist",S_name(v->u.field.sym));
			return expTy(NULL,Ty_Int());
		}
		case A_subscriptVar:{
			struct expty tv = transVar(venv,tenv,v->u.subscript.var);
			if(tv.ty->kind!=Ty_array){
				EM_error(v->pos,"array type required");
			}
			struct expty te = transExp(venv,tenv,v->u.subscript.exp);
			if (te.ty->kind!=Ty_int){
				assert(0);
			}
			return expTy(NULL,actrulyTy(te.ty->u.array));
		}
	}
	assert(0);
}

struct expty transExp(S_table venv, S_table tenv, A_exp a)
{
	assert(a);
	switch(a->kind){
		case A_varExp:
			return transVar(venv,tenv,a->u.var);
		case A_nilExp:
			return expTy(NULL,Ty_Nil());
		case A_intExp:
			return expTy(NULL,Ty_Int());
		case A_stringExp:
			return expTy(NULL,Ty_String());
		case A_callExp:{
			E_enventry tmp = (E_enventry)S_look(venv,a->u.call.func);
			if (tmp==NULL){
				EM_error(a->pos,"undefined function %s\n",S_name(a->u.call.func));
				return expTy(NULL,Ty_Int());
			}
			Ty_tyList tylist = tmp->u.fun.formals;
			A_expList explist = a->u.call.args;
			while (tylist!=NULL && explist!=NULL){
				struct expty exptyp = transExp(venv,tenv,explist->head);
				// if (exptyp.ty->kind==Ty_nil){
				// 	continue;
				// }
				// if (!isTyequTy(tylist->head,exptyp.ty)){
				// 	assert(0);
				// }
				if(!isTyequTy(tylist->head,exptyp.ty)){
					EM_error(a->pos,"para type mismatch");
				}
				tylist = tylist->tail;
				explist = explist->tail;
			}
			if (tylist!=NULL){
				EM_error(a->pos,"para type mismatch");
			}
			if (explist!=NULL){
				EM_error(a->pos,"too many params in function %s",S_name(a->u.call.func));
			}
			return expTy(NULL,actrulyTy(tmp->u.fun.result));
		}
		case A_opExp:{
			struct expty left = transExp(venv,tenv,a->u.op.left);
			struct expty right = transExp(venv,tenv,a->u.op.right);
			switch(a->u.op.oper){
				case A_plusOp:
				case A_minusOp:
				case A_timesOp:
				case A_divideOp:{
					if (left.ty->kind!=Ty_int)
						EM_error(a->u.op.left->pos,"integer required");
					if (right.ty->kind!=Ty_int)
						EM_error(a->u.op.right->pos,"integer required");
					return expTy(NULL,Ty_Int());
				}
				case A_ltOp:
				case A_leOp:
				case A_gtOp:
				case A_geOp:{
					if (left.ty->kind!=Ty_int)
						EM_error(a->u.op.left,"same type required\n");
					if (right.ty->kind!=Ty_int)
						EM_error(a->u.op.right,"same type required\n");
					return expTy(NULL,Ty_Int());
				}
				case A_eqOp:
				case A_neqOp:{
					if(left.ty->kind==Ty_void)
						EM_error(a->u.op.left->pos,"exp has no value");
					if(right.ty->kind==Ty_void)
						EM_error(a->u.op.right->pos,"exp has no value");
					if(!isTyequTy(left.ty,right.ty))
						EM_error(a->u.op.right->pos,"same type required");
					return expTy(NULL,Ty_Int());
					// if (left.ty->kind==Ty_int && right.ty->kind==Ty_int){
					// 	return expTy(NULL,Ty_Int());
					// }
					// if (left.ty->kind==right.ty->kind){
					// 	if (left.ty->kind==Ty_record||right.ty->kind==Ty_array){
					// 		if (left.ty==right.ty){
					// 			return expTy(NULL,Ty_Int());
					// 		}
					// 	}
					// }
				}
			}
			assert(0);
		}
		case A_recordExp:{
			Ty_ty tmpty = (Ty_ty)S_look(tenv,a->u.record.typ);
			tmpty = actrulyTy(tmpty);
			if (tmpty==NULL){
				EM_error(a->pos,"undefined type rectype");
			}
			if (tmpty->kind!=Ty_record){
				assert(0);
			}
			A_efieldList tef = a->u.record.fields;
			Ty_fieldList tfl = tmpty->u.record;
			while(tef && tfl){
				// EM_error(a->pos,"--%s %s",S_name(tef->tail->head->name),S_name(tfl->tail->head->name));
				if (tef->head->name != tfl->head->name){
					EM_error(a->pos,"same type required\n");
					return expTy(NULL,Ty_Record(NULL));
				}
				if (!isTyequTy(transExp(venv,tenv,tef->head->exp).ty,tfl->head->ty)){
					assert(0);
				}
				tef = tef->tail;
				tfl = tfl->tail;
			}
			if (tfl!=NULL || tef!=NULL){
				assert(0);
			}
			return expTy(NULL,tmpty);
		}
		case A_seqExp:{
			A_expList explist = a->u.seq;
			if (explist){
				while(explist->tail){
					EM_error(a->pos,"sig2:%d",explist->head->kind);
					transExp(venv,tenv,explist->head);
					explist = explist->tail;
				}
			}
			else{
				return expTy(NULL,Ty_Void());
			}
			EM_error(a->pos,"sig22:%d",explist->head->kind);
			return transExp(venv,tenv,explist->head);
		}
		case A_assignExp:{
			EM_error(a->pos,"ass kind:%d",a->u.assign.var->kind);
			struct expty tv = transVar(venv,tenv,a->u.assign.var);
			struct expty te = transExp(venv,tenv,a->u.assign.exp);
			EM_error(a->pos,"bet:%d %d",tv.ty->kind,te.ty->kind);
			if (!isTyequTy(tv.ty,te.ty)){
				EM_error(a->pos,"unmatched assign exp %d %d",tv.ty->kind,te.ty->kind);
			}
			return expTy(NULL,Ty_Void());
		}
		case A_ifExp:{
			struct expty test = transExp(venv,tenv,a->u.iff.test);
			struct expty then = transExp(venv,tenv,a->u.iff.then);
			if (test.ty->kind!=Ty_int){
				EM_error(a->pos,"if-exp was not an integer");
			}
			if(a->u.iff.elsee->kind==Ty_nil){
				if(then.ty->kind!=Ty_void){
					EM_error(a->pos,"if-then exp's body must produce no value");
				}
				return expTy(NULL,Ty_Void());
			}else{
				struct expty e = transExp(venv,tenv,a->u.iff.elsee);
				if(!isTyequTy(e.ty,then.ty)){
					EM_error(a->pos,"then exp and else exp type mismatch");
				}
				return expTy(NULL,then.ty);
			}
			return expTy(NULL,Ty_Void());
		}
		case A_whileExp:{
			//lack of loop counter
			struct expty test = transExp(venv,tenv,a->u.whilee.test);
			if (test.ty->kind != Ty_int){
				assert(0);
			}
			struct expty body = transExp(venv,tenv,a->u.whilee.body);
			if (body.ty->kind != Ty_void){
				EM_error(a->pos,"while body must produce no value\n");
			}
			return expTy(NULL,Ty_Void());
		}
		case A_forExp:{
			//lack of loop counter
			// EM_error(a->pos,"errhits");
			EM_error(a->pos,"test11:%d  %d",a->u.forr.lo->kind,a->u.forr.hi->kind);
			struct expty lo = transExp(venv,tenv,a->u.forr.lo);
			struct expty hi = transExp(venv,tenv,a->u.forr.hi);
			S_beginScope(venv);
			S_beginScope(tenv);
			S_enter(venv,a->u.forr.var,E_VarEntry(Ty_Int()));
			struct expty tmpbody = transExp(venv,tenv, a->u.forr.body);
			S_endScope(venv);
			S_endScope(tenv);
			EM_error(a->pos,"test:%d  %d",lo.ty->kind,hi.ty->kind);
			if (lo.ty->kind!=Ty_int){
				EM_error(a->pos,"for exp's range type is not integer\n");
				EM_error(a->pos,"loop variable can't be assigned\n");
			}
			if (hi.ty->kind!=Ty_int){
				EM_error(a->pos,"for exp's range type is not integer\n");
				EM_error(a->pos,"loop variable can't be assigned\n");
			}
			if (tmpbody.ty->kind!=Ty_void){
				assert(0);
			}
			return expTy(NULL,Ty_Void());
		}
		case A_breakExp:{
			//judge loop counter
			return expTy(NULL,Ty_Void());
		}
		case A_letExp:{
			S_beginScope(venv);
			S_beginScope(tenv);
			A_decList declist = a->u.let.decs;
			while (declist != NULL){
				transDec(venv,tenv,declist->head);
				declist = declist->tail;
			}
			struct expty tmp;
			if (a->u.let.body){
				EM_error(a->pos,"sig:%d",a->u.let.body->kind);
				tmp = transExp(venv,tenv,a->u.let.body);
			}else{
				tmp = expTy(NULL,Ty_Void());
			}
			S_endScope(venv);
			S_endScope(tenv);
			return tmp;
		}
		case A_arrayExp:{
			Ty_ty ty = (Ty_ty)S_look(tenv,a->u.array.typ);
			ty = actrulyTy(ty);
			if (ty==NULL || ty->kind!=Ty_array){
				assert(0);
			}
			struct expty tynum = transExp(venv,tenv,a->u.array.size);
			if (tynum.ty->kind != Ty_int){
				assert(0);
			}
			struct expty tyinit = transExp(venv,tenv,a->u.array.init);
			if (tyinit.ty!=ty->u.array){
				EM_error(a->pos,"type mismatch");
			}
			return expTy(NULL,ty);
		}
	}
	assert(0);
}

void transDec(S_table venv, S_table tenv, A_dec d)
{
	switch(d->kind){
		case A_functionDec:{
			A_fundecList tmpfun = d->u.function;
			// S_symbol fs[1000];
			// int fs_pos=0;
			syms_reset();
			while(tmpfun){
				A_fieldList tfl = tmpfun->head->params;
				Ty_tyList tylist = NULL;
				while(tfl){
					Ty_ty ty = (Ty_ty)S_look(tenv,tfl->head->typ);
					tylist = Ty_TyList(ty,tylist);
					tfl = tfl->tail;
				}
				if(!syms_push(tmpfun->head->name)){
					EM_error(d->pos,"two functions have the same name");
				}
				// if(tmpfun->head->name==S_Symbol("int") || tmpfun->head->name==S_Symbol("string")){
				// 	assert(0);
				// }
				// for(int i=0;i<fs_pos;i++){
				// 	EM_error(d->pos,"func info:%s %s",S_name(tmpfun->head->name),S_name(fs[i]));
				// 	if(S_name(tmpfun->head->name)==S_name(fs[i])){
				// 		EM_error(d->pos,"two functions have the same name");
				// 	}else{
				// 		fs[i] = tmpfun->head->name;
				// 		fs_pos++;
				// 	}
				// }
				Ty_ty re = NULL;
				if (tmpfun->head->result){
					re = S_look(tenv,tmpfun->head->result);
					if (!re){
						EM_error(d->pos,"xxxxx");
					}
				}else{
					re = Ty_Void();
				}
				S_enter(venv,tmpfun->head->name,E_FunEntry(tylist,re));
				tmpfun = tmpfun->tail;
			}
			tmpfun = d->u.function;
			while(tmpfun){
				S_beginScope(venv);
				A_fieldList tfl = tmpfun->head->params;
				while(tfl){
					Ty_ty ty = (Ty_ty)S_look(tenv,tfl->head->typ);
					if(tfl->head->name==S_Symbol("int") || tfl->head->name==S_Symbol("string")){
						assert(0);
					}
					S_enter(venv,tfl->head->name,E_VarEntry(ty));
					tfl = tfl->tail;
				}
				E_enventry ent = S_look(venv,tmpfun->head->name);
				struct expty exp = transExp(venv,tenv,tmpfun->head->body);
				// EM_error(d->pos,"pos33:%d %d",ent->u.fun.result->kind,exp.ty->kind);
				if (ent->u.fun.result->kind == Ty_void && exp.ty->kind != Ty_void)
					EM_error(tmpfun->head->pos, "procedure returns value\n");
				else if (!isTyequTy(ent->u.fun.result, exp.ty))
					EM_error(tmpfun->head->pos, "body result type mismatch");
				S_endScope(venv);
				tmpfun = tmpfun->tail;
			}
			return;
		}
		case A_typeDec:{
			A_nametyList namelist = d->u.type;
			syms_reset();
			while(namelist){
				if (!syms_push(namelist->head->name)){
					EM_error(d->pos,"two types have the same name\n");
					return;
				}
				EM_error(d->pos,"ty create:%s",S_name(namelist->head->name));
				Ty_ty tmp = Ty_Name(namelist->head->name,NULL);
				S_enter(tenv,namelist->head->name,tmp);
				namelist = namelist->tail;
			}
			
			syms_reset();
			namelist = d->u.type;
			while(namelist){
				if (!syms_push(namelist->head->name)){
					continue;
				}
				Ty_ty tmp = (Ty_ty)S_look(tenv,namelist->head->name);
				tmp->u.name.ty = transTy(tenv,namelist->head->ty);
				EM_error(d->pos,"%s",S_name(tmp->u.name.sym));
				namelist = namelist->tail;
			}
			// check recursive definition
			syms_reset();
			namelist = d->u.type;
			while(namelist){
				Ty_ty tmp = (Ty_ty)S_look(tenv,namelist->head->name);
				syms_reset();
				tmp = tmp->u.name.ty;
				while(tmp&&tmp->kind==Ty_name){
					if(!syms_push(tmp->u.name.sym)){
						EM_error(d->pos,"illegal type cycle\n");
						tmp->u.name.ty = Ty_Int();
						return;
					}
					tmp = tmp->u.name.ty;
					tmp = tmp->u.name.ty;
				}
				namelist = namelist->tail;
			}
			
			return;
		}
		case A_varDec:{
			struct expty e = transExp(venv,tenv,d->u.var.init);
			// if(d->u.var.init==NULL){
			// 	EM_error(d->pos,"u var init null err");
			// }else{
			// 	EM_error(d->pos,"init type:%s",S_name(d->u.var.init->u.record.fields->head->name));
			// 	EM_error(d->pos,"addition info:%d %d",d->u.var.init->u.record.fields->head->exp->kind,e.ty->kind);
			// }
			
			if(d->u.var.typ){
				Ty_ty t = S_look(tenv,d->u.var.typ);
				if(!t){
					EM_error(d->pos,"undefined type");
				}else{
					if(!isTyequTy(t,e.ty)){
						EM_error(d->pos,"var init type mismatch");
					}
					// EM_error(d->pos,"senter");
					S_enter(venv,d->u.var.var,E_VarEntry(t));
					break;
				}
			}
			if(e.ty==Ty_Void()){
				EM_error(d->pos,"init with no value");
			}else if(e.ty==Ty_Nil()){
				EM_error(d->pos,"init should not be nil without type specified");
			}
			// EM_error(d->pos,"s enter ret %s",S_name(d->u.var.var));
			// if(!e.ty->u.record){
			// 	EM_error(d->pos,"u record null error");
			// }else{
			// 	EM_error(d->pos,"u record not null");
			// }
			S_enter(venv,d->u.var.var,E_VarEntry(e.ty));
			return;
		}
	}
	assert(0);
}

Ty_fieldList transTF(S_table tenv,A_fieldList tfl,A_ty a){
	if (!tfl){
		return NULL;
	}
	Ty_ty tmp = (Ty_ty)S_look(tenv,tfl->head->typ);
	if(tmp==NULL){
		EM_error(a->pos,"undefined type %s\n",S_name(tfl->head->typ));
	}
	if(!syms_push(tfl->head->name)){
		assert(0);
	}
	return Ty_FieldList(Ty_Field(tfl->head->name,tmp),transTF(tenv,tfl->tail,a));
}

Ty_ty transTy (S_table tenv, A_ty a)
{
	switch(a->kind){
		case A_nameTy:{
			if (S_Symbol("int")==a->u.name){
				return Ty_Int();
			}
			if (S_Symbol("string")==a->u.name){
				return Ty_String();
			}
			Ty_ty tmp = (Ty_ty)S_look(tenv,a->u.name);
			if (tmp==NULL){
				assert(0);
			}
			return Ty_Name(a->u.name,tmp);
		}
		case A_recordTy:{
			syms_reset();
			A_fieldList tfl = a->u.record;
			// Ty_fieldList fdlist = NULL;
			// while(tfl){
			// 	Ty_ty tmp = (Ty_ty)S_look(tenv,tfl->head->typ);
			// 	if(tmp==NULL){
			// 		EM_error(a->pos,"undefined type %s\n",S_name(tfl->head->typ));
			// 	}
			// 	if(!syms_push(tfl->head->name)){
			// 		assert(0);
			// 	}
			// 	EM_error(a->pos,"typ:%s:%d",S_name(tfl->head->name),tmp->kind);
			// 	fdlist = Ty_FieldList(Ty_Field(tfl->head->name,tmp),fdlist);
			// 	tfl = tfl->tail;
			// }
			Ty_fieldList fdlist = transTF(tenv,tfl,a);
			EM_error(a->pos,"before return record");
			return Ty_Record(fdlist);
		}
		case A_arrayTy:{
			Ty_ty tmp = (Ty_ty)S_look(tenv,a->u.array);
			if(tmp==NULL){
				assert(0);
			}
			return Ty_Array(tmp);
		}
	}
	assert(0);
}

void SEM_transProg(A_exp exp)
{
	S_table tenv = E_base_tenv();
	S_table venv = E_base_venv();
	transExp(venv,tenv,exp);
}