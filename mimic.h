#ifndef MIMIC_H
#define MIMIC_H
#include <stdio.h>
typedef struct _where_ {
	long filePosition;
	int sizeOfEntry;
} where;

void writeHeader(int n, FILE *fout);
void writeEnd(where *wheres, int numWheres, FILE *fout);
#endif
