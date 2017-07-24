#ifndef STACK_H
#define STACK_H

typedef struct _node {
				struct _node* next;
				char* data;
} node;

node* push(node* top, char* data);

node* pop(node* top, char* res);

node* copyStack(node* top);

#endif
