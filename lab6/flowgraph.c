#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "util.h"
#include "symbol.h"
#include "temp.h"
#include "tree.h"
#include "absyn.h"
#include "assem.h"
#include "frame.h"
#include "graph.h"
#include "flowgraph.h"
#include "errormsg.h"
#include "table.h"

Temp_tempList FG_def(G_node n) {
	//your code here.
	AS_instr ins = G_nodeInfo(n);
	switch(ins->kind){
		case I_OPER:
			return ins->u.OPER.dst;
		case I_LABEL:
			assert(0);
		case I_MOVE:
			return ins->u.MOVE.dst;
	}
}

Temp_tempList FG_use(G_node n) {
	//your code here
	AS_instr ins = G_nodeInfo(n);
	switch(ins->kind){
		case I_OPER:
			return ins->u.OPER.src;
		case I_LABEL:
			assert(0);
		case I_MOVE:
			return ins->u.MOVE.src;
	}
}

bool FG_isMove(G_node n) {
	//your code here.
	AS_instr ins = G_nodeInfo(n);
	return ins->kind == I_MOVE && strstr(ins->u.MOVE.assem,"movq `s0, `d0");
}

//helper 
typedef struct labelNode_ *labelNode;
struct labelNode_{
	Temp_label label;
	AS_targets targets;
	G_node node;
};
labelNode LabelNode( G_node n, Temp_label lab, AS_targets ts){
	labelNode i = checked_malloc(sizeof(*i));
	i->label = lab;
	i->node = n;
	i->targets = ts;
	return i;
}

typedef struct labelNodeList_ *labelNodeList;
struct labelNodeList_{
	labelNode head;
	labelNodeList tail;
};
labelNodeList LabelNodeList(labelNode head, labelNodeList tail){
	labelNodeList l = checked_malloc(sizeof(*l));
	l->head = head;
	l->tail = tail;
	return l;
}

G_graph FG_AssemFlowGraph(AS_instrList il) {
	//your code here.
	G_graph g = G_Graph();

	labelNodeList label_list = NULL, jump_list = NULL;

	bool prevLab = FALSE;
	Temp_labelList lab = NULL;
	G_node prevNode = NULL;

	for(AS_instrList ls=il; ls; ls=ls->tail){
		AS_instr ins = ls->head;
		switch(ins->kind){
			case I_OPER:{
				G_node node = G_Node(g, ins);
				if(prevNode){
					G_addEdge(prevNode, node);
				}
				if(prevLab){
					for(;lab;lab=lab->tail)
						label_list = LabelNodeList(LabelNode(node, lab->head, NULL),label_list);
					prevLab = FALSE;
				}

				prevNode = node;
				if(ins->u.OPER.jumps){
					if(strstr(ins->u.OPER.assem, "jmp"))
						prevNode = NULL;
					jump_list = LabelNodeList(LabelNode(node, NULL, ins->u.OPER.jumps), jump_list);
				}
				break;
			}
			case I_LABEL:{
				prevLab = TRUE;
				lab = Temp_LabelList(ins->u.LABEL.label, lab); 
				break;
			}
			case I_MOVE:{
				Temp_tempList dst = ins->u.MOVE.dst;
				Temp_tempList src = ins->u.MOVE.src;
				string ass = ins->u.MOVE.assem;				

				G_node node = G_Node(g, ins);
				if(prevNode){
					G_addEdge(prevNode, node);
				}
				if(prevLab){
					for(;lab;lab=lab->tail)
						label_list = LabelNodeList(LabelNode(node, lab->head, NULL),label_list);
					prevLab = FALSE;
				}

				prevNode = node;
				break;
			}
			
		}
	}

	// add jump edges
	for(labelNodeList p=jump_list;p;p=p->tail){
		Temp_labelList pln;
		for(pln = p->head->targets->labels; pln; pln=pln->tail){
			Temp_label lab = pln->head;
			
			// label => node
			G_node succ = NULL;
			for(labelNodeList p=label_list; p; p=p->tail){
				Temp_label l = p->head->label;
				if(l == lab)
					succ = p->head->node;
			}

			G_addEdge(p->head->node, succ);
		}
	}
	return g;
}
