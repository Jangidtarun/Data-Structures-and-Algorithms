#include <stdio.h>
#include "p7-bst-adt.h"

int main() {
	struct node *root;
	
	int arr[] = {11, 2, 4, 1, 8, 12};
	for(int i = 0; i < sizeof(arr)/sizeof(int); i++) {
		root = bst_insert_tree(root, &arr[i]);
	}

	int key = 7;
	void *res = bst_retrieve(root, &key);
	if (!res) {
		printf("did not find %2.0d\n", key);
	} else {
		printf("found %2.0d\n", key);
	}

	printf("Inorder traversal\n");
	bst_traverse_inorder(root);
	printf("\n");

	printf("Total nodes in tree: %2.0d\n", root->count);
	printf("Tree height: %2.0d\n", root->height);


	bst_destroy(root);
	return 0;
}
