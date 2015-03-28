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

enum {MAGICLEN=5};
const char MAGIC[MAGICLEN]={ 'M', 'i', 'M', 'i', 'C' };
enum {ENDLEN=3};
const char END[ENDLEN]={ 'E', 'N', 'D' };

typedef struct _node_ {
	int value;
	struct _node_ *left, *right;
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

	/* write magic to mimic file */
	fwrite(MAGIC, sizeof(char), MAGICLEN, fout);

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

		/* write to mimic file */

		/* increment ngram */
		increment(ngram, n-1);
	}

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
