// Data categorization

#include "p4-queue-adt.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void print_queue(struct QUEUE *q) {
	int *dataptr;
	if (q) {
		while(!is_queue_empty(q)) {
			bool success = dequeue(q, (void *)&dataptr);
			if (success) {
				printf("%3d ", *dataptr);
			}
		}
		printf("\n");
	}
}


int main() {
	struct QUEUE *q = queue_init();

	int *x = malloc(sizeof(int));
	*x = 1;
	enqueue(q, x);

	int *y = malloc(sizeof(int));
	*y = 328;
	enqueue(q, y);
	
	dequeue(q, (void *)&x);
	printf("what was removed: %3d\n", *x);

	printf("what is in y: %3d\n", *y);

	printf("queue after removing\n");
	print_queue(q);

	free(x);
	free(y);

	free_queue(q);
	return 0;
}
