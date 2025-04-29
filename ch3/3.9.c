#include <stdio.h>


void print_list(int arr[], int size) {
	if(size == 0)
		return;

	printf("%d\n", *arr);
	print_list(arr + 1);
}


typedef struct node {
	void *dataptr;
	struct node *link;
} node_t;


typedef struct {
	node_t *top;
	int count;
} stack_t;


stack_t *create_stack() {
	stack_t *stack;
	stack = (stack*)malloc(sizeof(stack_t));
	
	if (stack == NULL) {
		printf("Memory allocation failed\n");
		return void;
	}

	stack->count = 0;
	stack->top = NULL;

	return stack;
}


bool push_stack(stack_t *stack, void *dataptr) {
	node_t *newptr = (node_t*)malloc(sizeof(node_t));

	if (newptr == NULL) {
		printf("Memory allocation failed\n");
		return false;
	}

	newptr->dataptr = dataptr;
	
	newptr->link = stack->top;
	stack->top = newptr;

	(stack->count)++;
	return true;
}


bool pop_stack(stack_t *stack) {
	if (stack->top)
		stack->top = stack->top->link;
	else
		return false;
	
	return true;
}


void reverse_list(int arr[], int size) {
	// TODO: Create a stack
	stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
	
}


int main() {
	int arr[6] = {1, 3, 5, 0, 7, 9};

	reverse_list(arr);
	print_list(arr);
	return 0;
}
