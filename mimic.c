#include "mimic.h"

enum {MAGICLEN=5};
const char MAGIC[MAGICLEN]={ 'M', 'i', 'M', 'i', 'C' };
enum {TYPELEN=1};
const char TYPE[TYPELEN]={ '\001' }; /* representing Huffman type mimic file */
enum {ENDLEN=3};
const char END[ENDLEN]={ 'E', 'N', 'D' };

void writeHeader(int n, FILE *fout) {
	fwrite(MAGIC, sizeof(char), MAGICLEN, fout);
	fwrite(TYPE, sizeof(char), TYPELEN, fout);
	fwrite(&n, sizeof(char), 1, fout);
	return;
}

void writeEnd(where *wheres, int numWheres, FILE *fout) {
	fwrite(wheres, sizeof(where), numWheres, fout);
	fwrite(END, sizeof(char), ENDLEN, fout);
	return;
}
