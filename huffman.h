#ifndef HUFFMAN_H
#define HUFFMAN_H
typedef struct _node_ {
	int value;
	char letter;
	struct _node_ *left, *right;
	struct _node_ *parent;
} node;

node * buildTree(node** array, int size);

char * extractLettersAndFree(node* root, int depth, char* letters, char* depths);
#endif
