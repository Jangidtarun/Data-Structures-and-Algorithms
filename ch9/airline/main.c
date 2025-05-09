#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "../p9-heap-adt.h"

#define MAX_BUFFER_SIZE 80
#define MAX_NAME_SIZE 50
#define FIELDS 4
#define MAX_PQ_SIZE 20


struct cust {
	char *name;
	int mileage;
	int years;
	int sequence;
	int priority;
};


int cmp_cust(void *arg1, void *arg2) {
	struct cust c1 = *(struct cust *)arg1;
	struct cust c2 = *(struct cust *)arg2;

	if (c1.priority < c2.priority) {
		return -1;
	} else if (c1.priority > c2.priority) {
		return +1;
	}
	return 0;
}


int get_priority(int mileage, int years, int sequence) {
	return mileage / 1000 + years - sequence;
}


void read_database_to_pq(FILE *db, struct heap *pq) {
	
	char buffer[MAX_BUFFER_SIZE];
	while (fgets(buffer, MAX_BUFFER_SIZE, db)) {
		char *token = strtok(buffer, ",\n");

		struct cust *tmp = (struct cust *) malloc(sizeof(struct cust));
		if (!tmp) {
			printf("Unable to read data\nMemory overflow\n");
			return;
		}

		tmp->name = strdup(token);

		token = strtok(NULL, ",\n");
		if (!token)
			tmp->mileage = 0;
		else
			tmp->mileage = atoi(token);

		token = strtok(NULL, ",\n");
		if (!token)
			tmp->years = 0;
		else
			tmp->years = atoi(token);

		token = strtok(NULL, ",\n");
		if (!token)
			tmp->sequence = INT_MAX;
		else
			tmp->sequence = atoi(token);

		tmp->priority = get_priority(tmp->mileage, tmp->years, tmp->sequence);

		int swaps = 0;
		bool success = heap_insert(pq, tmp, &swaps);
		if (!success) {
			printf("Unable to insert into heap\n");
			return;
		}
	}
}


void process(void *cust) {
	struct cust c = *(struct cust *)cust;
	printf("%s\t%d\n", c.name, c.priority);
}


void free_heap_airline(struct heap *h) {
	free(h->heaparr);
	free(h);
}


int main() {
	printf("Welcome to Q airline\n");

	char filename[] = "database.txt";
	FILE *airline_database = fopen(filename, "r");	
	if (!airline_database) {
		printf("Error: Failed to get the database\n");
		return 1;
	}

	struct heap *pq = heap_init(MAX_PQ_SIZE, cmp_cust);
	read_database_to_pq(airline_database, pq);

	printf("\nNAME\t\tPRIORITY\n");
	print_heap(pq, process);

	fclose(airline_database);
	free_heap_airline(pq);
	return 0;
}
