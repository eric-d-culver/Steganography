#ifndef BITFILE_H
#define BITFILE_H

#include <stdio.h>

unsigned char* byteToBits(unsigned char byte);

unsigned char bitsToByte(unsigned char* bits);

typedef struct {
				unsigned char* array;
				int num_elements;
				int num_allocated;
} dynaArray;

typedef struct _bitRead {
				FILE* file;
				dynaArray* bits;
				unsigned char* (*read)(struct _bitRead* self, int numBits);
				unsigned char* (*peek)(struct _bitRead* self, int numBits);
				int (*isEOF)(const struct _bitRead* self);
} bitRead;

typedef struct _bitWrite {
				FILE* file;
				dynaArray* bits;
				void (*write)(struct _bitWrite* self, unsigned char* bits, int numBits);
} bitWrite;

bitRead* initBitRead(FILE* file);
bitWrite* initBitWrite(FILE* file);
FILE* finiBitRead(bitRead* self);
FILE* finiBitWrite(bitWrite* self);

#endif
