#include"Header.h"
#include<stdio.h>
#include<stdlib.h> 


int main(void) {
	int sum;
	int N;
	
	int *arr = ReadText("file.txt", &sum, &N);

	int* answer = (int*)calloc(N ,sizeof(int));
	
	
	if (SearchSet(arr, answer, N-1, sum)) {
		WriteText("file2.txt", answer, N);
	}
	else {
		FILE* f;
		fopen_s(&f, "file.txt", "w");
		if (f == NULL) return;
		fprintf(f, "%d", 0);
		fclose(f);
	}

	return 0;
}

