#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "symbol.h"
#include "temp.h"
#include "table.h"
#include "tree.h"
#include "frame.h"

/*Lab5: Your implementation here.*/

const int F_wordsize = 8;

//F_frame_ in PPT
struct F_frame_ {
	Temp_label name;
	
	F_accessList formals;
	F_accessList locals;

	//the number of arguments
	int argSize;
	
	//the number of local variables
	int length;

	//register lists for the frame
	F_accessList calleesaves;
	F_accessList callersaves;
};

//varibales
struct F_access_ {
	enum {inFrame, inReg} kind;
	union {
		int offset; //inFrame
		Temp_temp reg; //inReg
	} u;
};

/* functions */
static F_access InFrame(int offset){
	F_access ac = checked_malloc(sizeof(*ac));

	ac->kind = inFrame;
	ac->u.offset = offset;
	return ac;
}   
int F_getFrameOff(F_access acc){
	return acc->u.offset;
}

static F_access InReg(Temp_temp reg){
	F_access ac = checked_malloc(sizeof(*ac));

	ac->kind = inReg;
	ac->u.reg = reg;
	return ac;
}

F_accessList F_AccessList(F_access head, F_accessList tail){
	F_accessList l = checked_malloc(sizeof(*l));

	l->head = head;
	l->tail = tail;
	return l;
}

// param position wait to be reset
F_accessList makeFormalsF(F_frame f, U_boolList formals, int* cntp){
	if(!formals){
		return NULL;
	}
	bool esc = formals->head;
	int cnt = *cntp;
	*cntp = cnt+1;

	F_access ac = F_allocLocal(f, esc);//args;
	
	if(formals->tail){
		return F_AccessList(ac, makeFormalsF(f, formals->tail, cntp));
	}
	else{
		return F_AccessList(ac, NULL);
	}
}

F_accessList F_callerPos(F_frame f){
	Temp_tempList regs =  F_callerSave();
	F_accessList l = NULL;
	F_accessList last = NULL;
	for(;regs;regs=regs->tail){
		F_access acc = F_allocLocal(f,FALSE);
		if(!last){
			last = F_AccessList(acc, NULL);
			l = last;
		}
		else{
			last->tail = F_AccessList(acc, NULL);
			last = last->tail;
		}
	}
	return l;
}

F_accessList F_calleePos(F_frame f){
	Temp_tempList regs = F_calleeSave();
	F_accessList l = NULL;
	F_accessList last = NULL;
	for(;regs;regs=regs->tail){
		F_access acc = F_allocLocal(f,FALSE);
		if(!last){
			last = F_AccessList(acc, NULL);
			l = last;
		}
		else{
			last->tail = F_AccessList(acc, NULL);
			last = last->tail;
		}
	}
	return l;
}

F_frame F_newFrame(Temp_label name, U_boolList formals){
	F_frame f = checked_malloc(sizeof(*f));
	f->length = 0;
	int *argsize = checked_malloc(sizeof(int));
	*argsize = 0;
	
	f->name = name;
	f->formals = makeFormalsF(f, formals, argsize);
	f->locals = NULL;
	f->argSize = *argsize;
	

	f->calleesaves = F_calleePos(f);
	f->callersaves = F_callerPos(f);

	return f;
}

F_access F_allocLocal(F_frame f, bool escape){
	int length = f->length;
	F_accessList locals = f->locals;

	F_access ac;
	if(escape){
		ac = InFrame(-(length+1) * F_wordsize);
		f->length = length+1;
	}
	else{
		ac = InReg(Temp_newtemp());
	}

	
	f->locals = F_AccessList(ac, locals);

	return ac;
}

Temp_label F_name(F_frame f){
	return f->name;
}
F_accessList F_formals(F_frame f){
	return f->formals;
}
int F_length(F_frame f){
	return f->length;
}
/* IR translation */

