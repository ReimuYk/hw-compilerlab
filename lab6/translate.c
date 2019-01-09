#include <stdio.h>
#include "util.h"
#include "table.h"
#include "symbol.h"
#include "absyn.h"
#include "temp.h"
#include "tree.h"
#include "frame.h"
#include "translate.h"

//LAB5: you can modify anything you want.

F_fragList funcfrags = NULL;
F_fragList strfrags = NULL;

/* Tr_expList*/

Tr_expList Tr_ExpList(Tr_exp head, Tr_expList tail){
	Tr_expList l = checked_malloc(sizeof(*l));

	l->head = head;
	l->tail = tail;
	return l;
}


static patchList PatchList(Temp_label *head, patchList tail)
{
	patchList list;

	list = (patchList)checked_malloc(sizeof(struct patchList_));
	list->head = head;
	list->tail = tail;
	return list;
}

void doPatch(patchList tList, Temp_label label)
{
	for(; tList; tList = tList->tail)
		*(tList->head) = label;
}

patchList joinPatch(patchList first, patchList second)
{
	if(!first) return second;
	for(; first->tail; first = first->tail);
	first->tail = second;
	return first;
}

// ex nx cx
static Tr_exp ex(T_exp exp) {
    Tr_exp tr_exp = checked_malloc(sizeof(*tr_exp));
    tr_exp->kind = Tr_ex;
    tr_exp->u.ex = exp;
    return tr_exp;
}

static Tr_exp nx(T_stm stm) {
    Tr_exp tr_exp = checked_malloc(sizeof(*tr_exp));
    tr_exp->kind = Tr_nx;
    tr_exp->u.nx = stm;
    return tr_exp;
}


static Tr_exp cx(struct Cx cx) {
    Tr_exp tr_exp = checked_malloc(sizeof(*tr_exp));
    tr_exp->kind = Tr_cx;
    tr_exp->u.cx = cx;
    return tr_exp;
}

// unEx unNx unCx
static T_exp unEx(Tr_exp e) {
    switch (e->kind) {
        case Tr_ex:
            return e->u.ex;
        case Tr_nx:
            return T_Eseq(e->u.nx, T_Const(0));
        case Tr_cx: {
            Temp_temp r = Temp_newtemp();
            Temp_label t = Temp_newlabel(), f = Temp_newlabel();
            doPatch(e->u.cx.trues, t);
            doPatch(e->u.cx.falses, f);
            return T_Eseq(T_Move(T_Temp(r), T_Const(1)),
                          T_Eseq(e->u.cx.stm,
                                 T_Eseq(T_Label(f),
                                        T_Eseq(T_Move(T_Temp(r), T_Const(0)),
                                               T_Eseq(T_Label(t), T_Temp(r))))));
        }
        default:
            assert(0);
    }
}

static T_stm unNx(Tr_exp e) {
    switch (e->kind) {
        case Tr_ex:
            return T_Exp(e->u.ex);
        case Tr_nx:
            return e->u.nx;
        case Tr_cx: {
            Temp_label label = Temp_newlabel();
            doPatch(e->u.cx.trues, label);
            doPatch(e->u.cx.falses, label);
            return T_Seq(e->u.cx.stm, T_Label(label));
        }
        default:
            assert(0);
    }
}
static struct Cx unCx(Tr_exp e){
	struct Cx cx;
	switch(e->kind){
		case Tr_ex:{
			T_exp ex = e->u.ex;
			T_stm s1 = T_Cjump(T_ne, ex, T_Const(0), NULL, NULL);
			cx.trues = PatchList(&(s1->u.CJUMP.true), NULL);
			cx.falses = PatchList(&(s1->u.CJUMP.false), NULL);
			cx.stm = s1;
			return cx;
		}
		case Tr_nx:{
            assert(0);
        }
		case Tr_cx:
			return e->u.cx;
	}
}

Tr_level Tr_outermost(void){
	Tr_level l = checked_malloc(sizeof(*l));

	Temp_label lab = Temp_namedlabel("tigermain");
	l->frame = F_newFrame(lab, NULL);
	l->parent = NULL;
	return l;
}

