#ifndef HUFFMAN_H
#define HUFFMAN_H

typedef struct {
				int weight;
				char* label;
} stuff;

stuff* newStuff(int weight, char* label);

#endif
