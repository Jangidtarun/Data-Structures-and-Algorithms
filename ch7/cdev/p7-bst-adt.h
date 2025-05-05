#ifndef _P7_BST_ADT_H
#define _P7_BST_ADT_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// bst node
struct node {
	void *dataptr;
	struct node *left;
	struct node *right;
	// number of nodes in this subtree, including this node
	int count;
	// height of the subtree rooted at this node
	int height;
};


static bool less(const void *a, const void *b) {
	// printf("less: a=%p, b=%p\n", a, b);
	return *(int *)a < *(int *)b;
}


static bool more(const void *a, const void *b) {
	return *(int *)a > *(int *)b;
}


// internal insert helper function
struct node *helper_insert(struct node *root, struct node *newptr) {
	if (!root) {
		return newptr;
	}

	if (less(newptr->dataptr, root->dataptr)) {
		root->left = helper_insert(root->left, newptr);
	} else {
		root->right = helper_insert(root->right, newptr);
	}

	int lc = root->left ? root->left->count : 0;
	int rc = root->right ? root->right->count : 0;
	root->count = 1 + lc + rc;

	int lh = root->left ? root->left->height : 0;
	int rh = root->right ? root->right->height : 0;
	root->height = 1 + (lh > rh ? lh : rh);

	return root;
}


// bst insert function
struct node *bst_insert_tree(struct node *root, void *dataptr) {
	struct node *newptr;

	newptr = (struct node *) malloc(sizeof(struct node));
	if (!newptr) {
		printf("Not enough memory to insert a node\n");
		return root;
	}

	newptr->dataptr = dataptr;
	newptr->left = NULL;
	newptr->right = NULL;
	newptr->count = 1;
	newptr->height = 1;

	return helper_insert(root, newptr);
}


// bst delete helper
struct node *helper_delete(struct node *root, void *dataptr) {
	if (!root) {
		return NULL;
	}

	if (less(dataptr, root->dataptr)) {
		root->left = helper_delete(root->left, dataptr);
	} else if (more(dataptr, root->dataptr)) {
		root->right = helper_delete(root->right, dataptr);
	} else {
		// found the node 
		struct node *tmp;

		if (!root->left) {
			// no left subtree
			tmp = root->right;
			free(root->dataptr);
			free(root);
			return tmp;
		} else if (!root->right) {
			// only left subtree
			tmp = root->left;
			free(root->dataptr);
			free(root);
			return tmp;
		} else {
			// find inorder predecessor (max in left)
			struct node *pred = root->left;
			while (pred->right) {
				pred = pred->right;
			}

			void *tmp = root->dataptr;
			root->dataptr = pred->dataptr;
			pred->dataptr = tmp;

			root->left = helper_delete(root->left, pred->dataptr);
		}
	}

	return root;
}


// deletes a node from the bst tree
struct node *bst_delete_tree(struct node *root, void *dltkey) {
	return helper_delete(root, dltkey);
}
		

// searches for a key and returns the corresponding node if found 
// else returns NULL
void *bst_retrieve(struct node *root, void *keyptr) {
	if (root) {
		// printf("bst_retrieve: root->dataptr = %p\n", root->dataptr);
		if (less(keyptr, root->dataptr)) {
			return bst_retrieve(root->left, keyptr);
		} else if (more(keyptr, root->dataptr)) {
			return bst_retrieve(root->right, keyptr);
		} else {
			// found equal key
			return root->dataptr;
		}
	}
	return NULL;
}


void bst_traverse_inorder(struct node *root) {
	if (!root)
		return;
	
	bst_traverse_inorder(root->left);
	printf("%2.0d ", *(int *)(root->dataptr));
	bst_traverse_inorder(root->right);
}


void bst_destroy(struct node *root) {
	if (!root)
		return;

	bst_destroy(root->left);
	bst_destroy(root->right);
	free(root);
}

#endif // _P7_BST_ADT_H
