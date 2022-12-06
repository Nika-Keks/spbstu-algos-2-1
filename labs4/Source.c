#include"Header.h"
#include<stdio.h>
#include<stdlib.h> 
#pragma warning(disable:4996)


int main(void) {
	int sum;
	int N;
	int main_key = 0;

	int *arr = ReadText("file.txt", &sum, &N);

	int* answer = (int*)calloc(N ,sizeof(int));//filling the auxiliary array with zeros
	
	
	if (SearchSet(arr, answer, N-1, sum, &main_key)) {//if it was possible to find a subsequence, write it to a file
		WriteText("file2.txt", answer, N);
	}
	else {//otherwise, we write zero to the file
		FILE* f;
		f = fopen("file2.txt", "w");
		if (f == NULL) return 0;
		fprintf(f, "%d", 0);
		fclose(f);
	}

	return 0;
}

