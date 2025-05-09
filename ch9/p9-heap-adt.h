#ifndef _P9_HEAP_ADT_H
#define _P9_HEAP_ADT_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct heap {
	void **heaparr;
	int last;
	int size;
	int maxsize;
	int (*cmp) (void *arg1, void *arg2);
};


struct heap *heap_init(int maxsize,
		int (*cmp) (void *arg1, void *arg2)) {
	struct heap *h = (struct heap *) malloc(sizeof(struct heap));
	if (!h) {
		printf("Error: Failed to create Heap\n");
		return NULL;
	}

	h->last = -1;
	h->size = 0;
	h->cmp = cmp;
	h->maxsize = (int) pow(2, ceil(log2(maxsize))) - 1;
	h->heaparr = (void *) calloc(h->maxsize, sizeof(void *));

	return h;
}


int _reheapup(struct heap *h, int childloc) {
	void **heaparr;
	int parent;
	void *hold;

	int nswap = 0;

	if (childloc) {
		heaparr = h->heaparr;
		parent = (childloc - 1) / 2;
		if (h->cmp(heaparr[childloc], heaparr[parent]) > 0) {
			hold = heaparr[parent];
			heaparr[parent] = heaparr[childloc];
			heaparr[childloc] = hold;
			++nswap;
			nswap += _reheapup(h, parent);
		}
	}

	return nswap;
}


bool heap_insert(struct heap *h, void *dataptr, int *swaps) {
	if (h->size == 0) {
		h->size = 1;
		h->last = 0;
		h->heaparr[h->last] = dataptr;
		return true;
	}

	if (h->last == h->maxsize - 1)
		return false;

	h->last += 1;
	h->size += 1;
	h->heaparr[h->last] = dataptr;
	*swaps += _reheapup(h, h->last);

	return true;
}


int _reheapdown(struct heap *h, int root) {
	int last = h->last;
	int leftdataloc = root * 2 + 1;
	int nswap = 0;

	if (leftdataloc <= last) {
		void *leftdata = h->heaparr[leftdataloc];
		int rightdataloc = root * 2 + 2;

		void *rightdata;
		if (rightdataloc <= last) {
			rightdata = h->heaparr[rightdataloc];
		} else {
			rightdata = NULL;
		}

		bool noright = !rightdata;
		bool is_left_larger = h->cmp(leftdata, rightdata) > 0;
		is_left_larger = noright || is_left_larger;

		int largeloc;
		if (is_left_larger) {
			largeloc = leftdataloc;
		} else {
			largeloc = rightdataloc;
		}

		bool is_root_larger = h->cmp(h->heaparr[root],
				h->heaparr[largeloc]) < 0;
		if (is_root_larger) {
			void *hold = h->heaparr[root];
			h->heaparr[root] = h->heaparr[largeloc];
			h->heaparr[largeloc] = hold;
			++nswap;
			nswap += _reheapdown(h, largeloc);
		}
	}

	return nswap;
}


bool build_heap_faster(struct heap *h, int *count) {
	int last_subtree_loc = h->size / 2 - 1;

	for (int i = last_subtree_loc; i >= 0; i--) {
		*count += _reheapdown(h, i);
	}

	return true;
}


void print_heap(struct heap *h, void (*process) (void *cust)) {
	for (int i = 0; i < h->size; i++) {
		process(h->heaparr[i]);
	}
	printf("\n");
}


bool heap_delete(struct heap *h, void **dataout_ptr, int *swaps) {
	if (h->size == 0)
		return false;

	*dataout_ptr = h->heaparr[0];
	h->heaparr[0] = h->heaparr[h->last];
	h->last -= 1;
	h->size -= 1;
	*swaps += _reheapdown(h, 0);

	return true;
}


void free_heap(struct heap *h) {
	free(h->heaparr);
	free(h);
}


#endif
