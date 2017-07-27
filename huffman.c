#include "huffman.h"
#include "list.h"
#include "tree.h"

stuff* newStuff(int weight, char* label) {
				stuff* res = malloc(sizeof(stuff));
				res->weight = weight;
				res->label = label;
				return res;
}

int getWeight(listNode* node) {
				return node->data->data->weight;
}

listNode* extractSmallestWeight(listNode* forest, treeNode* x) { /* returns the new list head, puts smallest weight treeNode in x */
				if (forest == NULL) {
								x = NULL;
								return forest;
				}
				/* find smallest */
				listNode* prev = forest;
				listNode* look = forest->next;
				listNode* smal = forest;
				listNode* befo = NULL;
				while(look != NULL) {
								if (getWeight(look) < getWeight(smal)) {
												smal = look;
												befo = prev;
								}
								prev = look;
								look = look->next;
				}
				/* assign x to data of smal */
				x = smal->data;
				/* remove smal from list */
				listNode* newForest = forest;
				if (befo == NULL) {
								/* smallest is first, remove it */
								newForest = forest->next;
				} else {
								befo->next = smal->next;
				}
				free(smal);
				return newForest;
}

listNode* add(listNode* forest, treeNode* data) { /* add data to list */
				listNode* newForest = newListNode(forest, sizeof(data), data);
				return newForest;
}

treeNode* createHuffTree(listNode* forest) { /* forest is a list of treeNodes, each of which has a stuff as data */
				/* continue until there is only one node in list, return it */
				while(lengthList(forest) > 1) {
								/* find the two with the smallest weight, remove from list */
								treeNode* x,y;
								forest = extractSmallestWeight(forest, x);
								forest = extractSmallestWeight(forest, y);
								/* combine them into one node, add to list */
								stuff* newStuf = newStuff((x->data->weight) + (y->data->weight), NULL);
								treeNode* newNode = newTreeNode(x, y, newStuf);
								forest = add(forest, newNode);
				}
				treeNode* tree = forest->data;
				free(forest);
				return tree;
}

