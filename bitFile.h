#ifndef BITFILE_H
#define BITFILE_H

#include <stdio.h>

unsigned char* byteToBits(unsigned char byte);

unsigned char bitsToByte(unsigned char* bits);

typedef struct {
				FILE* file;
				unsigned char* bits;
				unsigned char* (*read)(const void* self, int numBits);
				unsigned char* (*peek)(const void* self, int numBits);
				int (*isEOF)(const void* self);
} bitRead;

typedef struct {
				FILE* file;
				unsigned char* bits;
				void (*write)(const void* self, unsigned char* bits);
} bitWrite;

bitRead* initBitRead(FILE* file);
bitWrite* initBitWrite(FILE* file);

#endif
