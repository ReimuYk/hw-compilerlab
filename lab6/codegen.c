#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "symbol.h"
#include "absyn.h"
#include "temp.h"
#include "errormsg.h"
#include "tree.h"
#include "assem.h"
#include "frame.h"
#include "codegen.h"
#include "table.h"

//Lab 6: put your code here
static void emit(AS_instr inst);
static void munchStm(T_stm stm);
static Temp_temp munchExp(T_exp exp);
static Temp_tempList munchArgs(int cnt, T_expList args);

static string frame_size = NULL;

static void emitFP(){
    char s[100];
    sprintf(s, "leaq %s(`s0), `d0", frame_size);
    emit(AS_Move(String(s), Temp_TempList(F_FP(),NULL), Temp_TempList(F_SP(),NULL)));
}

static void MEM(Temp_temp src, Temp_temp dst, T_exp e){
    if(src == F_FP())
        emitFP();
    if(dst == F_FP())
        emitFP();
    switch(e->kind){
        case T_CONST:{
            char mstr[100];
            sprintf(mstr,"movq %d(`s0), `d0", e->u.CONST);
            emit(AS_Move(String(mstr), Temp_TempList(dst,NULL), Temp_TempList(src,NULL)));
            return;
        }
        case T_TEMP:{
            Temp_temp t = e->u.TEMP;
            if(t == F_FP())
                emitFP();
            string mstr = "movq (`s0,`s1), `d0";
            emit(AS_Move(mstr, Temp_TempList(dst,NULL), Temp_TempList(src,Temp_TempList(t, NULL))));
            return;
        }
    }
}
static void MOVE(Temp_temp src, Temp_temp dst, T_exp e){
    if(src == F_FP())
        emitFP();
    if(dst == F_FP())
        emitFP();
    char ass[100];
    sprintf(ass,"movq `s0, %d(`s1)", e->u.CONST);
    emit(AS_Move(String(ass), NULL, Temp_TempList(src,Temp_TempList(dst,NULL))));
    return;
}

static void munchStm(T_stm stm){
    switch(stm->kind){
        case T_SEQ:{
            assert(0);
        }
        case T_LABEL:{
            Temp_label LABEL = stm->u.LABEL;
            emit(AS_Label(Temp_labelstring(LABEL), LABEL));
            return;
        }
        case T_JUMP:{
            T_exp expp = stm->u.JUMP.exp; 
            Temp_labelList jumps = stm->u.JUMP.jumps;
            emit(AS_Oper("jmp `j0", NULL, NULL, AS_Targets(jumps)));
            return;
        }
        case T_CJUMP:{
            T_relOp op = stm->u.CJUMP.op;            
			Temp_label t = stm->u.CJUMP.true;
            Temp_temp left = munchExp(stm->u.CJUMP.left);
            Temp_temp right = munchExp(stm->u.CJUMP.right);
            emit(AS_Oper("cmpq `s0, `s1", NULL, Temp_TempList(right, Temp_TempList(left, NULL)),NULL));
            string ass;
            switch(op){
                case T_eq:
                    ass="je `j0";
                    break;
                case T_ne:
                    ass="jne `j0";
                    break;
                case T_lt:
                    ass="jl `j0";
                    break;
                case T_gt:
                    ass="jg `j0";
                    break;
                case T_le:
                    ass="jle `j0";
                    break;
                case T_ge:
                    ass="jge `j0";
                    break;
		        case T_ult:
                    ass="jb `j0";
                    break;
                case T_ule:
                    ass="jbe `j0";
                    break;
                case T_ugt:
                    ass="ja `j0";
                    break;
                case T_uge:
                    ass="jae `j0";
                    break;
            }
            emit(AS_Oper(ass, NULL, NULL, AS_Targets(Temp_LabelList(t, NULL))));
            return;
        }
        case T_EXP:{
            Temp_temp ts = munchExp(stm->u.EXP);
            Temp_temp td = Temp_newtemp();
            Temp_tempList s = Temp_TempList(ts,NULL);
            Temp_tempList d = Temp_TempList(td,NULL);
            emit(AS_Move("movq `s0, `d0", d, s));
            return;
        }
        case T_MOVE:{
            Temp_temp s = munchExp(stm->u.MOVE.src);
            T_exp dst = stm->u.MOVE.dst;
            if(dst->kind == T_TEMP){
                emit(AS_Move("movq `s0, `d0", Temp_TempList(dst->u.TEMP,NULL), Temp_TempList(s,NULL)));
                return;
            }
            else if(dst->kind == T_MEM){
                switch(dst->u.MEM->kind){
                    case T_TEMP:{
                        Temp_temp TEMP = dst->u.MEM->u.TEMP;
                        emit(AS_Move("movq `s0, (`s1)", NULL,Temp_TempList(s,Temp_TempList(TEMP,NULL))));
                        return;
                    }     
                    case T_CONST:{
                        Temp_temp d = munchExp(dst->u.MEM);
                        emit(AS_Move("movq `s0, (`s1)", NULL,Temp_TempList(s,Temp_TempList(d,NULL))));
                        return;
                    }       
                    case T_BINOP:{
                        T_binOp op = dst->u.MEM->u.BINOP.op;
                        T_exp left = dst->u.MEM->u.BINOP.left;
                        T_exp right = dst->u.MEM->u.BINOP.right;
                        if(left->kind!=T_CONST && left->kind!=T_TEMP && right->kind!=T_CONST && right->kind!=T_TEMP){
                            Temp_temp d = munchExp(dst->u.MEM);
                            emit(AS_Move("movq `s0, (`s1)", NULL ,Temp_TempList(s,Temp_TempList(d,NULL))));
                            return;
                        }
                        if(left->kind!=T_CONST && left->kind!=T_TEMP){
                            Temp_temp d = munchExp(left);
                            MOVE(s,d,right);
                            return;
                        }
                        if(right->kind!=T_CONST && right->kind!=T_TEMP){
                            Temp_temp d = munchExp(right);
                            MOVE(s, d, left);
                            return;
                        }
                        else{
                            if(right->kind == T_TEMP)
                                MOVE(s, right->u.TEMP, left);
                            else if(left->kind == T_TEMP)
                                MOVE(s, left->u.TEMP, right);
                            else{
                                assert(0);// impossible
                            }
                            return;
                        }
                    }
                }
            }
            assert(0); // impossible
            return;
        }
	    
    }
}

