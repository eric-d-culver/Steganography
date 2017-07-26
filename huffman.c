#include "huffman.h"
#include "list.h"
#include "tree.h"

stuff* newStuff(int weight, char* label) {
				stuff* res = malloc(sizeof(stuff));
				res->weight = weight;
				res->label = label;
				return res;
}

treeNode* createHuffTree(listNode* forest) { /* forest is a list of treeNodes, each of which has a stuff as data */
				/* find the two with the smallest weight, remove from list */
				/* combine them into one node, add to list */
				/* continue until there is only one node in list, return it */
}