Tr_level Tr_newLevel(Tr_level parent, Temp_label name, U_boolList formals){
	Tr_level l = checked_malloc(sizeof(*l));

	U_boolList newl = U_BoolList(1, formals); // 1 for static link
	l->frame = F_newFrame(name, newl);
	l->parent = parent;
	return l;
}

Tr_access Tr_allocLocal(Tr_level level, bool escape){
	Tr_access ac = checked_malloc(sizeof(*ac));

	ac->access = F_allocLocal(level->frame, escape);
	ac->level = level;

    return ac;
}

Tr_accessList Tr_AccessList(Tr_access head, Tr_accessList tail){
	Tr_accessList list = checked_malloc(sizeof(*list));

	list->head = head;
	list->tail = tail;
	return list;
}

Tr_accessList makeFormalsT(F_accessList fl, Tr_level level){
	Tr_access ac = checked_malloc(sizeof(*ac));

	ac->level = level;
	ac->access = fl->head;

	if(fl->tail){
		return Tr_AccessList(ac, makeFormalsT(fl->tail, level));
	}
	else{
		return Tr_AccessList(ac, NULL);
	}
}

Tr_accessList Tr_formals(Tr_level level){
	F_frame f = level->frame;
	F_accessList fl = F_formals(f);
	return makeFormalsT(fl, level);
}

Tr_exp Tr_err(){
    return ex(T_Const(0));
}

// Ex exp
Tr_exp Tr_simpleVar(Tr_access acc, Tr_level l){
	Tr_level vl = acc->level;
	F_access vacc = acc->access;
	T_exp fp = T_Temp(F_FP());

	while(l != vl){
        // trace static link
		fp = T_Mem(T_Binop(T_plus, T_Const(-F_wordsize), fp));
		l = l->parent;
	}
	return ex(F_exp(vacc, fp));
}

Tr_exp Tr_fieldVar(Tr_exp base, int cnt){
	T_exp b = unEx(base);
	int offset = F_wordsize * cnt;
	T_exp field = T_Mem(T_Binop(T_plus, T_Const(offset), b));
	return ex(field);
}

Tr_exp Tr_subscriptVar(Tr_exp base, Tr_exp off){
	T_exp b = unEx(base);
	T_exp field = T_Mem(T_Binop(T_plus, 
                            T_Binop(T_mul, T_Const(F_wordsize), unEx(off)), b));
	return ex(field);
}

Tr_exp Tr_nil(){
    return ex(T_Const(0));
}

Tr_exp Tr_int(int i){
    return ex(T_Const(i));
}

Tr_exp Tr_string(string str){
    Temp_label lab = Temp_newlabel();
    F_frag strf = F_StringFrag(lab, str);
    strfrags = F_FragList(strf, strfrags);
    return ex(T_Name(lab));
}

Tr_exp Tr_call(Temp_label fname, Tr_expList params, Tr_level fl, Tr_level envl, string func){
    T_expList args = NULL;
    F_frame envf = envl->frame;
    int cnt = 0;
    for(Tr_expList l=params; l; l=l->tail){
        Tr_exp param = l->head;
        args = T_ExpList(unEx(param), args);
        cnt+=1;
    }

    // arg num > 6
    for(int i=0;i<cnt-6;i++){
        F_allocLocal(envf, TRUE);
    }
    
    if(!fname){
        return ex(F_externalCall(func, args));
    }
    
    Tr_level target = fl->parent;
    T_exp fp = T_Temp(F_FP());
	while(envl != target){
        // trace static link
		fp = T_Mem(T_Binop(T_plus, T_Const(-F_wordsize), fp));
		envl = envl->parent;
	}
    args = T_ExpList(fp, args);

    return ex(T_Call(T_Name(fname), args));
}

Tr_exp Tr_arithmetic(A_oper op, Tr_exp left, Tr_exp right){
    switch(op){
        case A_plusOp:
            return ex(T_Binop(T_plus,unEx(left),unEx(right)));
        case A_minusOp:
            return ex(T_Binop(T_minus,unEx(left),unEx(right)));
        case A_timesOp:
            return ex(T_Binop(T_mul,unEx(left),unEx(right)));
        case A_divideOp:
            return ex(T_Binop(T_div,unEx(left),unEx(right)));
        default:
            assert(0);
    }
}

