#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "p9-heap-adt.h"

const int maxqueue = 20;

struct pq_node {
	int id;
	int priority;
	int serial;
};


int cmp_pq_node(void *n1, void *n2) {
	struct pq_node c1 = *(struct pq_node *)n1;
	struct pq_node c2 = *(struct pq_node *)n2;

	if (c1.serial < c2.serial)
		return -1;
	else if (c1.serial > c2.serial)
		return +1;
	return 0;
}


char menu() {
	char option;
	bool valid = true;

	printf("\n------------------------------------------------\n");
	printf(" e : Enter customer flight\n");
	printf(" d : Delete customer flight\n");
	printf(" q : Quit\n");
	printf("\n------------------------------------------------\n");

	while (valid) {
		scanf(" %c", &option);
		option = tolower(option);
		switch (option) {
			case 'e' :
			case 'd' :
			case 'q' :
				valid = false;
				break;

			default:
				printf("Invalid choice. Re enter: ");
				valid = true;
				break;
		}
	}
	return option;
}


struct pq_node *get_pq_node() {
	struct pq_node *c = (struct pq_node *) malloc(sizeof(struct pq_node));
	if (!c) {
		printf("Not enough memory for another customer\n");
		exit(200);
	}

	printf("Enter customer id: ");
	scanf("%d", &c->id);
	printf("Enter customer priority: ");
	scanf("%d", &c->priority);
	return c;
}


void process_pq(struct heap *pq) {
	struct pq_node *c;
	bool res;
	char option;
	int num_nodes = 0;

	while(option != 'q') {
		option = menu();
		switch (option) {
			case 'e':
				c = get_pq_node();
				++num_nodes;
				c->serial = c->priority * 1000 + (1000 - num_nodes);
				res = heap_insert(pq, c);
				if (!res) {
					printf("Error: Failed to insert into heap\n");
					exit(101);
				}
				break;
			case 'd':
				res = heap_delete(pq, (void **)&c);
				if (!res) {
					printf("Error: Customer not found\n");
				} else {
					printf("Customer %4d deleted\n", c->id);
					--num_nodes;
				}
		}
	}
}


int main() {
	struct heap *pq;
	printf("Begin priority queue demonstrations\n");

	pq = heap_init(maxqueue, cmp_pq_node);
	process_pq(pq);

	printf("End priority queue demonstration\n");
	return 0;
}
