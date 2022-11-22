#include"Header.h"
#include<stdio.h>
#include<stdlib.h> 
#pragma warning(disable:4996)


int main(void) {
	int sum;
	int N;
	int main_key = 0;

	int *arr = ReadText("file.txt", &sum, &N);

	int* answer = (int*)calloc(N ,sizeof(int));
	
	
	if (SearchSet(arr, answer, N-1, sum, &main_key)) {
		WriteText("file2.txt", answer, N);
	}
	else {
		FILE* f;
		f = fopen("file2.txt", "w");
		if (f == NULL) return;
		fprintf(f, "%d", 0);
		fclose(f);
	}

	return 0;
}

