#ifndef TREE_H
#define TREE_H

typedef struct _treeNode {
				struct _treeNode* left;
				struct _treeNode* right;
				void* data;
} treeNode;

treeNode* freeTree(treeNode* root);

treeNode** getLeaves(treeNode* root);

#endif
