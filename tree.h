#ifndef TREE_H
#define TREE_H

typedef struct _node {
				struct _node* left;
				struct _node* right;
				void* data;
} node;

node* freeTree(node* root);

node** getLeaves(node* root);

#endif
