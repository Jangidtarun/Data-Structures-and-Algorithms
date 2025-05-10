#ifndef _P11_GRAPH_ADT_H
#define _P11_GRAPH_ADT_H


#include <stdbool.h>
#include "../ch4/p4-queue-adt.h"
#include "../ch3/p3-stack-adt.h"


struct VERTEX {
	struct VERTEX *pnext_vertex;
	void *dataptr;
	int indegree;
	int outdegree;
	bool processed;
	struct ARC *parc;
};


struct GRAPH {
	int count;
	struct vertex *first;
	int (*cmp) (void *arg1, void *arg2);
};


struct ARC {
	struct vertex *destination;
	struct ARC *pnextarc;
};


struct GRAPH *graph_init(int (*cmp) (void *arg1, void *arg2)) {
	struct GRAPH *g = malloc(sizeof(struct GRAPH));
	if (g) {
		g->count = 0;
		g->first = NULL;
		g->cmp = cmp;
	}

	return g;
}


#endif
