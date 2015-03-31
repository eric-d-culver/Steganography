#include "huffman.h"

void findTwoSmallest(node** array, int size, int* first, int* second);
int numNonZero(node** array, int size);
int isLeaf(node* np);

void findTwoSmallest(node** array, int size, int* first, int* second) {
	*first=0;
	*second=0;
	int i;
	for (i=0; i<size; ++i) {
		if (array[i]->value == 0) continue;
		if (array[i]->value < array[*second]->value) {
			if (array[i]->value < array[*first]->value) *first=i;
			else *second=i;
		}
	}
	return;
}

int numNonZero(node** array, int size) {
	int i;
	int num;
	for (i=0; i<size; ++i)
		if (array[i]->value!=0) ++num;
	return num;
}

node * buildTree(node** array, int size) {
	unsigned int firstIndex, secondIndex, topIndex;
	while (numNonZero(array, size)>1) {
		findTwoSmallest(array, size, &firstIndex, &secondIndex);
		node *oneUp = (node *)malloc(sizeof(node));
		oneUp->value=array[firstIndex]->value + array[secondIndex]->value;

		if (firstIndex<secondIndex) {
			oneUp->left=array[firstIndex];
			oneUp->right=array[secondIndex];
		} else {
			oneUp->left=array[secondIndex];
			oneUp->right=array[firstIndex];
		}

		array[firstIndex]->parent=oneUp;
		array[secondIndex]->parent=oneUp;
		array[firstIndex]=oneUp;
		array[secondIndex]->value=0;
		topIndex=firstIndex;
	}
	return array[topIndex];
}

int isLeaf(node* np) {
	if (np->left==NULL && np->right==NULL) return 1;
	return 0;
}

char * extractLettersAndFree(node* root, int depth, char* nextLetter, char* depths) {
	if (isLeaf(root)) {
		*(nextLetter++)=root->letter;
		++depths[depth];
		free(root);
		return nextLetter;
	}
	nextLetter=extractLettersAndFree(root->left, depth+1, nextLetter, depths);
	nextLetter=extractLettersAndFree(root->right, depth+1, nextLetter, depths);
	free(root);
	return nextLetter;
}
