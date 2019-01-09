#include <stdio.h>
#include <string.h>

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
#include "table.h"

static Temp_map coloring = NULL;
Temp_map COL_map(){	
	if(!coloring){
		coloring = Temp_empty();
	}
	return coloring;
}

void COL_init(){
	coloring = NULL;
	COL_map();
}

Temp_tempList COL_remove(G_node t, Temp_tempList l){
	Temp_temp c = Live_gtemp(t);
	Temp_map map = Temp_layerMap(coloring, F_tempMap);
	string color = Temp_look(map, c);
	Temp_tempList last = NULL;
	for(Temp_tempList p=l;p;p=p->tail){
		string i = Temp_look(map, p->head);
		if(!strcmp(i, color)){
			if(last){
				last->tail = p->tail;
			}
			else{
				l = l->tail;
			}
			break;
		}
		last = p;
	}
	return l;
}

void COL_assignColor(G_node t, Temp_tempList colors){
	string color = Temp_look(F_tempMap, colors->head);
	assert(color);
	Temp_temp rr = Live_gtemp(t);
	Temp_enter(coloring, rr, color);
}

void COL_assignCoalesce(G_node node,G_node alia){
	Temp_map map = Temp_layerMap(coloring, F_tempMap);
	string color = Temp_look(map, Live_gtemp(alia));
	assert(color);
	Temp_enter(coloring, Live_gtemp(node), color);
}

struct COL_result COL_color(G_graph ig, Temp_map initial, Temp_tempList regs, Live_moveList moves)
{
	//your code here.
	struct COL_result ret;
	return ret;
}
