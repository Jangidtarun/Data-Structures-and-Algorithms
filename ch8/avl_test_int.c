#include <stdio.h>
#include "p8-avl-adt.h"


int cmp_int(void *arg1, void *arg2) {
	int key1 = *(int *)arg1;
	int key2 = *(int *)arg2;

	if (key1 < key2)
		return -1;
	else if (key1 > key2)
		return 1;
	return 0;
}


void process(void *dataptr) {
	int data = *(int *)dataptr;
	printf("%2d\n", data);
}


void print_tree_inorder(struct avl_tree *tree, 
		void (*process) (void *dataptr)) {
	printf("Inorder\n");
	avl_inorder(tree->root, process);
	printf("\n");
}


int main() {
	struct avl_tree *tree = avl_tree_init(&cmp_int);
	int vals[] = {10, 20, 30, 40, 50, 25};

	for (int i = 0; i < 6; i++) {
		int *data = (int *)malloc(sizeof(int));
		if (!data) {
			printf("unable to assign new data\n");
			exit(110);
		}
		*data = vals[i];
		tree->root = avl_insert(tree, tree->root, data);
	}

	printf("Inorder\n");
	avl_inorder(tree->root, process);
	printf("\n");
	// print_tree_inorder(tree, process);

	// test delete case 4
	tree->root = avl_delete(tree, tree->root, &vals[2]);
	print_tree_inorder(tree, process);
	avl_pretty_print(tree->root, 0, process);

	avl_tree_destroy(tree);
	return 0;
}
