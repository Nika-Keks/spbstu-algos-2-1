#include "main.h"

int main(void) {
	char* f = "input.txt";
	int bound = StrCounter(f);

	List* list = AlterationListFromFile(f, bound);
	PrintListComplited(list);

	printf("\ncoincidence check\n");
	Date* input_date = InputFromScreen();
	CheckDate(list, input_date);

	return 0;
}