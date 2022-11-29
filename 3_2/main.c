#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"

int main() {
	char* f = "input.txt";
	List* list = CreateListFromFile(f);
	List** Array = FormArray(list);
	List* buf = list;
	while (buf->next != NULL) {
		InsertToArray(buf->point, buf->next->point, Array, list);
		buf = buf->next;
	}
	InsertToArray(buf->point, list->point, Array, list);
	CompleteMatrix(Array, list);
	return 0;
}