// Cx exp
Tr_exp Tr_cond_norm(A_oper op, Tr_exp left, Tr_exp right){
    T_relOp rop;
    switch(op){
        case A_eqOp:rop=T_eq;break;
        case A_neqOp:rop=T_ne;break;
        case A_ltOp:rop=T_lt;break;
        case A_leOp:rop=T_le;break;
        case A_gtOp:rop=T_gt;break;
        case A_geOp:rop=T_ge;break;
    }
    T_stm s = T_Cjump(rop, unEx(left), unEx(right),NULL, NULL);
    patchList trues = PatchList(&(s->u.CJUMP.true),NULL);
    patchList falses = PatchList(&(s->u.CJUMP.false),NULL);
    struct Cx cond;
    cond.stm = s;
    cond.trues = trues;
    cond.falses = falses;
    
    return cx(cond);
}

Tr_exp Tr_cond_str(A_oper op, Tr_exp left, Tr_exp right){
    T_relOp rop;
    switch(op){
        case A_ltOp:
        case A_leOp:
        case A_gtOp:
        case A_geOp:
            return Tr_cond_norm(op, left, right);
        case A_eqOp:rop=T_eq;break;
        case A_neqOp:rop=T_ne;break;
    }
    T_exp func = F_externalCall("stringEqual", T_ExpList(unEx(left),T_ExpList(unEx(right),NULL)));
    T_stm s = T_Cjump(rop, func, T_Const(1), NULL, NULL);
    patchList trues = PatchList(&(s->u.CJUMP.true),NULL);
    patchList falses = PatchList(&(s->u.CJUMP.false),NULL);
    struct Cx cond;
    cond.stm = s;
    cond.trues = trues;
    cond.falses = falses;
    return cx(cond);  
}

Tr_exp Tr_record(Tr_expList list, int cnt){
    Temp_temp r = Temp_newtemp();
    T_exp base = T_Temp(r);

    T_stm fill;
    Tr_expList lp;
    int i;
    for(i=1,lp=list; i<=cnt; i++, lp=lp->tail){
        Tr_exp e = lp->head;
        int off = (cnt-i) * F_wordsize;
        
        T_stm move = T_Move(T_Mem(T_Binop(T_plus, T_Const(off), base)),unEx(e));

        if(i == 1)
            fill = move;
        else
            fill = T_Seq(move, fill);
    }

    int total = cnt * F_wordsize;
    T_stm init = T_Move(base, F_externalCall("malloc", T_ExpList(T_Const(total),NULL)));

    T_exp finall = T_Eseq(T_Seq(init,fill), base); 
    
    return ex(finall);    
}

Tr_exp Tr_SeqExp(Tr_expList list){
    T_exp e = unEx(list->head);
    T_exp s = NULL;
    Tr_expList p;
    for(p=list->tail;p;p=p->tail){
        if(s){
            s = T_Eseq(unNx(p->head),s);
        }
        else{
            s = T_Eseq(unNx(p->head),e);
        }
    }
    if(!s){
        return ex(e);
    }
    return ex(s);
}

