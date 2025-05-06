#include <stdio.h>
#include "p3-stack-adt.h"

/*
 * read numbers one at a time
 * for now just read them from an array
 *
 * create a stack from that array
 * print and verify it
 */

int main() {
	printf("Reverse number list application.\n");

	int arr[] = {10, 20, 30, 40, 50, 25, 45, 35};

	struct stack *this = stack_init();
	for (int i = 0; i < sizeof(arr)/sizeof(int); i++) {
		int *data = malloc(sizeof(int));
		if (!data) {
			printf("Error: Failed to allocate dataptr\n");
		}

		*data = arr[i];
		bool success = push_stack(this, data);
		if (success) {
			printf("Successfully inserted %2d\n", arr[i]);
		}
	}


	// print stack
	struct stack_node *tmp = this->top;
	while (tmp) {
		printf("%2d\n", *(int *)(tmp->dataptr));
		tmp = tmp->link;
	}

	stack_destroy(this);
	return 0;
}
