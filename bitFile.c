/* bitFile.c
** helper module for reading and writing to a file bit by bit
*/

#include "bitFile.h"
#include <stdio.h>
#include <stdlib.h>
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
								self->array = realloc(self->array, (num_allocated * sizeof(unsigned char)));
				}

				(self->array)[self->num_elements] = item;
				(self->num_elements)++;

				return 0;
}

int removeFromArray(dynaArray* self, int numItems) { /* removes numItems from beginning of dynamic array self */
				memmove(self->array, (self->array)+numItems, (self->num_elements)-numItems);
				(self->num_elements) -= numItems;
				return 0;
}

void finiArray(dynaArray* self) { /* empties and frees dynamic array self */
				removeFromArray(self, self->num_elements);
				free(self->array);
				self->num_elements = 0;
				self->num_allocated = 0;
				free(self);
				return;
}

bitRead* initBitRead(FILE* file) {
				bitRead* self = malloc(sizeof(bitRead));
				self->file = file;
				self->bits = initArray();
				return self;
}

bitWrite* initBitWrite(FILE* file) {
				bitWrite* self = malloc(sizeof(bitWrite));
				self->file = file;
				self->bits = initArray();
				return self;
}

FILE* finiBitRead(bitRead* self) {
				FILE* tmp = self->file;
				finiArray(self->bits);

				return tmp;
}

FILE* finiBitWrite(bitWrite* self) {
				FILE* tmp = self->file;
				finiArray(self->bits);

				return tmp;
}

/*
int main(int argc, char* argv) {
				unsigned char* bits = byteToBits('A');
				for (int i = 0; i < CHAR_BIT; i++) {
								printf("%d\n", bits[i]);
				}
				unsigned char byte = bitsToByte(bits);
				printf("%c", byte);
				return 0;
}
*/