// Nx exp
Tr_exp Tr_assign(Tr_exp pos, Tr_exp val){
    return nx(T_Move(unEx(pos), unEx(val)));
}
Tr_exp Tr_if(Tr_exp test, Tr_exp then, Tr_exp elsee, Ty_ty type){
    Temp_label t = Temp_newlabel();
    Temp_label f = Temp_newlabel();
    Temp_label next = Temp_newlabel();

    struct Cx testCx = unCx(test);
    doPatch(testCx.trues, t);
    doPatch(testCx.falses,f);

    T_stm testStm = testCx.stm;//Cx(t,f)

    if(type->kind == Ty_void){
        T_stm thenStm = unNx(then);
        T_stm elseStm = unNx(elsee);
        T_exp e = T_Eseq(testStm,
                T_Eseq(T_Label(t),
                    T_Eseq(thenStm, 
                        T_Eseq(T_Jump(T_Name(next), Temp_LabelList(next,NULL)),
                            T_Eseq(T_Label(f),
                                T_Eseq(elseStm,
                                    T_Eseq(T_Jump(T_Name(next), Temp_LabelList(next,NULL)),
                                        T_Eseq(T_Label(next), T_Const(0)))))))));

        return nx(T_Exp(e));
    }

    T_exp thenexp = unEx(then);
    T_exp elseexp = unEx(elsee);

    Temp_temp r = Temp_newtemp();
    
    T_exp e = T_Eseq(testStm,
                T_Eseq(T_Label(t),
                    T_Eseq(T_Move(T_Temp(r),thenexp), 
                        T_Eseq(T_Jump(T_Name(next), Temp_LabelList(next,NULL)),
                            T_Eseq(T_Label(f),
                                T_Eseq(T_Move(T_Temp(r),elseexp), 
                                    T_Eseq(T_Jump(T_Name(next), Temp_LabelList(next,NULL)),
                                        T_Eseq(T_Label(next), T_Temp(r)))))))));
    return ex(e);
}
Tr_exp Tr_while(Tr_exp test, Tr_exp body, Temp_label done){
    Temp_label check = Temp_newlabel();
    Temp_label run = Temp_newlabel();
    
    struct Cx testCx = unCx(test);
    
    doPatch(testCx.trues,run);
    doPatch(testCx.falses,done);
    
    T_stm testStm = testCx.stm;

    T_exp e = T_Eseq(T_Label(check),
                T_Eseq(testStm,
                    T_Eseq(T_Label(run),
                        T_Eseq(unNx(body),
                            T_Eseq(T_Jump(T_Name(check),Temp_LabelList(check,NULL)),
                                T_Eseq(T_Label(done),T_Const(0)))))));
    
    return nx(T_Exp(e));
}
Tr_exp Tr_for(Tr_exp forvar, Tr_exp lo, Tr_exp hi, Tr_exp body, Temp_label done){
    T_exp low = unEx(lo);
    T_exp high = unEx(hi);    
    T_exp i = unEx(forvar);

    Temp_label loop = Temp_newlabel();
    Temp_label pass = Temp_newlabel();

    T_stm init = T_Move(i,low);
    T_stm update = T_Move(i,T_Binop(T_plus, i, T_Const(1)));
    T_stm bodyy1 = unNx(body);
    T_stm bodyy2 = unNx(body);

    T_exp e = T_Eseq(init,
                    T_Eseq(T_Cjump(T_gt, i, high, done, loop),
                                T_Eseq(T_Label(loop), 
                                    T_Eseq(bodyy2,
                                        T_Eseq(update,
                                            T_Eseq(T_Cjump(T_le, i, high, loop, done),
                                                T_Eseq(T_Label(done), T_Const(0))))))));

    return nx(T_Exp(e));

}

Tr_exp Tr_break(Temp_label done){
    return nx(T_Jump(T_Name(done),Temp_LabelList(done,NULL)));
}

Tr_exp Tr_let(Tr_expList dec, Tr_exp body){
    T_exp e = unEx(body);
    T_exp s = NULL;
    for(Tr_expList p=dec;p;p=p->tail){
        if(s){
            s = T_Eseq(unNx(p->head), s);
        }
        else{
            s = T_Eseq(unNx(p->head), e);
        }
    }
    if(!s){
        return body;
    }
    return ex(s);
}

Tr_exp Tr_array(Tr_exp size, Tr_exp initvar){
    Temp_temp r = Temp_newtemp();
    T_exp base = T_Temp(r);
    T_stm init = T_Move(base, F_externalCall("initArray", T_ExpList(unEx(size),
                                                               T_ExpList(unEx(initvar),NULL))));
    T_exp finall = T_Eseq(init, base); 
    return ex(finall);   
} 

// Dec exp
Tr_exp Tr_varDec(Tr_access acc, Tr_exp init){
    T_exp pos = unEx(Tr_simpleVar(acc, acc->level));
    return nx(T_Move(pos, unEx(init)));
}

void Tr_procEntryExit(Tr_level level, Tr_exp body, Tr_accessList formals){
	F_frame f = level->frame;
	//fill holes
	T_stm s = T_Move(T_Temp(F_RAX()), unEx(body)); 
    s = F_procEntryExit1(f, s);

	F_frag proc = F_ProcFrag(s, f);

	funcfrags = F_FragList(proc, funcfrags);
}

F_fragList Tr_getResult(void){
    F_fragList p = strfrags;
    if(!p) 
        return funcfrags;
    while (p->tail){
        p = p->tail;
    }
    p->tail = funcfrags;
	return strfrags;
}