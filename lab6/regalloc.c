#include <stdio.h>
#include "util.h"
#include "symbol.h"
#include "temp.h"
#include "tree.h"
#include "absyn.h"
#include "assem.h"
#include "frame.h"
#include "graph.h"
#include "liveness.h"
#include "color.h"
#include "regalloc.h"
#include "table.h"
#include "flowgraph.h"

#define K 16 // reg number

static G_nodeList precolored;
static G_nodeList coloredNode;
static G_nodeList spilledNode;
static G_nodeList coalescedNodes;

static G_nodeList spillWorkList;
static G_nodeList freezeWorkList;
static G_nodeList simplifyWorkList;

static Live_moveList worklistMoves;
static Live_moveList coalescedMoves;
static Live_moveList frozenMoves;
static Live_moveList constrainedMoves;
static Live_moveList activeMoves;


// stack
static G_nodeList selectStack;

// extra helper (for list operation)
G_nodeList L_except(G_nodeList li, G_node node){
    G_nodeList p = li;
    G_nodeList last = NULL;
    while(p){
        if(p->head == node){
            if(last){
                last->tail = p->tail;
                break;
            }
            else{
                li = li->tail;
                break;
            }
        }
        last = p;
        p = p->tail;
    }
    return li;
}

G_nodeList L_union(G_nodeList A, G_nodeList B){
    G_nodeList ret = A;

    for(;B;B=B->tail){
        G_node n = B->head;
        if(!G_inNodeList(n, A)){
            ret = G_NodeList(n, ret);
        }
    }
    return ret;
}

G_nodeList L_minus(G_nodeList A, G_nodeList B){
    G_nodeList ret = NULL;
    for(;A;A=A->tail){
        G_node n = A->head;
        if(!G_inNodeList(n, B)){
            ret = G_NodeList(n, ret);
        }
    }
    return ret;
}

bool L_in(G_node node, Live_moveList list){
    for(;list;list = list->tail){
        if(node == list->dst || node == list->src){
            return TRUE;
        }
    }
    return FALSE;
}

Live_moveList L_exceptRelated(G_node node, Live_moveList list){
    Live_moveList li = NULL;
    Live_moveList last = NULL;
    for(;list;list = list->tail){
        if(node == list->dst || node == list->src){
            li = Live_MoveList(list->src, list->dst, li);
            if(last){
                last->tail = list->tail;
                list = last;
            }
        }
        last = list;
    }
    return li;
}

// code in textbook
static void init(){
	//node set
	precolored = NULL;
	coloredNode = NULL;
	spilledNode = NULL;
	coalescedNodes = NULL;

	//nodeWorklist
	spillWorkList = NULL;
	freezeWorkList = NULL;
	simplifyWorkList = NULL;

	//moveList
	worklistMoves = NULL;
	coalescedMoves = NULL;
	frozenMoves = NULL;
	constrainedMoves = NULL;
	activeMoves = NULL;

	selectStack = NULL;
}

static void push(G_node node, G_nodeList *tail){
	*tail = G_NodeList(node, *tail);
}

static G_nodeList NodeMoves(G_node node){
	
}

static bool MoveRelated(G_node node){
	return L_in(node, worklistMoves) || L_in(node, activeMoves);
}

static G_nodeList Adjacent(G_node node){
	// adjList(n) \ (selectStack U coalescedNodes)
	return L_minus(G_adj(node),L_union(selectStack,coalescedNodes));
}

static void EnableMoves(G_nodeList nodes){
	for(;nodes;nodes=nodes->tail){
		G_node node = nodes->head;
		if(L_in(node, activeMoves)){
			activeMoves = activeMoves->tail;
		}
	}	
}

static void DecrementDegree(G_node node){
	nodeInfo info = G_nodeInfo(node);
	int d = info->degree;
	info->degree = d-1;
	if(d == K){
		EnableMoves(G_NodeList(node, Adjacent(node)));
		spillWorkList = L_except(spillWorkList, node);
		if(MoveRelated(node)){
			push(node, &freezeWorkList);
		}
		else{
			push(node, &simplifyWorkList);
		}
	}
}

static G_node GetAlias(G_node node){
	if(G_inNodeList(node, coalescedNodes)){
		nodeInfo info = G_nodeInfo(node);
		return GetAlias(info->alias);
	}
	else
		return node;
}

static void AddWorkList(G_node node){
	nodeInfo info = G_nodeInfo(node);
	if(!G_inNodeList(node, precolored) && !MoveRelated(node) && info->degree < K){
		freezeWorkList = L_except(freezeWorkList, node);
		push(node, &simplifyWorkList);
	}
}

static bool OK(G_node t, G_node r){
	nodeInfo info = G_nodeInfo(t);
	return (info->degree < K || G_inNodeList(t,precolored)	|| G_inNodeList(t, G_adj(r)));
}

