#ifndef LIST_H
#define LIST_H
#include <stddef.h>

typedef struct _listNode {
				struct _listNode* next;
				size_t size; /* of the data stored with list node */
				void* data;
} listNode;

typedef listNode list;

listNode* newListNode(listNode* next, size_t size, void* data); /* returns pointer to new listNode with this data */

listNode* copyListNode(listNode* orig); /* returns pointer to copy of orig listNode. Also copies data. */

list* copyList(list* head); /* returns pointer to head of new list. Copies entire list starting with head. */

list* combineLists(list* head1, list* head2); /* returns pointer to head of new list with the nodes of list1 followed by nodes of list2. */

int lengthList(list* head); /* returns length of list starting at head */

#endif
