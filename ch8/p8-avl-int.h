#ifndef _P8_AVL_ADT_H
#define _P8_AVL_ADT_H

#include <stdlib.h>
#include <stdio.h>

struct node {
	int key;
	int height;
	struct node *left;
	struct node *right;
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
struct node *make_node(int key) {
	struct node *curr = (struct node *) malloc(sizeof(struct node));
	if (!curr) {
		fprintf(stderr, "Out of memory allocating new node\n");
		return NULL;
	}

	curr->key = key;
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


struct node *avl_insert(struct node *root, int key) {
	if (!root) {
		return make_node(key);
	}

	if (key < root->key) {
		root->left = avl_insert(root->left, key);
	} else if (key > root->key) {
		root->right = avl_insert(root->right, key);
	} else {
		// no duplicates
		return root;
	}

	update_height(root);
	int bal = get_balance(root);

	// LL
	if (bal > 1 && key < root->left->key)
		return rotate_right(root);

	// LR
	if (bal > 1 && key > root->left->key) {
		root->left = rotate_left(root->left);
		return rotate_right(root);
	}

	// RR
	if (bal < -1 && key > root->right->key)
		return rotate_left(root);

	// RL
	if (bal < -1 && key < root->right->key) {
		root->right = rotate_right(root->right);
		return rotate_left(root);
	}

	return root;
}


void avl_inorder(struct node *root) {
	if (root) {
		avl_inorder(root->left);
		printf("%2d ", root->key);
		avl_inorder(root->right);
	}
}


void avl_destroy(struct node *root) {
	if (root) {
		avl_destroy(root->left);
		avl_destroy(root->right);
	}
	free(root);
}


#endif
