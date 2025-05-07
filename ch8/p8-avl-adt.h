#ifndef _P8_AVL_ADT_H
#define _P8_AVL_ADT_H

#include <stdlib.h>
#include <stdio.h>
#include "../ch3/p3-stack-adt.h"


struct node {
	void *dataptr;
	struct node *left;
	struct node *right;
	int height;
};


struct avl_tree {
	struct node *root;
	int count;
	int (*cmp) (void *arg1, void *arg2);
};


static int height(struct node *root) {
	return root ? root->height : 0;
}


static int get_balance(struct node *root) {
	if (!root)
		return 0;
	return height(root->left) - height(root->right);
}


int max(const int a, const int b) {
	return (a > b) ? a : b;
}


void update_height(struct node *curr) {
	if (curr)
		curr->height = 1 + max(height(curr->left), height(curr->right));
}


struct node *make_node(void *dataptr) {
	struct node *curr = (struct node *) malloc(sizeof(struct node));
	if (!curr) {
		printf("Out of memory allocating new node\n");
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


struct node *balance_tree(struct avl_tree *tree, 
		struct node *root, 
		void *dataptr) {

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
 * this function is bug free both balancing algorithms work exactly the 
 * same way just that this one does not require the additional argument
 * to dataptr
 */
struct node *balance_tree_chatgpt(struct avl_tree *tree, struct node *root) {
	if (!root)
		return NULL;

	update_height(root);
	int bal = get_balance(root);

	// left heavy
	if (bal > 1) {
		if (get_balance(root->left) >= 0) {
			return rotate_right(root);
		} else {
			root->left = rotate_left(root->left);
			return rotate_right(root);
		}
	}

	// right heavy
	if (bal < -1) {
		if (get_balance(root->right) <= 0) {
			return rotate_left(root);
		} else {
			root->right = rotate_right(root->right);
			return rotate_left(root);
		}
	}

	return root;
}


struct node *avl_insert(struct avl_tree *tree, 
						struct node *root, 
						void *dataptr) {
	
	if (!root) {
		struct node *newnode = make_node(dataptr);
		if (!newnode) {
			return NULL;
		} else {
			tree->count += 1;
		}
		return newnode;
	}

	int cmpres = tree->cmp(dataptr, root->dataptr);
	if (cmpres < 0) {
		root->left = avl_insert(tree, root->left, dataptr);
	} else if (cmpres > 0) {
		root->right = avl_insert(tree, root->right, dataptr);
	} else {
		// no duplicates for now
		// might add later
		return root;
	}

	return balance_tree_chatgpt(tree, root);
}


struct node *get_predecesor(struct node *root) {
	struct node *tmp = root;
	while (tmp && tmp->right) {
		tmp = tmp->right;
	}
	return tmp;
}


struct node *avl_delete(struct avl_tree *tree,
						struct node		*root,
						void			*dataptr) {
	if (!root) {
		return root;
	}

	int cmpres = tree->cmp(dataptr, root->dataptr);

	if (cmpres < 0) {
		root->left = avl_delete(tree, root->left, dataptr);
	} else if (cmpres > 0) {
		root->right = avl_delete(tree, root->right, dataptr);
	} else {
		tree->count -= 1;

		// case 1: no subtree exist
		if (!root->left && !root->right) {
			free(root->dataptr);
			free(root);
			return NULL;
		}

		// case 2: only right subtree exist
		else if (!root->left) {
			struct node *tmp = root->right;
			free(root->dataptr);
			free(root);
			return tmp;
		}

		// case 3: only left subtree exist
		else if (!root->right) {
			struct node *tmp = root->left;
			free(root->dataptr);
			free(root);
			return tmp;
		}

		// case 4: both subtree exist
		else if (root->left && root->right) {
			struct node *pred =	get_predecesor(root->left);
			void *tmp = root->dataptr;
			root->dataptr = pred->dataptr;
			pred->dataptr = tmp;

			root->left = avl_delete(tree, root->left, pred->dataptr);
		}
	}

	return balance_tree_chatgpt(tree, root);
}


struct node *avl_retrieve(struct avl_tree *tree, 
		struct node	*root, void *dataptr) {

	int cmpres = tree->cmp(dataptr, root->dataptr);

	if (root) {
		if (cmpres < 0) {
			return avl_retrieve(tree, root->left, dataptr);
		} else if (cmpres > 0) {
			return avl_retrieve(tree, root->right, dataptr);
		} else {
			return root;
		}
	}

	return NULL;
}


void avl_inorder(struct node *root, 
				 void (*process) (void *dataptr)) {
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


void avl_pretty_print(struct node *root, 
		int depth, 
		void (*process) (void *dataptr)) {

    if (!root) 
		return;

    avl_pretty_print(root->right, depth + 1, process);

    for (int i = 0; i < depth; i++)
        printf("  ");  
	printf("%2d. ", depth);
	process(root->dataptr);

    avl_pretty_print(root->left, depth + 1, process);
}


/*
 * under construction
 * balancing remains
 * no memory issues for now
 */
struct node *avl_iterative_insert(struct avl_tree *tree,
		struct node *root,
		void *dataptr) {
	struct node *newnode = make_node(dataptr);

	if (!root) {
		tree->count += 1;
		return newnode;
	}

	struct stack *stk = stack_init();
	struct node *traveller = root;

	while (traveller) {
		push_stack(stk, traveller);
		printf("pushing %2d in stack\n", *(int *)(traveller->dataptr));

		int cmp = tree->cmp(dataptr, traveller->dataptr);
		
		if (cmp < 0)
			traveller = traveller->left;
		else if (cmp > 0)
			traveller = traveller->right;
		else {
			printf("Duplicates are not allowed\n");
			free(newnode);
			free_stack_nodata(stk);
			return root;
		}

	}

	struct node *insert_point = stack_top(stk);
	int cmp = tree->cmp(dataptr, insert_point->dataptr);
	if (cmp < 0) {
		insert_point->left = newnode;
	} else {
		insert_point->right = newnode;
	}

	tree->count += 1;

	/*
	 * the issue with balancing is that pop_stack also frees the node it stored
	 * unless there is a way around that balancing is tricky
	 * pop_stack frees memory it should not [just in this case]
	 */

	free_stack_nodata(stk);
	return root;
}


#endif
