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
	short processed;
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
	newptr->processed = 0;
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


int graph_insert_arc(struct graph *g, void *from, void *to) {
	struct arc *newptr = malloc(sizeof(struct arc));
	if (!newptr) {
		return -1;
	}

	struct vertex *vert_from = g->first;
	while (vert_from && (g->cmp(from, vert_from->dataptr) > 0)) {
		vert_from = vert_from->pnext_vertex;
	}

	if (!vert_from || (g->cmp(from, vert_from->dataptr) != 0))
		return -2;

	struct vertex *vert_to = g->first;
	while (vert_to && (g->cmp(to, vert_to->dataptr) > 0)) {
		vert_to = vert_to->pnext_vertex;
	}

	if (!vert_to || (g->cmp(to, vert_to->dataptr) != ))
		return -3;

	vert_from->outdeg += 1;
	vert_to->indeg += 1;
	newptr->destination = vert_to;
	if (!vert_from->parc) {
		vert_from->parc = newptr;
		newptr->pnext_arc = NULL;
		return 1;
	}

	struct arc *arc_predptr = NULL;
	struct arc *arc_walkptr = vert_from->parc;
	while (arc_walkptr && 
			(g->cmp(to, arc_walkptr->destination->dataptr) >= 0)) {
		arc_predptr = arc_walkptr;
		arc_walkptr = arc_walkptr->pnext_arc;
	}

	if (!arc_predptr)
		vert_from->parc = newptr;
	else
		arc_predptr->pnext_arc = newptr;

	newptr->pnext_arc = arc_walkptr;
	return 1;
}


int graph_delete_arc(struct graph *g, void *from, void *to) {
	if (!g->first)
		return -2;

	struct vertex *vert_from = g->first;
	while (vert_from && (g->cmp(from, vert_from->dataptr) > 0))
		vert_from = vert_from->pnext_vertex;

	if (!vert_from || g->cmp(from, vert_from->dataptr) != 0)
		return -2;

	if (!vert_from->parc)
		return -3;

	struct arc *arc_preptr = NULL;
	struct arc *arc_walkptr = vert_from->parc;
	while (arc_walkptr && g->cmp(to, arc_walkptr->destination->dataptr) > 0) {
		arc_preptr = arc_walkptr;
		arc_walkptr = arc_walkptr->pnext_arc;
	}

	if (!arc_walkptr || g->cmp(to, arc_walkptr->destination->dataptr) != 0)
		return -3;

	struct vertex *vert_to = arc_walkptr->destination;

	vert_from->outdeg -= 1;
	vert_to->indeg -= 1;
	if (!arc_preptr)
		vert_from->parc = arc_walkptr->pnext_arc;
	else
		arc_preptr->pnext_arc = arc_walkptr->pnext_arc;

	free(arc_walkptr);
	return 1;
}


void graph_dfs(struct graph *g, void (*process) (void *dataptr)) {
	if (!g->first)
		return;

	struct vertex *walkptr = g->first;
	while (walkptr) {
		walkptr->processed = 0;
		walkptr = walkptr->pnext_vertex;
	}

	struct stack *s = stack_init();
	walkptr = g->first;
	while (walkptr) {
		if (walkptr->processed = 0) {
			bool success = push_stack(s, walkptr);
			if (!success) {
				printf("Stack overflow\n");
				exit(101);
			}

			walkptr->processed = 1;
		}

		while (!is_stack_empty(s)) {
			struct vertex *vertptr = pop_stack(s);
			process(vertptr->dataptr);
			vertptr->processed = 2;

			struct arc *arc_walkptr = vertptr->parc;
			while (arc_walkptr) {
				struct vertex *vert_to = arc_walkptr->destination;
				if (vert_to->processed == 0) {
					bool success = push_stack(s, vert_to);
					if (!success) {
						printf("\aStack overflow\a\n");
						exit(101);
					}

					vert_to->processed = 1;
				}
				arc_walkptr = arc_walkptr->pnext_arc;
			}
		}

		walkptr = walkptr->pnext_vertex;
	}

	free_stack(s);
}


#endif
