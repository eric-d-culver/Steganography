#include "stack.h"
#include <stdlib.h>
#include <string.h>

node* push(node* top, char* data) {
				node* newNode;
				newNode = (node*) malloc(sizeof(node));
				newNode->next = top;
				newNode->data = data;
				return newNode;
}

node* pop(node* top, char* res) {
				res = top->data;
				node* newTop = top->next;
				free(top);
				return newTop;
}

node* copyStack(node* top) {
				node* newTop = (node*) malloc(sizeof(node));
				strcpy(newTop->data, top->data);
				newTop->next = copyStack(top->next);
				return newTop;
}
