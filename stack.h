#ifndef STACK_H
#define STACK_H
#include "list.h"

typedef listNode stack;

stack* push(stack* top, char* data);

stack* pop(stack* top, char* res);

stack* copyStack(stack* top);

#endif