Temp_temp F_FP(void){
	static Temp_temp fp  = NULL;
	if(!fp){
		fp = Temp_newtemp();
	}
	return fp;
}
Temp_temp F_SP(void){
	static Temp_temp sp  = NULL;
	if(!sp){
		sp = Temp_newtemp();
		Temp_enter(F_tempMap, sp, "%rsp");
	}
	return sp;
}
Temp_temp F_RAX(void){
	static Temp_temp r = NULL;
	if(!r){
		r = Temp_newtemp();
		Temp_enter(F_tempMap, r, "%rax");
	}
	return r;
}
Temp_temp F_RDI(void){
	static Temp_temp r = NULL;
	if(!r){
		r = Temp_newtemp();
		Temp_enter(F_tempMap, r, "%rdi");
	}
	return r;
}
Temp_temp F_RSI(void){
	static Temp_temp r = NULL;
	if(!r){
		r = Temp_newtemp();
		Temp_enter(F_tempMap, r, "%rsi");
	}
	return r;
}
Temp_temp F_RDX(void){
	static Temp_temp r = NULL;
	if(!r){
		r = Temp_newtemp();
		Temp_enter(F_tempMap, r, "%rdx");
	}
	return r;
}
Temp_temp F_RCX(void){
	static Temp_temp r = NULL;
	if(!r){
		r = Temp_newtemp();
		Temp_enter(F_tempMap, r, "%rcx");
	}
	return r;
}
Temp_temp F_RBX(void){
	static Temp_temp r = NULL;
	if(!r){
		r = Temp_newtemp();
		Temp_enter(F_tempMap, r, "%rbx");
	}
	return r;
}
Temp_temp F_RBP(void){
	static Temp_temp r = NULL;
	if(!r){
		r = Temp_newtemp();
		Temp_enter(F_tempMap, r, "%rbp");
	}
	return r;
}
Temp_temp F_R8(void){
	static Temp_temp r = NULL;
	if(!r){
		r = Temp_newtemp();
		Temp_enter(F_tempMap, r, "%r8");
	}
	return r;
}
Temp_temp F_R9(void){
	static Temp_temp r = NULL;
	if(!r){
		r = Temp_newtemp();
		Temp_enter(F_tempMap, r, "%r9");
	}
	return r;
}
Temp_temp F_R10(void){
	static Temp_temp r = NULL;
	if(!r){
		r = Temp_newtemp();
		Temp_enter(F_tempMap, r, "%r10");
	}
	return r;
}
Temp_temp F_R11(void){
	static Temp_temp r = NULL;
	if(!r){
		r = Temp_newtemp();
		Temp_enter(F_tempMap, r, "%r11");
	}
	return r;
}
Temp_temp F_R12(void){
	static Temp_temp r = NULL;
	if(!r){
		r = Temp_newtemp();
		Temp_enter(F_tempMap, r, "%r12");
	}
	return r;
}
Temp_temp F_R13(void){
	static Temp_temp r = NULL;
	if(!r){
		r = Temp_newtemp();
		Temp_enter(F_tempMap, r, "%r13");
	}
	return r;
}
Temp_temp F_R14(void){
	static Temp_temp r = NULL;
	if(!r){
		r = Temp_newtemp();
		Temp_enter(F_tempMap, r, "%r14");
	}
	return r;
}
Temp_temp F_R15(void){
	static Temp_temp r = NULL;
	if(!r){
		r = Temp_newtemp();
		Temp_enter(F_tempMap, r, "%r15");
	}
	return r;
}

Temp_tempList F_Args(){
	// rdi rsi rdx rcx r8 r9
	return Temp_TempList(F_RDI(),
				Temp_TempList(F_RSI(),
					Temp_TempList(F_RDX(),
						Temp_TempList(F_RCX(),
							Temp_TempList(F_R8(),
								Temp_TempList(F_R9(),NULL))))));
}
Temp_tempList F_callerSave(){
	// r10 r11 argregs
	return Temp_TempList(F_R10(), Temp_TempList(F_R11(), F_Args()));
}
Temp_tempList F_calleeSave(){
	// r12 r13 r14 r15 rbx rbp
	return Temp_TempList(F_R12(), 
				Temp_TempList(F_R13(),
					Temp_TempList(F_R14(), 
						Temp_TempList(F_R15(), 
							Temp_TempList(F_RBX(),
								Temp_TempList(F_RBP(), NULL))))));
}
Temp_tempList F_register(){
	static Temp_tempList regs = NULL;
	if(!regs){
		regs = Temp_TempList(F_SP(),
					Temp_TempList(F_RAX(),
						F_calleeSave()));
		regs = Temp_add(regs, F_callerSave());
	}
	return regs;											
}

T_exp F_exp(F_access acc, T_exp framePtr){
	if(acc->kind == inFrame){
		int off = acc->u.offset;
		return T_Mem(T_Binop(T_plus, T_Const(off), framePtr));
	}
	else{
		return T_Temp(acc->u.reg);
	}
}

T_exp F_externalCall(string s, T_expList args){
	return T_Call(T_Name(Temp_namedlabel(s)), args);
}


/* fragment */
F_frag F_StringFrag(Temp_label label, string str) { 
	F_frag f = checked_malloc(sizeof(*f));
	f->kind = F_stringFrag;
	f->u.stringg.label = label;
	f->u.stringg.str = str;

	return f;                                      
}                                                     
                                                      
F_frag F_ProcFrag(T_stm body, F_frame frame) {        
	F_frag f = checked_malloc(sizeof(*f));
	f->kind = F_procFrag;
	f->u.proc.body = body;
	f->u.proc.frame = frame;

	return f;                                     
}                                                     
                                                      
F_fragList F_FragList(F_frag head, F_fragList tail) { 
	F_fragList l = checked_malloc(sizeof(*l));
	l->head = head;
	l->tail = tail;
	return l;                                      
}                                                     

