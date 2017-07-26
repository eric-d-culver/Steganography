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

list* copyList(list* head) {
				if (head == NULL) {
								return NULL;
				}
				listNode* newHead = copyListNode(head);
				newHead->next = copyList(head->next);
				return newHead;
}

list* combineLists(list* head1, list* head2) {
				if (head1 == NULL) {
								return head2;
				}
				/* find end of list1 */
				listNode* temp1 = head1;
				listNode* temp2 = head1->next;
				while (temp2 != NULL) {
								temp1 = temp2;
								temp2 = temp2->next;
				}
				/* assign to list2 */
				temp1->next = head2;
				return head1;
}

int lengthList(list* head) {
				if (head == NULL) {
								return 0;
				}
				int len = 0;
				listNode* temp = head;
				while(temp != NULL) {
								temp = temp->next;
								len++;
				}
				return len;
}
