#include "tree.h"

treeNode* freeTree(treeNode* root) {
				if (root == NULL) {
								return NULL;
				}
				root->left = freeTree(root->left);
				root->right = freeTree(root->right);
				return NULL;
}

treeNode** getLeaves(treeNode* root) {
				if (root == NULL) {
								return NULL;
				}
				if (root->left != NULL or root->right != NULL) {
								/* getLeaves of left and right and combine them */
				}
				/* root has no left or right, so it is a leaf */
				return &root;
}
