#ifndef LIST_H
#define LIST_H
#include <stddef.h>

typedef struct _listNode {
				struct _listNode* next;
				size_t size; /* of the data stored with list node */
				void* data;
} listNode;

listNode* newListNode(listNode* next, size_t size, void* data); /* returns pointer to new listNode with this data */

listNode* copyListNode(listNode* orig); /* returns pointer to copy of orig listNode. Also copies data. */

listNode* copyList(listNode* head); /* returns pointer to head of new list. Copies entire list starting with head. */

#endif