static void Combine(G_node u, G_node v){
	if(G_inNodeList(v, freezeWorkList))
		freezeWorkList = L_except(freezeWorkList, v);
	else
		spillWorkList = L_except(spillWorkList, v);

	coalescedNodes = G_NodeList(v, coalescedNodes);
	nodeInfo vinfo = G_nodeInfo(v);
	vinfo->alias = u;
	EnableMoves(G_NodeList(v, NULL));
	for(G_nodeList nl=Adjacent(v);nl;nl=nl->tail){
		G_node t = nl->head;
		if(G_goesTo(u, t) || u == t)continue;
		G_addEdge(t, u);		
		DecrementDegree(t);
	}
	nodeInfo uinfo = G_nodeInfo(u);
	if(uinfo->degree>=K && G_inNodeList(u, freezeWorkList)){
		freezeWorkList = L_except(freezeWorkList, u);
		spillWorkList = G_NodeList(u, spillWorkList);
	}	
}

static void FreezeMoves(G_node node){
	Live_moveList ml = L_exceptRelated(node, activeMoves);
	if(L_in(node, activeMoves))
		activeMoves = activeMoves->tail;
	for(;ml;ml=ml->tail){
		G_node src = GetAlias(ml->src);
		G_node dst = GetAlias(ml->dst);
		G_node v;
		if(GetAlias(node) == src)
			v = dst;
		else
			v = src;
		frozenMoves = Live_MoveList(ml->src, ml->dst, frozenMoves);
		
		nodeInfo vinfo = G_nodeInfo(v);
		if(!G_inNodeList(v,precolored) && !L_in(v, activeMoves) && vinfo->degree<K){
			freezeWorkList = L_except(freezeWorkList, v);
			simplifyWorkList = G_NodeList(v, simplifyWorkList);
		}

	}
}

static void MakeWorkList(G_graph cfgraph){
	G_nodeList nl = G_nodes(cfgraph);
	for(;nl;nl=nl->tail){
		G_node node = nl->head;
		nodeInfo info = G_nodeInfo(node);
		int degree = G_degree(node);
		info->degree = degree;
		if(Temp_look(F_tempMap, info->reg)){
			info->degree = 9999;
			push(node, &precolored);
			continue;
		}		
		if(degree >= K){
			push(node, &spillWorkList);
		}
		else if(MoveRelated(node)){
			push(node, &freezeWorkList);
		}
		else{
			push(node, &simplifyWorkList);
		}
	}
}
static void Simplify(){
	G_node n = simplifyWorkList->head;
	simplifyWorkList = simplifyWorkList->tail;	
	nodeInfo info = G_nodeInfo(n);
	push(n, &selectStack);
	for(G_nodeList m=Adjacent(n);m;m=m->tail){
		DecrementDegree(m->head);
	}
}

static bool CoalesceBranch3(G_node u, G_node v){
	if(G_inNodeList(u, precolored)){
		bool pass = TRUE;
		for(G_nodeList nl=Adjacent(v);nl;nl=nl->tail){
			G_node t = nl->head;
			if(!OK(t,u)){
				pass = FALSE;
				break;
			}
		}
		if(pass) return TRUE;
	}
	else{
		G_nodeList nodes = L_union(Adjacent(u),Adjacent(v));
		int cnt = 0;
		for(;nodes;nodes=nodes->tail){
			G_node n = nodes->head;
			nodeInfo info = G_nodeInfo(n);
			if(info->degree >= K) cnt += 1;
		}
		if(cnt < K) return TRUE;
	}
	return FALSE;
}

static void Coalesce(){
	Live_moveList p = Live_MoveList(worklistMoves->src,worklistMoves->dst,NULL);
	worklistMoves = worklistMoves->tail;
	G_node src = GetAlias(p->src);
	G_node dst = GetAlias(p->dst);

	G_node u,v;
	if(G_inNodeList(src, precolored)){
		u = src; v = dst;
	}
	else{
		u = dst; v = src;
	}
	
	if(u == v){
		coalescedMoves = Live_MoveList(p->src, p->dst, coalescedMoves);
		AddWorkList(u);
	}
	else if(G_inNodeList(v, precolored) || G_inNodeList(u, G_adj(v))){
		constrainedMoves = Live_MoveList(p->src, p->dst, constrainedMoves);
		AddWorkList(u);
		AddWorkList(v);
	}
	else if(CoalesceBranch3(u, v)){
		coalescedMoves = Live_MoveList(p->src, p->dst, coalescedMoves);
		Combine(u, v);
		AddWorkList(u);
	}
	else{
		activeMoves = Live_MoveList(p->src, p->dst, activeMoves);
	}
}
static void Freeze(){
	G_node node = freezeWorkList->head;
	freezeWorkList = freezeWorkList->tail;
	simplifyWorkList = G_NodeList(node, simplifyWorkList);
	FreezeMoves(node);
}
static void SelectSpill(){
	// select 1st node in spillWorkList to spill
	G_node node = spillWorkList->head;
	spillWorkList = spillWorkList->tail;
	simplifyWorkList = G_NodeList(node, simplifyWorkList);
}
static void AssignColor(){
	COL_init();
	for(G_nodeList nl=selectStack;nl;nl=nl->tail){
		G_node node = nl->head;

		Temp_tempList okColors = NULL;
		for(Temp_tempList r =F_register();r;r=r->tail){
			okColors = Temp_TempList(r->head,okColors);
		}
		
		for(G_nodeList adj=G_adj(node);adj;adj=adj->tail){
			if(G_inNodeList(GetAlias(adj->head), L_union(precolored, coloredNode))){
				okColors = COL_remove(GetAlias(adj->head), okColors);
			}
		}

		if(!okColors){
			spilledNode = G_NodeList(node, spilledNode);
		}
		else{
			COL_assignColor(node, okColors);
			coloredNode = G_NodeList(node, coloredNode);
		}
	}

	for(G_nodeList nl=coalescedNodes;nl;nl=nl->tail){
		G_node node = nl->head;
		COL_assignCoalesce(node,GetAlias(node));
	}
}

