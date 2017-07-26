#include "list.h"
#include "tree.h"

typedef struct _stuff {
				int weight;
				char* label;
} stuff;

stuff* newStuff(int weight, char* label) {
				stuff* res = malloc(sizeof(stuff));
				res->weight = weight;
				res->label = label;
				return res;
}
