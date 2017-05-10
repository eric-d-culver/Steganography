/* bitFile.c
** helper module for reading and writing to a file bit by bit
*/

#include "bitFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

unsigned char* byteToBits(unsigned char byte) {
				unsigned char* bits = malloc(CHAR_BIT*sizeof(unsigned char));
				for (int i = 0; i < CHAR_BIT; i++) {
								bits[i] = (byte >> i)&1;
				}
				return bits;
}

unsigned char bitsToByte(unsigned char* bits) {
				unsigned char byte = 0;
				for (int i = 0; i < CHAR_BIT; i++) {
								byte = byte | ((bits[i]) << i);
				}
				return byte;
}

dynaArray* initArray() { /* initilizes dynamic array */
				dynaArray* self = malloc(sizeof(dynaArray));
				self->num_elements = 0;
				self->num_allocated = 3;
				
				self->array = malloc((self->num_allocated) * sizeof(unsigned char));

				return self;
}

int addToArray(dynaArray* self, unsigned char item) { /* adds item to end of dynamic array self */
				if((self->num_elements) == (self->num_allocated)) { /* are more refs required? */
								if (self->num_allocated == 0) {
												self->num_allocated = 3; /* start off with 3 */
								} else {
												self->num_allocated *= 2; /* double the number of refs */
								}
								self->array = realloc(self->array, ((self->num_allocated) * sizeof(unsigned char)));
				}

				(self->array)[self->num_elements] = item;
				(self->num_elements)++;

				return 0;
}

unsigned char* copyFromArray(dynaArray* self, int numItems) { /* returns numItems from beginning of dynamic array self without removing them */
				unsigned char* res = malloc(numItems * sizeof(unsigned char));
				memcpy(res, self->array, numItems);
				return res;
}

unsigned char* pullFromArray(dynaArray* self, int numItems) { /* removes numItems from beginning of dynamic array self and returns them */
				unsigned char* res = malloc(numItems * sizeof(unsigned char));
				memcpy(res, self->array, numItems);
				memmove(self->array, (self->array)+numItems, (self->num_elements)-numItems);
				(self->num_elements) -= numItems;
				return res;
}

void finiArray(dynaArray* self) { /* empties and frees dynamic array self */
				pullFromArray(self, self->num_elements);
				free(self->array);
				self->num_elements = 0;
				self->num_allocated = 0;
				free(self);
				return;
}

unsigned char* bitRead_read(bitRead* self, int numBits) { /* reads next numBits bits from file */
				unsigned char nextChar;
				unsigned char* bits;
				while ((self->bits->num_elements < numBits) && !(self->isEOF(self))) {
								nextChar = (unsigned char) fgetc(self->file);
								bits = byteToBits(nextChar);
								for (int i = 0; i < CHAR_BIT; i++) {
												addToArray(self->bits, bits[i]);
								}
								free(bits);
				}
				return pullFromArray(self->bits, numBits);
}

unsigned char* bitRead_peek(bitRead* self, int numBits) { /* peeks at next numBits bits from file */
				unsigned char nextChar;
				unsigned char* bits;
				while((self->bits->num_elements < numBits) && !(self->isEOF(self))) {
								nextChar = (unsigned char) fgetc(self->file);
								bits = byteToBits(nextChar);
								for (int i = 0; i < CHAR_BIT; i++) {
												addToArray(self->bits, bits[i]);
								}
								free(bits);
				}
				return copyFromArray(self->bits, numBits);
}

int bitRead_isEOF(const bitRead* self) { /* tests if file is at EOF */
				return feof(self->file);
}

void bitWrite_write(bitWrite* self, unsigned char* bits, int numBits) { /* writes bits to file */
				for (int i = 0; i < numBits; i++) {
								addToArray(self->bits, bits[i]);
				}
				while (self->bits->num_elements >= CHAR_BIT) {
								fputc(bitsToByte(pullFromArray(self->bits, CHAR_BIT)), self->file);
				}
				return;
}

bitRead* initBitRead(FILE* file) {
				bitRead* self = malloc(sizeof(bitRead));
				self->file = file;
				self->bits = initArray();
				self->read = bitRead_read;
				self->peek = bitRead_peek;
				self->isEOF = bitRead_isEOF;
				return self;
}

bitWrite* initBitWrite(FILE* file) {
				bitWrite* self = malloc(sizeof(bitWrite));
				self->file = file;
				self->bits = initArray();
				self->write = bitWrite_write;
				return self;
}

FILE* finiBitRead(bitRead* self) {
				FILE* tmp = self->file;
				finiArray(self->bits);
				free(self);

				return tmp;
}

FILE* finiBitWrite(bitWrite* self) {
				FILE* tmp = self->file;
				finiArray(self->bits);
				free(self);

				return tmp;
}

/*
int main(int argc, char* argv) {
				int num = 16;
				FILE* fin = fopen("test.txt", "r");
				bitRead* test1 = initBitRead(fin);
				unsigned char* bits = test1->read(test1, num);
				for (int i = 0; i < num; i++) {
								printf("%d\n", bits[i]);
				}

				FILE* fout = fopen("test2.txt", "w");
				bitWrite* test2 = initBitWrite(fout);
				test2->write(test2, bits, num);

				fclose(finiBitRead(test1));
				fclose(finiBitWrite(test2));

				return 0;
}
*/