T_exp F_procChange(F_frame f, T_exp call){
	T_exp fp = T_Temp(F_FP());
	//caller save
	T_stm save = NULL;
	F_accessList al = f->callersaves;
	Temp_tempList tl = F_callerSave();
	for(;tl;tl=tl->tail, al=al->tail){
		T_exp pos = F_exp(al->head, fp);
		if(save){
			save = T_Seq(T_Move(pos, T_Temp(tl->head)), save);
		}
		else{
			save = T_Move(pos, T_Temp(tl->head));
		}
	}

	//caller restore
	T_stm restore = NULL;
	al = f->callersaves;
	tl = F_callerSave();
	for(;tl;tl=tl->tail, al=al->tail){
		T_exp pos = F_exp(al->head, fp);
		if(restore){
			restore = T_Seq(T_Move(T_Temp(tl->head),pos), restore);
		}
		else{
			restore = T_Move(T_Temp(tl->head), pos);
		}
	}

	Temp_temp t = Temp_newtemp();
	T_exp e = T_Eseq(save,
				T_Eseq(T_Move(T_Temp(t), call),
					T_Eseq(restore, T_Temp(t))));
	return e;

}

T_stm F_procEntryExit1(F_frame f, T_stm stm){
	//view change
	T_stm view = NULL;
	int cnt = 0;
	T_exp fp = T_Temp(F_FP());
	for(F_accessList l=f->formals;l;l=l->tail){
		F_access arg = l->head;
		T_exp argpos = F_exp(arg,fp);
		switch(cnt){
			case 0:// rdi
				view=T_Move(argpos,T_Temp(F_RDI()));
				break;
			case 1:// rsi
				view = T_Seq(T_Move(argpos,T_Temp(F_RSI())),view);
				break;
			case 2:// rdx
				view = T_Seq(T_Move(argpos,T_Temp(F_RDX())),view);
				break;
			case 3:// rcx
				view = T_Seq(T_Move(argpos,T_Temp(F_RCX())),view);
				break;
			case 4:// r8
				view = T_Seq(T_Move(argpos,T_Temp(F_R8())),view);
				break;
			case 5:// r9
				view = T_Seq(T_Move(argpos,T_Temp(F_R9())),view);
				break;
			default:{
				int off = (cnt-6+1)*F_wordsize ;
				view = T_Seq(
						T_Move(argpos,T_Mem(T_Binop(T_plus, T_Const(off), fp))),view);
			}
		}
		cnt += 1;
	}

	//callee save
	T_stm save = NULL;
	F_accessList al = f->calleesaves;
	Temp_tempList tl = F_calleeSave();
	for(;tl;tl=tl->tail, al=al->tail){
		T_exp pos = F_exp(al->head, fp);
		if(save){
			save = T_Seq(T_Move(pos, T_Temp(tl->head)), save);
		}
		else{
			save = T_Move(pos, T_Temp(tl->head));
		}
	}

	//callee restore
	T_stm restore = NULL;
	al = f->calleesaves;
	tl = F_calleeSave();
	for(;tl;tl=tl->tail, al=al->tail){
		T_exp pos = F_exp(al->head, fp);
		if(restore){
			restore = T_Seq(T_Move(T_Temp(tl->head),pos), restore);
		}
		else{
			restore = T_Move(T_Temp(tl->head), pos);
		}
	}

	if(!view){
		return T_Seq(save,T_Seq(stm, restore));
	}
	return T_Seq(save,T_Seq(view, T_Seq(stm, restore)));
}
AS_instrList F_procEntryExit2(AS_instrList body){
	static Temp_tempList returnSink = NULL ;
	if (!returnSink)  
		returnSink = Temp_TempList(F_SP(), F_calleeSave());
    return AS_splice(body, 
				AS_InstrList(AS_Oper("ret", NULL, returnSink, NULL), NULL));

}

// helper of F_procEntryExit3
static string str_replace(char* s, char* old, char* new){
	int location = -1;
	int len_s = strlen(s);
	int len_old = strlen(old);
	int len_new = strlen(new);
	for(int i=0;i<len_s-len_old+1;i++){
		if (!strncmp(s+i,old,len_old)){
			location = i;
		}
	}
	if(location==-1){
		return String(s);
	}
	char ret[100];
	for(int i=0;i<len_s-len_old+len_new;i++){
		if (i<location){
			ret[i] = s[i];
		}else if(i<location+len_new){
			ret[i] = new[i-location];
		}else{
			ret[i] = s[i+len_old-len_new];
		}
	}
	ret[len_s-len_old+len_new]='\0';
	return String(ret);
}

AS_proc F_procEntryExit3(F_frame frame, AS_instrList body){
	int len = frame->length;
	string fn =  S_name(F_name(frame));
	char target[100];
	char length[20];
	sprintf(target, "%s_framesize", fn);
	sprintf(length, "%d", F_wordsize*len);

	// rewrite the framesize
	AS_instrList ilist = body;
	while (ilist){
		AS_instr ins = ilist->head;
		string ass = ins->u.MOVE.assem;
		ins->u.MOVE.assem = str_replace(ass,target,length);  
		ilist = ilist->tail; 
	}

	return AS_Proc("", body, "");
}

