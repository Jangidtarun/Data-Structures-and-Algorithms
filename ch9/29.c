#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "p9-heap-adt.h"

#define _T100 100
#define _T200 200
#define _T500 500
#define _T1000 1000
#define _T2000 2000

#define _MAX 9999


int *generate_random_arr(int size) {
	int *arr = malloc(sizeof(int)*size);

	srand(time(NULL));

	for (int i = 0; i < size; i++) {
		arr[i] = rand() % _MAX;
	}

	return arr;
}


void print_arr(int *arr, int size) {
	printf("\n");
	for (int i = 0; i < size; i++) {
		printf("%4d\t", arr[i]);
	}
	printf("\n");
}


int cmp_int(void *arg1, void *arg2) {
	int a = *(int *)arg1;
	int b = *(int *)arg2;

	if (a < b)
		return -1;
	else if (a > b) 
		return +1;
	return 0;
}


int main() {
	printf("Select arr size\n");

	printf("[0]\t100\n");
	printf("[1]\t200\n");
	printf("[2]\t500\n");
	printf("[3]\t1000\n");
	printf("[4]\t2000\n\n");

	int option = 0;
	scanf("%d", &option);
	
	int current_size = _T100;
	switch (option) {
		case 0:
			current_size = _T100;
			break;
		case 1:
			current_size = _T200;
			break;
		case 2:
			current_size = _T500;
			break;
		case 3:
			current_size = _T1000;
			break;
		case 4:
			current_size = _T2000;
			break;
		default:
			printf("Invalid option moving along with default size 100\n");
			break;
	}

	int *arr = generate_random_arr(current_size);
	int moves = 0;
	
	struct heap *h = heap_init(current_size, cmp_int);
/*
	h->heaparr = (void **)&arr;
	bool success = build_heap_faster(h, &moves);
	if (success) {
		printf("successfully built heap\n");
	}
*/
	for (int i = 0; i < current_size; i++) {
		bool success = heap_insert(h, &arr[i], &moves);
	}

	printf("moves: %5d\n", moves);
	print_heap(h);

	free(arr);
	// free_heap(h);
	return 0;
}
