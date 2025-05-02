#import <stdbool.h>

typedef struct node
{
    void *dataptr;
    struct node *left;
    struct node *right;
} node_t;

typedef struct
{
    int count;
    int (*cmp) (void *arg1, void *arg2);
    node_t *root;
} bst_tree;


// prototype declarations
bst_tree *bst_create(int (*cmp) (void *arg1, void *arg2));
bst_tree *bst_destroy(bst_tree *tree);
bool bst_insert(bst_tree *tree, void *dataptr);
bool bst_delete(bst_tree *tree, void *dltkey);
void *bst_retrieve(bst_tree *tree, void *keyptr);
void bst_traverse(bst_tree *tree, void (*process) (void *dataptr));
bool bst_empty (bst_tree *tree);
bool bst_full (bst_tree *tree);
int bst_count (bst_tree *tree);
static node_t* _insert(bst_tree *tree, node_t *root, node_t *newptr);
static node_t* _delete(bst_tree *tree, node_t *root, node_t *dataptr, bool *success);
static void* _retrieve(bst_tree *tree, void *dataptr, node *root);
static void _traverse(node_t *root, void (*process) (void *dataptr));
static void _destroy(node_t *root);



