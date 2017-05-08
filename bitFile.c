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

bitRead* initBitRead(FILE* file) {
				bitRead* self = malloc(sizeof(bitRead));
				self->file = file;
				return self;
}

bitWrite* initBitWrite(FILE* file) {
				bitWrite* self = malloc(sizeof(bitWrite));
				self->file = file;
				return self;
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
