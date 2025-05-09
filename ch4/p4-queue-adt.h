#ifndef _P4_QUEUE_ADT_H
#define _P4_QUEUE_ADT_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct QUEUE_NODE {
	void *dataptr;
	struct QUEUE_NODE *next;
};


struct QUEUE {
	int count;
	struct QUEUE_NODE *front;
	struct QUEUE_NODE *rear;
};


struct QUEUE *queue_init() {
	struct QUEUE *q = malloc(sizeof(struct QUEUE));
	if (!q) {
		printf("Error: Failed to initialize the queue\n");
		exit(101);
	}

	q->count = 0;
	q->front = NULL;
	q->rear = NULL;

	return q;
}


void free_queue(struct QUEUE *q) {
	if (q) {
		while (q->front != NULL) {
			free(q->front->dataptr);
			struct QUEUE_NODE *dltptr = q->front;
			q->front = q->front->next;
			free(dltptr);
		}
		free(q);
	}
}


bool enqueue(struct QUEUE *q, void *dataptr) {
	struct QUEUE_NODE *newptr = malloc(sizeof(struct QUEUE_NODE));
	if (!newptr) {
		return false;
	}

	newptr->dataptr = dataptr;
	newptr->next = NULL;

	if (q->count == 0) {
		q->front = q->rear = newptr;
	} else {
		q->rear->next = newptr;
	}

	q->count += 1;
	return true;
}


bool dequeue(struct QUEUE *q, void **dataptr) {
	if (q->count == 0)
		return false;

	*dataptr = q->front->dataptr;
	struct QUEUE_NODE *dltptr = q->front;

	if (q->count == 1) {
		q->rear = q->front = NULL;
	} else {
		q->front = q->front->next;
	}

	q->count -= 1;
	free(dltptr);

	return true;
}


bool queuefront(struct QUEUE *q, void **dataptr) {
	if (q->count == 0)
		return false;
	
	*dataptr = q->front->dataptr;
	return true;
}


bool queuerear(struct QUEUE *q, void **dataptr) {
	if (q->count == 0)
		return false;

	*dataptr = q->rear->dataptr;
	return true;
}


bool is_queue_empty(struct QUEUE *q) {
	return q->count == 0;
}


#endif
