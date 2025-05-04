#ifndef P7_BST_ADT_H
#define P7_BST_ADT_H

#include <stdlib.h>
#include <stdbool.h>

// bst node
struct node {
	int height;
	int count;
	void *dataptr;
	struct node *left;
	struct node *right;
};


// bst create function
struct node *bst_create_tree() {
	struct node *root;

	root = (struct node *) malloc(sizeof(struct node));
	if (!root) {
		printf("Not enough memory to create tree\n");
		return NULL;
	}

	root->height = 0;
	root->count = 0;
	root->dataptr = NULL;
	root->left = NULL;
	root->right = NULL;

	return root;
}


static bool less(const void *a, const void *b) {
	printf("less: a=%p, b=%p\n", a, b);
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

	return root;
}


// bst insert function
struct node *bst_insert_tree(struct node **root, void *dataptr) {
	struct node *newptr;

	newptr = (struct node *) malloc(sizeof(struct node));
	if (!newptr) {
		printf("Not enough memory to insert a node\n");
		return root;
	}

	newptr->height = 1;
	newptr->count = 1;
	newptr->dataptr = dataptr;
	newptr->left = NULL;
	newptr->right = NULL;

	if (!root || root->count == 0) {
		root = newptr;
	} else {
		helper_insert(root, newptr);
		root->count += 1;
	}

	return root;
}


struct node *helper_delete(struct node *root, void *dataptr, bool *success) {
	struct node *dltptr;
	struct node *exchptr;
	struct node *newroot;
	void *holdptr;

	if (!root) {
		*success = false;
		return NULL;
	}

	if (less(dataptr, root->dataptr)) {
		root->left = helper_delete(root->left, dataptr, success);
	} else if (more(dataptr, root->dataptr)) {
		root->right = helper_delete(root->right, dataptr, success);
	} else {
		// this is the node to delete
		dltptr = root;
		if (!root->left) {
			// no left subtree
			free(root->dataptr);
			newroot = root->right;
			free(dltptr);
			*success = true;
			return newroot;
		} else if (!root->right) {
			// only left subtree
			newroot = root->left;
			free(dltptr);
			*success = true;
			return newroot;
		} else {
			// both subtrees are there
			exchptr = root->left;
			
			// look for largest node on left subtree
			while (exchptr->right) {
				exchptr = exchptr->right;
			}

			// exchange data
			holdptr = root->dataptr;
			root->dataptr = exchptr->dataptr;
			exchptr->dataptr = holdptr;
			root->left = helper_delete(root->left, exchptr->dataptr, success);
		}
	}

	return root;
}


// deletes a node from the bst tree
bool bst_delete_tree(struct node *root, void *dltkey) {
	struct node *newroot;
	bool success;

	newroot = helper_delete(root, dltkey, &success);

	if (success) {
		root = newroot;
		root->count -= 1;
	}

	return success;
}
		

// searches for a key and returns the corresponding node if found 
// else returns NULL
void *bst_retrieve(struct node *root, void *keyptr) {
	if (root) {
		printf("bst_retrieve: root->dataptr = %p\n", root->dataptr);
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
	if (root) {
		if (root->left)
			bst_traverse_inorder(root->left);
		printf("%2.0d ", *(int *)(root->dataptr));
		if (root->right)
			bst_traverse_inorder(root->right);
	}
}


bool is_bst_empty(struct node *root) {
	return root->count == 0;
}


int bst_count(struct node *root) {
	return root->count;
}


void bst_destroy(struct node *root) {
	if (root) {
		bst_destroy(root->left);
		bst_destroy(root->right);
		free(root);
	}
}

#endif
