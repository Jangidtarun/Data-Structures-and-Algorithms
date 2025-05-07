#include "p9-heap-adt.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define maxsize 20

struct qnode {
	int priority;
	int serial;
	char data;
};


int cmp_qnode(void *n1, void *n2) {
	struct qnode c1 = *(struct qnode *)n1;
	struct qnode c2 = *(struct qnode *)n2;

	if (c1.serial < c2.serial)
		return -1;
	else if (c1.serial > c2.serial)
		return +1;
	return 0;
}


char menu() {
	char option;
	bool valid = true;

	printf("\n--------------------------------\n");
	printf("e -> insert data\n");
	printf("d -> delete data\n");
	printf("q -> quit\n");
	printf("\n--------------------------------\n");

	while (valid) {
		scanf(" %c", &option);
		option = tolower(option);
		switch (option) {
			case 'e':
			case 'd':
			case 'q':
				valid = false;
				break;
			default:
				printf("Invalid option. Select again: \n");
				valid = true;
				break;
		}
	}

	return option;
}


struct qnode *get_data() {
	struct qnode *d = (struct qnode *) malloc(sizeof(struct qnode));
	if (!d) {
		printf("Not enough memory for another node\n");
		exit(200);
	}

	printf("priority: ");
	scanf("%d", &d->priority);
	printf("data: ");
	scanf(" %c", &d->data);
	
	return d;
}


int generate_serial(int priority, int num_nodes) {
	return priority * 1000 + num_nodes;
}


void process_pq(struct heap *pq) {
	struct qnode *d;
	bool res;
	char option;
	int num_nodes = 0;

	while (option != 'q') {
		option = menu();
		switch (option) {
			case 'e':
				d = get_data();
				++num_nodes;
				d->serial = generate_serial(d->priority, num_nodes);

				res = heap_insert(pq, d);
				if (!res) {
					printf("Error: insertion failed\n");
					exit(101);
				}
				break;
			case 'd':
				res = heap_delete(pq, (void **)&d);
				if (!res) {
					printf("Error: deletion failed\n");
				} else {
					printf("Node %2d-%c deleted\n", d->priority, d->data);
					--num_nodes;
				}
		}
	}
}

int main() {
	struct heap *pq = heap_init(maxsize, cmp_qnode);

	printf("Enter the data one at a time\n");
	process_pq(pq);

	free_heap(pq);

	return 0;
}











	
