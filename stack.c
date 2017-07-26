#include "stack.h"
#include <stdlib.h>
#include <string.h>

stack* push(stack* top, char* data) {
				size_t size = sizeof(char)*strlen(data);
				stack* newNode = newListNode(top, size, (void*) data);
				return newNode;
}

stack* pop(stack* top, char* res) {
				res = (char*) top->data;
				stack* newTop = top->next;
				free(top);
				return newTop;
}

stack* copyStack(stack* top) {
				stack* newTop = copyList(top);
				return newTop;
}
