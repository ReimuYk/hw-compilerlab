#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "util.h"
#include "absyn.h"
#include "temp.h"
#include "frame.h"
#include "types.h"
#include "printtree.h"

/* Lab5: your code below */

typedef struct Tr_exp_ *Tr_exp;
typedef struct Tr_expList_ *Tr_expList; // ADD
typedef struct Tr_access_ *Tr_access;
typedef struct Tr_accessList_ *Tr_accessList;
typedef struct Tr_level_ *Tr_level;
typedef struct patchList_ *patchList; // 

// structs
struct Tr_access_ { Tr_level level; F_access access; };
struct Tr_accessList_ { Tr_access head; Tr_accessList tail; };
struct Tr_level_ { F_frame frame; Tr_level parent; };
struct patchList_ { Temp_label *head; patchList tail; };
struct Cx {	patchList trues; patchList falses; 	T_stm stm;};
struct Tr_exp_ { 
    enum { Tr_ex, Tr_nx, Tr_cx } kind;
    union {
        T_exp ex;
        T_stm nx;
        struct Cx cx;
    } u;
};
struct Tr_expList_ {Tr_exp head; Tr_expList tail;};

Tr_accessList Tr_AccessList(Tr_access head, Tr_accessList tail);
Tr_level Tr_outermost(void);
Tr_level Tr_newLevel(Tr_level parent, Temp_label name, U_boolList formals);

Tr_accessList Tr_formals(Tr_level level);
Tr_access Tr_allocLocal(Tr_level level, bool escape);
Tr_expList Tr_ExpList(Tr_exp head, Tr_expList tail);

void Tr_procEntryExit(Tr_level level, Tr_exp body, Tr_accessList formals);

//---------------


/* IR translation */
F_fragList Tr_getResult(void);

Tr_exp Tr_err();

// Ex
Tr_exp Tr_simpleVar(Tr_access acc, Tr_level l);
Tr_exp Tr_fieldVar(Tr_exp base,  int cnt);
Tr_exp Tr_subscriptVar(Tr_exp base, Tr_exp off);

Tr_exp Tr_nil();
Tr_exp Tr_int(int i);
Tr_exp Tr_string(string str);
Tr_exp Tr_call(Temp_label fname, Tr_expList params, Tr_level fl, Tr_level envl, string func);
Tr_exp Tr_arithmetic(A_oper op, Tr_exp left, Tr_exp right);

// Cx
Tr_exp Tr_cond_norm(A_oper op, Tr_exp left, Tr_exp right);
Tr_exp Tr_cond_str(A_oper op, Tr_exp left, Tr_exp right);


Tr_exp Tr_record(Tr_expList list, int cnt);
Tr_exp Tr_SeqExp(Tr_expList list);

// Nx
Tr_exp Tr_assign(Tr_exp pos, Tr_exp val);
Tr_exp Tr_if(Tr_exp test, Tr_exp then, Tr_exp elsee, Ty_ty type);
Tr_exp Tr_while(Tr_exp test, Tr_exp body, Temp_label done);
Tr_exp Tr_for(Tr_exp forvar, Tr_exp lo, Tr_exp hi, Tr_exp body, Temp_label done);
Tr_exp Tr_break(Temp_label done);

Tr_exp Tr_let(Tr_expList dec, Tr_exp body);
Tr_exp Tr_array(Tr_exp size, Tr_exp initvar);

// Dec exp
Tr_exp Tr_varDec(Tr_access acc, Tr_exp init);

#endif
