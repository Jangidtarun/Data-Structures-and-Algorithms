#include <stdio.h>

void print_reverse(int arr[], int size) {
	if(size == 0)
		return;

	print_reverse(arr + 1, size - 1);

	printf("%d\n", *arr);
}

int main() {
	int arr[5] = {1, 2, 0, 20, 30};

	print_reverse(arr, sizeof(arr) / sizeof(int));
	return 0;
}
