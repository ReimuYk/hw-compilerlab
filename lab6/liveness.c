#include <stdio.h>
#include "util.h"
#include "symbol.h"
#include "temp.h"
#include "tree.h"
#include "absyn.h"
#include "assem.h"
#include "frame.h"
#include "graph.h"
#include "flowgraph.h"
#include "liveness.h"
#include "table.h"


static G_graph conflict_gragh;
static TAB_table table_live;
static TAB_table table_tmp2node;
static Live_moveList move_list;

// struct constructor
liveInfo LiveInfo(Temp_tempList in, Temp_tempList out){
	liveInfo i = checked_malloc(sizeof(*i));
	i->in = in;
	i->out = out;
	return i;
}

nodeInfo NodeInfo(Temp_temp t, int d){
	nodeInfo i = checked_malloc(sizeof(*i));
	i->degree = d;
	i->reg = t;
	// i->stat = s;
	i->alias = NULL;
	return i;
}

Live_moveList Live_MoveList(G_node src, G_node dst, Live_moveList tail) {
	Live_moveList lm = (Live_moveList) checked_malloc(sizeof(*lm));
	lm->src = src;
	lm->dst = dst;
	lm->tail = tail;
	return lm;
}

Temp_temp Live_gtemp(G_node n) {
	//your code here.
	nodeInfo p = G_nodeInfo(n);
	Temp_temp t = p->reg;
	return t;
}

// helpers
Temp_tempList SetUnion(Temp_tempList A, Temp_tempList B){
	// return A U B
	Temp_tempList ret = A;
	while(B){
		Temp_temp t = B->head;
		if(!Temp_exist(A, t)){
			ret = Temp_TempList(t, ret);
		}
		B = B->tail;
	}
	return ret;
}

Temp_tempList SetMinus(Temp_tempList A, Temp_tempList B){
	// return A - B
	Temp_tempList ret = NULL;
	while(A){
		Temp_temp tt = A->head;
		if(!Temp_exist(B, tt)){
			ret = Temp_TempList(tt, ret);
		}
		A=A->tail;
	}
	return ret;
}

bool SetEqual(Temp_tempList A, Temp_tempList B){
	// return A == B 
	if(SetMinus(A,B)==NULL && SetMinus(B,A)==NULL){
		return TRUE;
	}
	return FALSE;
}

// procedure functions
static G_nodeList EmptyConflictGraph(G_graph flow){
	G_nodeList ret = NULL;
	for(G_nodeList nodes=G_nodes(flow);nodes;nodes=nodes->tail){
		G_node fnode = nodes->head;

		Temp_tempList tp;
		tp = FG_def(fnode);
		while(tp){
			Temp_temp t = tp->head;
			if(!TAB_look(table_tmp2node,t)){
				G_node cfnode = G_Node(conflict_gragh,NodeInfo(t,0));
				TAB_enter(table_tmp2node, t, cfnode);
			}
			tp=tp->tail;
		}

		tp = FG_use(fnode);
		while(tp){
			Temp_temp t = tp->head;
			if(!TAB_look(table_tmp2node,t)){
				G_node cfnode = G_Node(conflict_gragh,NodeInfo(t,0));
				TAB_enter(table_tmp2node, t, cfnode);
			}
			tp=tp->tail;
		}

		TAB_enter(table_live, fnode, LiveInfo(NULL, NULL));
		ret = G_NodeList(fnode, ret);
	}
	return ret;
}



static void updateInAndOut(G_nodeList conflict_nodelist){
	bool balanced = FALSE; // until not change
	while(!balanced){
		balanced = TRUE;
		/* 
			for each node
			1. in[s] = use[s] U (out[s] - def[s])
			2. out[s] = U(every succ's in)
		*/
		G_nodeList np = conflict_nodelist;
		while(np){
			G_node fnode = np->head;

			liveInfo old = TAB_look(table_live, fnode);

			Temp_tempList out = old->out;
			G_nodeList sp=G_succ(fnode);
			while(sp){
				G_node succ = sp->head;
				liveInfo tmp = TAB_look(table_live, succ);
				out = SetUnion(out,tmp->in);
				sp=sp->tail;
			}

			Temp_tempList in = SetUnion(FG_use(fnode), SetMinus(out, FG_def(fnode)));
			
			if(!SetEqual(in, old->in) || !SetEqual(out, old->out)){
				balanced = FALSE;
			}

			TAB_enter(table_live, fnode, LiveInfo(in, out));
			np=np->tail;
		}
	}
}
static void buildConflictEdge(G_nodeList conflict_nodelist){
	G_nodeList np=conflict_nodelist;
	while(np){
		G_node fnode = np->head;

		liveInfo info = TAB_look(table_live, fnode);
		Temp_tempList live = info->out;

		//move
		if(FG_isMove(fnode)){
			live = SetMinus(live, FG_use(fnode));

			Temp_temp dst = FG_def(fnode)->head;
			G_node d = TAB_look(table_tmp2node, dst);
			Temp_temp src = FG_use(fnode)->head;
			G_node s = TAB_look(table_tmp2node, src);

			move_list = Live_MoveList(s, d, move_list);
		}

		//add conflicts 
		Temp_tempList def = FG_def(fnode);
		live = SetUnion(live, def);
		for(Temp_tempList p1=def;p1;p1=p1->tail){
			G_node cf1 = TAB_look(table_tmp2node, p1->head);
			for(Temp_tempList p2=live;p2;p2=p2->tail){
				G_node cf2 = TAB_look(table_tmp2node, p2->head);
				if(G_goesTo(cf2, cf1) || cf1 == cf2)continue;
				G_addEdge(cf1, cf2);
			}
		}
		np=np->tail;
	}
}

struct Live_graph Live_liveness(G_graph flow) {
	//your code here.
	struct Live_graph lg;

	conflict_gragh = G_Graph();
	table_live = TAB_empty();
	table_tmp2node = TAB_empty();
	move_list = NULL;	

	G_nodeList conflict_nodelist = EmptyConflictGraph(flow);
	
	updateInAndOut(conflict_nodelist);
	
	buildConflictEdge(conflict_nodelist);
	
	lg.graph = conflict_gragh;
	lg.moves = move_list;

	return lg;
}