static Temp_temp munchExp(T_exp e){
    switch(e->kind){        
        case T_BINOP:{
            T_binOp op = e->u.BINOP.op;
            Temp_temp left = munchExp(e->u.BINOP.left);
            Temp_temp right = munchExp(e->u.BINOP.right);
            string ass;
            switch(op){
                case T_plus:
                    ass = "addq `s1, `d0";
                    break;
                case T_minus:
                    ass = "subq `s1, `d0";
                    break;
                case T_mul:
                    ass = "imulq `s1, `d0";
                    break;
                case T_div:{
                   emit(AS_Move("movq `s0, `d0",Temp_TempList(F_RAX(),NULL),Temp_TempList(left,NULL)));
                   emit(AS_Oper("cqto",Temp_TempList(F_RAX(),Temp_TempList(F_RDX(), NULL)),NULL,NULL));
                   emit(AS_Oper("idivq `s0", Temp_TempList(F_RAX(),Temp_TempList(F_RDX(), NULL)), Temp_TempList(right,NULL), NULL));
                   return F_RAX();
                }
                default:
                    assert(0);
            }

            if(e->u.BINOP.left->kind == T_TEMP){
                Temp_temp n = Temp_newtemp();
                emit(AS_Move("movq `s0, `d0", Temp_TempList(n,NULL), Temp_TempList(left,NULL)));
                emit(AS_Oper(ass, Temp_TempList(n, NULL), Temp_TempList(n, Temp_TempList(right,NULL)), NULL));
                return n;
            }
            
            emit(AS_Oper(ass, Temp_TempList(left, NULL), Temp_TempList(left, Temp_TempList(right,NULL)), NULL));
            return left;
        }
        case T_MEM:{
            Em_log("T MEM %d",e->u.MEM->kind);
            Temp_temp dst = Temp_newtemp();
            switch(e->u.MEM->kind){
                case T_TEMP:{
                    Em_log("T TEMP");
                    Temp_temp TEMP = e->u.MEM->u.TEMP;
                    if(TEMP == F_FP())
                        emitFP();
                    emit(AS_Move("movq (`s0), `d0", Temp_TempList(dst,NULL),Temp_TempList(TEMP,NULL)));
                    return dst;
                }      
                case T_BINOP:{
                    T_binOp op = e->u.MEM->u.BINOP.op;
                    T_exp left = e->u.MEM->u.BINOP.left;
                    T_exp right = e->u.MEM->u.BINOP.right;
                    if(left->kind!=T_CONST && left->kind!=T_TEMP && right->kind!=T_CONST && right->kind!=T_TEMP){
                        Temp_temp src = munchExp(e->u.MEM);
                        emit(AS_Move("movq (`s0), `d0", Temp_TempList(dst,NULL),Temp_TempList(src,NULL)));
                        return dst;
                    }
                    if(right->kind!=T_CONST && right->kind!=T_TEMP){
                        Temp_temp src = munchExp(right);
                        MEM(src, dst, left);
                        return dst;
                    }
                    else{
                        if(right->kind == T_TEMP)
                            MEM(right->u.TEMP, dst, left);
                        else if(left->kind == T_TEMP)
                            MEM(left->u.TEMP, dst, right);
                        return dst;
                    }
                }
            }
            assert(0);
        }
        case T_TEMP:{
            Temp_temp t = e->u.TEMP;
            if (t == F_FP())
                emitFP(); 
           return t;
        }
        case T_ESEQ:{
            assert(0);
        }
        case T_NAME:{
            Temp_label NAME = e->u.NAME;
            Temp_temp dst = Temp_newtemp();
            char str[100];
            sprintf(str,"leaq %s, `d0", Temp_labelstring(NAME));
            emit(AS_Oper(String(str), Temp_TempList(dst, NULL), NULL, NULL));
            return dst;
        }
		case T_CONST:{
            Temp_temp d = Temp_newtemp();
            char cstr[100];
            sprintf(cstr, "movq $%d, `d0", e->u.CONST);
            emit(AS_Move(String(cstr), Temp_TempList(d,NULL), NULL));
            return d;
        }
        case T_CALL:{
            T_exp fun = e->u.CALL.fun; 
            T_expList args = e->u.CALL.args;
            Temp_tempList regs = munchArgs(0, args);
            Temp_tempList calldefs = Temp_TempList(F_RAX(), F_callerSave());
            char call[100];
            sprintf(call, "call %s", Temp_labelstring(fun->u.NAME));
            emit(AS_Oper(String(call), calldefs, regs, NULL));
            return F_RAX();
        }
    }
}

