#include <stdio.h>
#include "p8-avl-adt.h"


int main() {
	struct node *root = NULL;
	int vals[] = {10, 20, 30, 40, 50, 25};

	for (int i = 0; i < 6; i++) {
		root = avl_insert(root, vals[i]);
	}

	printf("Inorder\n");
	avl_inorder(root);
	printf("\n");

	avl_destroy(root);
	return 0;
}
