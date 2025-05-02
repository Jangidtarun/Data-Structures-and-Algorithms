#define LH +1
#define EH  0
#define RH -1

// structure declarations
typedef struct node {
	void*			dataptr;
	struct node*	left;
	int				bal;
	struct node*	right;
} Node;

typedef struct {
	int		count;
	int		(*compare) (void* arg1, void* arg2);
	Node*	root;
} avl_tree;


// prototype declarations
avl_tree* avl_create	(int (*compare) (void* arg1, void* arg2));
avl_tree* avl_destory	(avl_tree* tree);

bool avl_insert		(avl_tree* tree, void* dataptr);
bool avl_delete		(avl_tree* tree, void* dltkey);
void* avl_retrieve	(avl_tree* tree, void* keyptr);
void* avl_traverse	(avl_tree* tree, void (*process) (void* dataptr));
int avl_count		(avl_tree* tree);
bool avl_empty		(avl_tree* tree);
bool avl_full		(avl_tree* tree);

static Node* _insert	(avl_tree* tree, Node* root, Node* newptr, bool* taller);
static Node* _delete	(avl_tree* tree, Node* root, void* dltkey, bool* shorter, bool* success);
static void* _retrieve	(avl_tree* tree, void* keyptr, Node* root);
static void _traversal	(Node* root, void (*process) (void* dataptr));
static void _destroy	(Node* root);

static Node* rotate_left	(Node* root);
static Node* rotate_right	(Node* root);
static Node* ins_left_bal	(Node* root, bool* taller);
static Node* ins_right_bal	(Node* root, bool* taller);
static Node* dlt_left_bal	(Node* root, bool* shorter);
static Node* dlt_right_bal	(Node* root, bool* shorter);


/*
 * Allocates dynamic memory for an AVL tree head 
 * node and returns its address to caller.
 */
avl_tree* avl_create (int (*compare) (void* arg1, void* arg2)) {
	avl_tree* tree = (avl_tree*) malloc(sizeof(avl_tree));

	if (tree) {
		tree->count = 0;
		tree->compare = compare;
		tree->root = NULL;
	}

	return tree;
}


/*
 * This function inserts new data into the tree.
 */
bool avl_insert (avl_tree* tree, void* dataptr) {
	// local definitions
	Node* newptr;
	bool fortaller;

	newptr = (Node*) malloc(sizeof(Node));
	if (!newptr)
		return false;

	newptr->bal		= EH;
	newptr->right	= NULL;
	newptr->left	= NULL;
	newptr->dataptr	= dataptr;

	tree->root = _insert(tree, tree->root, newptr, &fortaller);
	(tree->count) += 1;
	return true;
}
