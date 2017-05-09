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

typedef struct {
				FILE* file;
				dynaArray* bits;
				unsigned char* (*read)(const void* self, int numBits);
				unsigned char* (*peek)(const void* self, int numBits);
				int (*isEOF)(const void* self);
} bitRead;

typedef struct {
				FILE* file;
				dynaArray* bits;
				void (*write)(const void* self, unsigned char* bits);
} bitWrite;

bitRead* initBitRead(FILE* file);
bitWrite* initBitWrite(FILE* file);
FILE* finiBitRead(bitRead* self);
FILE* finiBitWrite(bitWrite* self);

#endif
