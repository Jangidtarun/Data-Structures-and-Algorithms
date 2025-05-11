#ifndef _P11_GRAPH_ADT_H
#define _P11_GRAPH_ADT_H


#include <stdbool.h>
#include "../ch4/p4-queue-adt.h"
#include "../ch3/p3-stack-adt.h"


struct vertex {
	struct vertex *pnext_vertex;
	void *dataptr;
	int indeg;
	int outdeg;
	bool processed;
	struct arc *parc;
};


struct graph {
	int count;
	struct vertex *first;
	int (*cmp) (void *arg1, void *arg2);
};


struct arc {
	struct vertex *destination;
	struct arc *pnext_arc;
};


struct graph *graph_init(int (*cmp) (void *arg1, void *arg2)) {
	struct graph *g = malloc(sizeof(struct graph));
	if (g) {
		g->count = 0;
		g->first = NULL;
		g->cmp = cmp;
	}

	return g;
}


bool graph_insert_vertex(struct graph *g, void *dataptr) {
	struct vertex *newptr = malloc(sizeof(struct vertex));
	if (!newptr) {
		return false;
	}

	newptr->pnext_vertex = NULL;
	newptr->dataptr = dataptr;
	newptr->indeg = 0;
	newptr->outdeg = 0;
	newptr->processed = false;
	newptr->parc = NULL;

	if (!g->first)
		g->first = newptr;
	else {
		struct vertex *predptr = NULL;
		struct vertex *locptr = g->first;
		while (locptr && (g->cmp(dataptr, locptr->dataptr) > 0)) {
			predptr = locptr;
			locptr = locptr->pnext_vertex;
		}

		if (!predptr) {
			g->first = newptr;
		} else {
			predptr->pnext_vertex = newptr;
		}

		newptr->pnext_vertex = locptr;
	}

	return true;
}


int graph_delete_vertex(struct graph *g, void *dltptr) {
	if (!g->first)
		return -2;

	struct vertex *predptr = NULL;
	struct vertex *walkptr = g->first;
	while (walkptr && (g->cmp(dltptr, walkptr->dataptr) > 0)) {
		predptr = walkptr;
		walkptr = walkptr->pnext_vertex;
	}

	if (!walkptr || g->cmp(dltptr, walkptr->dataptr) != 0)
		return -2;

	if (walkptr->indeg > 0 || walkptr->outdeg > 0)
		return -1;

	if (!predptr)
		g->first = walkptr->pnext_vertex;
	else {
		predptr->pnext_vertex = walkptr->pnext_vertex;
	}

	g->count -= 1;
	free(walkptr);
	return 1;
}


#endif
