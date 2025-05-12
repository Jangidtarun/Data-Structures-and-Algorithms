#include <stdio.h>


void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}


void selection_sort(int arr[], int size) {
	if (size <= 1)
		return;

	int first_unsorted_loc = 0;

	while (first_unsorted_loc + 1 < size) {
		int min_val_loc = first_unsorted_loc;
		for (int i = first_unsorted_loc; i < size; i++) {
			if (arr[min_val_loc] > arr[i]) {
				min_val_loc = i;
			}
		}

		swap(&arr[min_val_loc], &arr[first_unsorted_loc]);
		first_unsorted_loc += 1;
	}
}


void print_arr(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%2d ", arr[i]);
	}
	printf("\n");
}


void max_heapify(int arr[], int size, int curr) {
	int left = curr * 2 + 1;
	int right = curr * 2 + 2;
	int largest = curr;

	if (left < size && arr[left] > arr[largest])
		largest = left;

	if (right < size && arr[right] > arr[largest])
		largest = right;

	if (largest != curr) {
		swap(&arr[curr], &arr[largest]);
		max_heapify(arr, size, largest);
	}
}

	
void build_max_heap(int arr[], int size) {
	for (int i = size / 2 - 1; i >= 0; i--)
		max_heapify(arr, size, i);
}
	

void heap_sort(int arr[], int size) {
	if (size <= 1)
		return;

	build_max_heap(arr, size);

	for (int i = size - 1; i > 0; i--) {
		swap(&arr[i], &arr[0]);
		max_heapify(arr, i, 0);
	}
}


void insertion_sort(int arr[], int size) {
	if (size <= 1)
		return;

	int first_unsorted_loc = 1;
	while (first_unsorted_loc < size) {
		int last_sorted_loc = first_unsorted_loc - 1;
		int tmp_unsorted_loc = first_unsorted_loc;

		while (last_sorted_loc >= 0 && 
				arr[last_sorted_loc] > arr[tmp_unsorted_loc]) {
			swap(&arr[last_sorted_loc], &arr[tmp_unsorted_loc]);

			last_sorted_loc -= 1;
			tmp_unsorted_loc -= 1;
		}

		first_unsorted_loc += 1;
	}
}	


// O(n) maybe
void shell_sort(int arr[], int size) {
	int k = size / 2;
	
	while (k > 0) {
		for (int i = 0; i < k; i++) {
			int first_unsorted_loc = i + k;
			while (first_unsorted_loc < size) {
				int last_sorted_loc = first_unsorted_loc - k;
				int tmp_unsorted_loc = first_unsorted_loc;

				while (last_sorted_loc >= 0 && 
						arr[last_sorted_loc] > arr[tmp_unsorted_loc]) {
					swap(&arr[last_sorted_loc], &arr[tmp_unsorted_loc]);

					last_sorted_loc -= k;
					tmp_unsorted_loc -= k;
				}
				first_unsorted_loc += k;
			}
		}
		k /= 2;
	}
}


// unoptimized
// plain O(n^2) in any case
void bubble_sort(int arr[], int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = i; j < size; j++) {
			if (arr[i] > arr[j]) {
				swap(&arr[i], &arr[j]);
			}
		}
	}
}


void quick_sort(int arr[], int start, int end) {
	if (end - start <= 1)
		return;
	
	int pivot_loc = (end + start) / 2;	

	int left = start;
	int right = end;

	while (left < right) {
		while (arr[left] <= arr[pivot_loc])
			left += 1;

		while (arr[right] >= arr[pivot_loc])
			right -= 1;

		if (left < right) {
			swap(&arr[left], &arr[right]);
			left += 1;
			right -= 1;
		}
	}

	quick_sort(arr, start, pivot_loc - 1);
	quick_sort(arr, pivot_loc + 1, end);
}


void merge(int arr[], int start, int end) {
	if (start >= end)
		return;

	int mid = (end + start) / 2;
	int tmp_arr[end - start + 1];
	
	int first = start;
	int second = mid + 1;
	int w = 0;

	while (first <= mid && second <= end) {
		if (arr[first] < arr[second]) {
			tmp_arr[w++] = arr[first++];
		} else {
			tmp_arr[w++] = arr[second++];
		}
	}

	while (first <= mid)
		tmp_arr[w++] = arr[first++];

	while (second <= end)
		tmp_arr[w++] = arr[second++];

	for (int i = 0; i < end - start + 1; i++) {
		arr[i + start] = tmp_arr[i];
	}
}


void merge_sort(int arr[], int start, int end) {
	if (start >= end)
		return;

	int mid = (end + start) / 2;
	merge_sort(arr, start, mid);
	merge_sort(arr, mid + 1, end);
	merge(arr, start, end);
}


int main() {
	int arr[] = {93, 74, 90, 37, 57, 61, 30, 14, 19, 56, 24};
	int size = sizeof(arr) / sizeof(int);

	printf("Unsorted arr\n");
	print_arr(arr, size);

	merge_sort(arr, 0, size - 1);
	printf("After merge sort\n");
	print_arr(arr, size);

	return 0;
}
