#include <stdio.h>

void selection_sort(int arr[], int size) {
	if (size == 0)
		return;

	int first_unsorted_loc = 0;

	while (first_unsorted_loc + 1 < size) {
		int min_val_loc = first_unsorted_loc;
		for (int i = first_unsorted_loc; i < size; i++) {
			if (arr[min_val_loc] > arr[i]) {
				min_val_loc = i;
			}
		}

		int tmp = arr[min_val_loc];
		arr[min_val_loc] = arr[first_unsorted_loc];
		arr[first_unsorted_loc] = tmp;

		first_unsorted_loc += 1;
	}
}


void print_arr(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%2d ", arr[i]);
	}
	printf("\n");
}


int main() {
	int arr[] = {93, 74, 90, 37, 57, 61, 30, 14, 19, 56, 24};
	int size = sizeof(arr) / sizeof(int);

	print_arr(arr, size);
	selection_sort(arr, size);
	print_arr(arr, size);

	return 0;
}