static Temp_tempList munchArgs(int cnt, T_expList args){
    if (args==NULL){
        return NULL;
    }
    T_exp arg = args->head;
    Temp_temp src = munchExp(arg);
    switch(cnt){
        case 0:{ // rdi
            Temp_temp dst = F_RDI();
            Temp_tempList tl = Temp_TempList(dst, munchArgs(cnt+1, args->tail));
            emit(AS_Move("movq `s0, `d0", Temp_TempList(dst,NULL),Temp_TempList(src,NULL)));
            return tl;
        }
        case 1:{ // rsi
            Temp_temp dst = F_RSI();
            Temp_tempList tl = Temp_TempList(dst, munchArgs(cnt+1, args->tail));
            emit(AS_Move("movq `s0, `d0", Temp_TempList(dst,NULL),Temp_TempList(src,NULL)));
            return tl;
        }
        case 2:{ // rdx
            Temp_temp dst = F_RDX();
            Temp_tempList tl = Temp_TempList(dst, munchArgs(cnt+1, args->tail));
            emit(AS_Move("movq `s0, `d0", Temp_TempList(dst,NULL),Temp_TempList(src,NULL)));
            return tl;
        }
        case 3:{ // rcx
            Temp_temp dst = F_RCX();
            Temp_tempList tl = Temp_TempList(dst, munchArgs(cnt+1, args->tail));
            emit(AS_Move("movq `s0, `d0", Temp_TempList(dst,NULL),Temp_TempList(src,NULL)));
            return tl;
        }
        case 4:{ // r8
            Temp_temp dst = F_R8();
            Temp_tempList tl = Temp_TempList(dst, munchArgs(cnt+1, args->tail));
            emit(AS_Move("movq `s0, `d0", Temp_TempList(dst,NULL),Temp_TempList(src,NULL)));
            return tl;
        }
        case 5:{ // r9
            Temp_temp dst = F_R9();
            Temp_tempList tl = Temp_TempList(dst, munchArgs(cnt+1, args->tail));
            emit(AS_Move("movq `s0, `d0", Temp_TempList(dst,NULL),Temp_TempList(src,NULL)));
            return tl;
        }
        default:{
            munchArgs(cnt+1, args->tail);
            char str[100];
            sprintf(str, "movq `s0, %d(`s1)", (cnt-6)*F_wordsize);
            emit(AS_Move(String(str), NULL, Temp_TempList(src,Temp_TempList(F_SP(),NULL))));
            return NULL;
        }
    }
}

static AS_instrList inst_list;
static void emit(AS_instr inst) {
    if(!inst_list){
        inst_list = AS_InstrList(inst, NULL);
    }else{
        AS_instrList listtail = inst_list;
        while(listtail->tail){
            listtail = listtail->tail;
        }
        listtail->tail = AS_InstrList(inst,NULL);
    }
}


AS_instrList F_codegen(F_frame f, T_stmList stmList) {
    Em_log("codegen");
    inst_list = NULL;
    AS_instrList list; 

    char fs[100];
    sprintf(fs, "%s_framesize", Temp_labelstring(F_name(f)));
    frame_size = String(fs);

    char alloc_frame_assem[100];
    sprintf(alloc_frame_assem, "subq $%s, `d0", frame_size);
    emit(AS_Oper(String(alloc_frame_assem), Temp_TempList(F_SP(),NULL), Temp_TempList(F_SP(),NULL), NULL));

    for (T_stmList sl=stmList; sl; sl = sl->tail){
        // Em_log("codegen - munchStm");
        T_stm stm = sl->head;
        munchStm(stm);
    }

    char exit_frame_assem[100];
    sprintf(exit_frame_assem, "addq $%s, `d0", frame_size);
    emit(AS_Oper(String(exit_frame_assem), Temp_TempList(F_SP(),NULL), Temp_TempList(F_SP(),NULL), NULL));

    return F_procEntryExit2(inst_list);
}

