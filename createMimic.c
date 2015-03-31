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
#include "huffman.h"

typedef struct _node_ {
	int value;
	char letter;
	struct _node_ *left, *right;
	struct _node_ *parent;
} node;

void increment(char* array, int size);

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

	/* write header of mimic file */
	writeHeader(n, fout);

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

	/* write end of mimic file */
	writeEnd(wheres, 1<<n, fout);

	/* clean up */
	free(window);
	free(ngram);
	free(wheres);
	fclose(fin);
	fclose(fout);

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
