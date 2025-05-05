#ifndef _P8_AVL_ADT_H
#define _P8_AVL_ADT_H

#include <stdlib.h>
#include <stdio.h>


/*
 * AVL node structure
 */
struct node {
	void *dataptr;
	struct node *left;
	struct node *right;
	int height;
};


/*
 * AVL Tree structure
 * uses a compare function
 */
struct avl_tree {
	struct node *root;
	int count;
	int (*cmp) (void *arg1, void *arg2);
};


// get height utility function
static int height(struct node *root) {
	return root ? root->height : 0;
}


// get balance factor utility function
static int get_balance(struct node *root) {
	if (root == NULL) {
		return 0;
	}
	return height(root->left) - height(root->right);
}


// get max utility function
static int max(int a, int b) {
	return (a > b) ? a : b;
}


// update height utility function
void update_height(struct node *curr) {
	if (curr)
		curr->height = 1 + max(height(curr->left), height(curr->right));
}


// make node function
struct node *make_node(void *dataptr) {
	struct node *curr = (struct node *) malloc(sizeof(struct node));
	if (!curr) {
		fprintf(stderr, "Out of memory allocating new node\n");
		return NULL;
	}

	curr->dataptr = dataptr;
	curr->left = NULL;
	curr->right = NULL;
	curr->height = 1;

	return curr;
}


static struct node *rotate_right(struct node *curr) {
	struct node *newcurr = curr->left;
	struct node *tmp = newcurr->right;

	newcurr->right = curr;
	curr->left = tmp;

	update_height(newcurr);
	update_height(curr);

	return newcurr;
}


static struct node *rotate_left(struct node *curr) {
	struct node *newcurr = curr->right;
	struct node *tmp = newcurr->left;

	newcurr->left = curr;
	curr->right = tmp;

	update_height(newcurr);
	update_height(curr);

	return newcurr;
}


struct avl_tree *avl_tree_init(int (*cmp) (void *arg1, void *arg2)) {
	struct avl_tree *tree = (struct avl_tree *) malloc(sizeof(struct avl_tree));
	if (!tree) {
		printf("Not enough memory to initialize tree.\n");
		return NULL;
	}

	tree->count = 0;
	tree->root = NULL;
	tree->cmp = cmp;

	return tree;
}


struct node *avl_insert(struct avl_tree *tree, struct node *root, void *dataptr) {
	if (!root) {
		tree->count += 1;
		return make_node(dataptr);
	}

	if (tree->cmp(dataptr, root->dataptr) < 0) {
		root->left = avl_insert(tree, root->left, dataptr);
	} else if (tree->cmp(dataptr, root->dataptr) > 0) {
		root->right = avl_insert(tree, root->right, dataptr);
	} else {
		// no duplicates
		return root;
	}

	update_height(root);
	int bal = get_balance(root);

	// LL
	if (bal > 1 && tree->cmp(dataptr, root->left->dataptr) < 0)
		return rotate_right(root);

	// LR
	if (bal > 1 && tree->cmp(dataptr, root->left->dataptr) > 0) {
		root->left = rotate_left(root->left);
		return rotate_right(root);
	}

	// RR
	if (bal < -1 && tree->cmp(dataptr, root->right->dataptr) > 0)
		return rotate_left(root);

	// RL
	if (bal < -1 && tree->cmp(dataptr, root->right->dataptr) < 0) {
		root->right = rotate_right(root->right);
		return rotate_left(root);
	}

	return root;
}


/*
 * retrive a given data pointer
 */
struct node *avl_retrieve(struct avl_tree *tree, struct node *root, void *dataptr) {
	if (root) {
		if (tree->cmp(dataptr, root->dataptr) < 0) {
			return avl_retrieve(tree, root->left, dataptr);
		} else if (tree->cmp(dataptr, root->dataptr) > 0) {
			return avl_retrieve(tree, root->right, dataptr);
		} else {
			return root;
		}
	}

	return NULL;
}


void avl_inorder(struct node *root, void (*process) (void *dataptr)) {
	if (root) {
		avl_inorder(root->left, process);
		process(root->dataptr);
		avl_inorder(root->right, process);
	}
}


static void avl_destroy(struct node *root) {
	if (root) {
		avl_destroy(root->left);
		avl_destroy(root->right);
		free(root->dataptr);
		free(root);
	}
}

void avl_tree_destroy(struct avl_tree *tree) {
	if (!tree) {
		return;
	} else {
		if (tree->root) {
			avl_destroy(tree->root);
		}
		free(tree);
	}
}


#endif
