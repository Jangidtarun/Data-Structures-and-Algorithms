#ifndef _P3_STACK_ADT_H
#define _P3_STACK_ADT_H

#include <stdlib.h>
#include <stdbool.h>

struct stack_node {
	void *dataptr;
	struct stack_node *link;
};


struct stack {
	int count;
	struct stack_node *top;
};


struct stack *stack_init() {
	struct stack *this = (struct stack *) malloc(sizeof(struct stack));
	if (!this) {
		printf("Error: Failed to initialize stack\n");
		printf("Not enough memory to initialize\n");
		return NULL;
	}

	this->count = 0;
	this->top = NULL;
	return this;
}


struct stack_node *make_stack_node(void *dataptr) {
	struct stack_node *newnode = malloc(sizeof(struct stack_node));
	if (!newnode) {
		printf("Error: Failed to create a new node\n");
		printf("Not enough memory to create a node\n");
		return NULL;
	}

	newnode->dataptr = dataptr;
	newnode->link = NULL;
}


bool push_stack(struct stack *this, void *dataptr) {
	struct stack_node *newnode = make_stack_node(dataptr);
	if (!newnode) {
		return false;
	}

	newnode->link = this->top;
	this->top = newnode;
	this->count += 1;

	return true;
}


void *pop_stack(struct stack *this) {
	if (this->count == 0) {
	   return NULL;
	} 

	void *dataptr;
	struct stack_node *tmp = this->top;
	dataptr = tmp->dataptr;
	this->top = tmp->link;

	free(tmp);
	this->count -= 1;

	return dataptr;
}


void *stack_top(struct stack *this) {
	if (this->count == 0) {
		return NULL;
	}

	return this->top->dataptr;
}


bool is_stack_empty(struct stack *this) {
	return this->count == 0;
}


struct stack *stack_destroy(struct stack *this) {
	if (this) {
		while (this->top != NULL) {
			free(this->top->dataptr);

			struct stack_node *tmp = this->top;
			this->top = this->top->link;
			free(tmp);
		}

		free(this);
	}

	return NULL;
}


/*
 * this free function only frees the memory allocated for the stack
 * structure and does nothing for the node structure, designed for the 
 * case when you want to retain the pointers from stack even after deleting 
 * the stack.
 */
void free_stack_nodata(struct stack *stk) {
	if (stk) {
		while (stk->top != NULL) {
			struct stack_node *tmp = stk->top;
			stk->top = stk->top->link;
			free(tmp);
		}
		free(stk);
	}
}



#endif
