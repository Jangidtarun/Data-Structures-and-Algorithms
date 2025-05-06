#include <string.h>
#include <ctype.h>
#include "p8-avl-adt.h"

#define MAX_WORD_LEN			51
#define MAX_FILENAME_LEN		25
#define EXIT_FAILURE_FOPEN		100
#define EXIT_FAILURE_MALLOC		101

struct data {
	char word[MAX_WORD_LEN];
	int count;
};


// prototypes
void build_list	(struct avl_tree *wlist);
void insert_word (struct avl_tree *words);
void delete_word (struct avl_tree *words);
void print_list (struct avl_tree *wlist);
void print_word (void *word);
bool get_word (struct data *word, FILE *fpwords);
int compare_words (void *arg1, void *arg2);

int main() {
	struct avl_tree *wlist;

	printf("Start count words in document\n");
	wlist = avl_tree_init(compare_words);

	build_list(wlist);
	print_list(wlist);

	avl_tree_destroy(wlist);
	printf("End count words\n");
	return 0;
}


void build_list(struct avl_tree *wlist) {
	printf("Enter name of file to be processed: ");

	// reading file
	char filename[MAX_FILENAME_LEN];
	scanf("%s", filename);
	printf("filename that scanf read: --%s--\n", filename);

	FILE *fpwords = fopen(filename, "r");
	if (!fpwords) {
		printf("%-s could not be opened\a\n", filename);
		printf("Please verify name and try again.\n");
		exit(EXIT_FAILURE_FOPEN);
	}

	struct data *word;
	struct data newword;
	while (get_word (&newword, fpwords)) {
		struct node *word_node = avl_retrieve(wlist, wlist->root, &newword);
		
		if (word_node) {
			// word already exists
			// just update the counter
			word = word_node->dataptr;
			word->count += 1;
		} else {
			// create and insert a new node
			word = (struct data *) malloc(sizeof(struct data));
			if (!word) {
				printf("Error %3d in build_list\n", EXIT_FAILURE_MALLOC);
				exit(EXIT_FAILURE_MALLOC);
			}

			// add word to the tree
			*word = newword;
			word->count = 1;
			wlist->root = avl_insert(wlist, wlist->root, word);
		}
	}

	fclose(fpwords);
	printf("End AVL Tree\n");
	return;
}


bool get_word(struct data *word, FILE *fpwords) {
	char str_read_buff[MAX_WORD_LEN];
	int iores;
	int last_char;

	iores = fscanf(fpwords, "%s", str_read_buff);
	if (iores != 1)
		return false;

	strcpy(word->word, str_read_buff);
	last_char = strlen(word->word) - 1;
	if (ispunct(word->word[last_char]))
		word->word[last_char] = '\0';
	
	return true;
}


int compare_words(void *arg1, void *arg2) {
	struct data w1 = *(struct data *)arg1;
	struct data w2 = *(struct data *)arg2;

	return strcmp(w1.word, w2.word);
}


void print_list(struct avl_tree *wlist) {
	printf("\nWords found in list\n");
	avl_inorder(wlist->root, print_word);
	printf("\nEnd of word list\n");
	return;
}


void print_word(void *word) {
	struct data w = *(struct data *)word;
	printf("%-25s %3d\n", w.word, w.count);
	return;
}






















