#ifndef MIMIC_H
#define MIMIC_H
enum {MAGICLEN=5};
const char MAGIC[MAGICLEN]={ 'M', 'i', 'M', 'i', 'C' };
enum {TYPELEN=1};
const char TYPE[TYPELEN]={ '\001' }; /* representing Huffman type mimic file */
enum {ENDLEN=3};
const char END[ENDLEN]={ 'E', 'N', 'D' };

typedef struct _where_ {
	long filePosition;
	int sizeOfEntry;
} where;

void writeHeader(FILE *fout);
#endif
