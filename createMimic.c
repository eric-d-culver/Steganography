/* createMimic.c
** Usage: createMimic <file to mimic> mimicParam <mimic file>
** Used to create a Huffman-coded mimic function for hiding data.
** This takes a source to mimic and extracts the relevent frequency 
** information then creates a canonical Huffman code from the freqs.
** This canonical Huffman code is stored into the mimic file.
*/
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "mimic.h"

typedef struct _node_ {
	int value;
	char letter;
	struct _node_ *left, *right;
	struct _node_ *parent;
} node;

void increment(char* array, int size);

void findTwoSmallest(node** array, int size, int* first, int* second);

int numNonZero(node** array, int size);

node * buildTree(node** array, int size);

int isLeaf(node* np);

char * extractLettersAndFree(node* root, int depth, char* letters, char* depths);

int main(int argc, char* argv[]) {
	FILE *fin=fopen(argv[1], "r");
	int n=atoi(argv[2]);
	FILE *fout=fopen(argv[3], "w");

	char *window=(char *) malloc((n-1)*sizeof(char));
	char buffer;
	char *ngram=(char *) malloc((n-1)*sizeof(char));

	int freqs[1<<CHAR_BIT];
	int i, j;
	where * wheres;
	wheres=(where *)malloc((1<<n)*sizeof(where));

	/* write magic to mimic file */
	fwrite(MAGIC, sizeof(char), MAGICLEN, fout);

	/* write type to mimic file */
	fwrite(TYPE, sizeof(char), TYPELEN, fout);

	/* write n to mimic file */
	fwrite(&n, sizeof(char), 1, fout);

	/* initializing ngram */
	for (i=0; i<(n-1); ++i) {
		ngram[i]=0;
	}

	for (j=0; j<(1<<n); ++j) {
		/* initialize  freqs to zero */
		for (i=0; i<(1<<CHAR_BIT); ++i) {
			freqs[i]=0;
		}

		/* moving window through fin */
		fread(window, sizeof(char), n-1, fin);

		while(fread(&buffer, sizeof(char), 1, fin)==1) {
			if (memcmp(window, ngram, n-1)) {
				++freqs[buffer];
			}
			for (i=0; i<(n-2); ++i) {
				window[i]=window[i+1];
			}
			window[n-1]=buffer;
		}

		/* create canonical Huffman code */
		node *array[1<<CHAR_BIT];
		for (i=0; i<(1<<CHAR_BIT); ++i) {
			array[i]=(node *) malloc(sizeof(node));
			array[i]->value=freqs[i];
			array[i]->letter=i;
			array[i]->left=NULL;
			array[i]->right=NULL;
			array[i]->parent=NULL;
		}

		node *root=buildTree(array, 1<<CHAR_BIT);

		char huffCode[1<<CHAR_BIT];
		char* place=(char *)huffCode;
		char depths[CHAR_BIT];

		for (i=0; i<CHAR_BIT; ++i) depths[i]=0;

		/* traverse tree, picking up letters in order from least deep to most deep */
		/* also free memory for tree, we don't need it anymore */
		place=extractLettersAndFree(root, 0, place, depths);

		/* write to mimic file */
		wheres[j].filePosition=ftell(fout);
		fwrite(depths, sizeof(char), CHAR_BIT, fout);
		fwrite(huffCode, sizeof(char), place-huffCode, fout);
		wheres[j].sizeOfEntry=ftell(fout)-wheres[j].filePosition;

		/* increment ngram */
		increment(ngram, n-1);

		/* reset input file */
		rewind(fin);
	}

	/* writes wheres to mimic file */
	fwrite(wheres, sizeof(index), 1<<n, fout);

	/* write end to mimic file */
	fwrite(END, sizeof(char), ENDLEN, fout);

	/* clean up */
	free(window);
	free(ngram);

	return 0;
}

void increment(char* array, int size) {
	int i;
	for (i=size-1; i>=0; --i) {
		if (array[i]==255) array[i]==0;
		else {
			++array[i];
			i=-1;
		}
	}
	return;
}

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
