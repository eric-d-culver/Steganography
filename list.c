#include <stdlib.h>
#include "list.h"

listNode* newListNode(listNode* next, size_t size, void* data) {
				listNode* res = (listNode*) malloc(sizeof(listNode));
				res->next = next;
				res->size = size;
				res->data = data;
				return res;
}

listNode* copyListNode(listNode* orig) {
				if (orig == NULL) {
								return NULL;
				}
				void* newData = malloc(orig->size);
				memcpy(newData, orig->data, orig->size);
				listNode* copy = newListNode(orig->next, orig->size, newData);
				return copy;
}

listNode* copyList(listNode* head) {
				if (head == NULL) {
								return NULL;
				}
				listNode* newHead = copyListNode(head);
				newHead->next = copyList(head->next);
				return newHead;
}