AS_instrList RewriteProgram(F_frame f, AS_instrList il, G_nodeList spills){
	TAB_table tab = TAB_empty();
	Temp_tempList targets = NULL;

	// alloc temps for each spillnode
	G_nodeList nl=spills;
	while(nl){
		Temp_temp t = Live_gtemp(nl->head);
		targets = Temp_TempList(t, targets);
		TAB_enter(tab, t, F_allocLocal(f, TRUE));
		nl=nl->tail;
	}

	// traverse instlist
	int flen = F_length(f) * F_wordsize;
	AS_instrList ret = NULL;
	for(AS_instrList p=il;p;p=p->tail){
		AS_instr ins = p->head;
		switch(ins->kind){
			case I_LABEL:{
				ret = AS_splice(ret, AS_InstrList(ins,NULL));
				break;
			}
			case I_MOVE:
			case I_OPER:{
				Temp_tempList dst = ins->u.OPER.dst;
				Temp_tempList src = ins->u.OPER.src;
				AS_instrList th_inst = AS_InstrList(ins, NULL);
				// newil = ins;
				
				// add LOAD for spill
				while(src){
					Temp_temp t = src->head;
					if(Temp_exist(targets, t)){
						Temp_temp n = Temp_newtemp();
						Temp_replace(t, n, src);
						F_access acc = TAB_look(tab, t);
						int off = F_getFrameOff(acc);
						char mov[100];
						sprintf(mov, "movq %d(`s0), `d0",flen+off);
						AS_instr i = AS_Move(String(mov),Temp_TempList(n,NULL),Temp_TempList(F_SP(),NULL));
						th_inst = AS_splice(AS_InstrList(i,NULL),th_inst);
					}
					src = src->tail;
				}

				// add STORE for spill
				AS_instrList store = NULL;
				while(dst){
					Temp_temp t = dst->head;
					if(Temp_exist(targets, t)){
						Temp_temp n = Temp_newtemp();
						Temp_replace(t, n, dst);
						F_access acc = TAB_look(tab, t);
						int off = F_getFrameOff(acc);
						char mov[100];
						sprintf(mov, "movq `s0, %d(`s1)",flen+off);
						AS_instr i = AS_Move(String(mov),NULL,Temp_TempList(n,Temp_TempList(F_SP(),NULL)));
						th_inst = AS_splice(th_inst,AS_InstrList(i,NULL));       
					}
					dst = dst->tail;
				}

				// emit
				ret = AS_splice(ret, th_inst);
				break;
			}
		}
	}
	return ret;

}

struct RA_result RA_regAlloc(F_frame f, AS_instrList il) {
	init();

	G_graph fg = FG_AssemFlowGraph(il); 

	struct Live_graph lg = Live_liveness(fg); 

	worklistMoves = lg.moves;
	MakeWorkList(lg.graph);
		
	while(!!simplifyWorkList || !!worklistMoves || !!freezeWorkList || !!spillWorkList){
		if(simplifyWorkList)
			Simplify();
		else if(worklistMoves)
			Coalesce();
		else if(freezeWorkList)
			Freeze();
		else if(spillWorkList)
			SelectSpill();
	}
		
	AssignColor();

	if(spilledNode){
		AS_instrList nil = RewriteProgram(f, il, spilledNode);
		return RA_regAlloc(f, nil);
	}

	
	// delete src==dst move
	Temp_map map = Temp_layerMap(COL_map(),Temp_layerMap(F_tempMap, Temp_name()));
	AS_instrList p = il;
	AS_instrList last = NULL;
	for(;p;p=p->tail){
		AS_instr ins = p->head;
		if(ins->kind == I_MOVE){
			Temp_tempList dst = ins->u.MOVE.dst;
			Temp_tempList src = ins->u.MOVE.src;
			string ass = ins->u.MOVE.assem;				
			if(strstr(ass,"movq `s0, `d0")){
				string s = Temp_look(map, src->head);
				string d = Temp_look(map, dst->head);
				if(!strcmp(s,d)){
					last->tail = p->tail;  
					continue;          
				}          
			}
		}
		last = p;
	}

	struct RA_result ret;
	ret.coloring = COL_map();
	ret.il=il;

	return ret;
}
