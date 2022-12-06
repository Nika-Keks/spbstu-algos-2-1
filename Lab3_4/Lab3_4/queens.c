#include <stdio.h>
#include <stdlib.h>
#include "queens.h"

#pragma warning(disable:4996)

#define QUEENS_INIT_VALUE -1

#define NotNull(ptr) notNull(ptr, __LINE__)
#define SafeMalloc(size) safeMalloc(size, __LINE__)

void* notNull(void* ptr, int line) {
	if (ptr == NULL) {
		printf("Null pointer at %i\n", line);
		exit(1);
	}
	return ptr;
}

void* safeMalloc(int size, int line) {
	return notNull(malloc(size), line);
}

int** boardCreate(int n) {
	int** A = malloc(n * sizeof(int*) + n * n * sizeof(int));
	char* p = A;
	p += n * sizeof(int*);
	for (int i = 0; i < n; i++) {
		A[i] = p + i * n * sizeof(int);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j] = 0;
			//printf("%p ", &(A[i][j]));
		}
		//printf("\n");
	}
	return A;
}

void boardDestroy(int** board, int n) {
	for (int i = 0; i < n; i++) {
		free(board[i]);
	}
	free(board);
}

void boardPrint(int** board, int n) {
	printf("----------------\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%i ", board[i][j]);
		}
		printf("\n");
	}
	printf("----------------\n");
}

int* queensCreate(int n) {
	int* queens = SafeMalloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		queens[i] = QUEENS_INIT_VALUE;
	}
	return queens;
}

void queensDestroy(int* queens) {
	free(queens);
}

void queensPrintMatrix(int* queens, int n) {
	//printf("Printing queens...\n");
	FILE* file = fopen("matrixOutput.txt", "w");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (j == queens[i]) {
				fprintf(file, "1 ");
			}
			else {
				fprintf(file, "0 ");
			}
		}
		fprintf(file, "\n");
	}
	fclose(file);
	//printf("----------------\n");
}

int solved = 0;

int* sumsInit(int n) {
	int* sums = SafeMalloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		sums[i] = 0;
	}
	return sums;
}

void sumsDestroy(int* sums) {
	free(sums);
}

int firstUnoccupiedRow(int* queens, int n) {
	for (int i = 0; i < n; i++) {
		if (queens[i] == QUEENS_INIT_VALUE) {
			return i;
		}
	}
	printf("All rows are occupied.\n");
	exit(1);
}

int unoccupiedRowWithLeastFreeSquares(int** board, int* queens, int n) {
	//printf("Looking for unoccupied row with least free squares\n Current queens: \n");
	//for (int i = 0; i < n; i++) {
	//	printf("(%i; %i) ", i, queens[i]);
	//}
	//printf("\n");
	int* sums = sumsInit(n);
	int row = firstUnoccupiedRow(queens, n);
	for (int i = 0; i < n; i++) {
		int cur = 0;
		for (int j = 0; j < n; j++) {
			if (board[i][j] == 0) {
				sums[i] += 1;
			}
		}
		if (sums[i] < sums[row] && queens[i] == QUEENS_INIT_VALUE && sums[i] > 0) {
			row = i;
		}
	}
	//printf("resulting sums for rows:\n");
	/*for (int i = 0; i < n; i++) {
		printf("(%i, %i) ", i, sums[i]);
	}
	printf("\n");*/
	sumsDestroy(sums);
	return row;
}

void boardOccupy(int** board, int n, int row, int col, int count) {
	//printf("Occupying board for %i row, %i column, %i queen\n", row, col, count);
	for (int j = 0; j < n; j++) {
		if (board[row][j] == 0) {
			board[row][j] = count;
		}
	}
	for (int i = 0; i < n; i++) {
		if (board[i][col] == 0) {
			board[i][col] = count;
		}
	}
	for (int k = 0; k < n; k++) {
		if (row - k >= 0 && col - k >= 0 && board[row - k][col - k] == 0) {
			board[row - k][col - k] = count;
		}
		if (row - k >= 0 && col + k < n && board[row - k][col + k] == 0) {
			board[row - k][col + k] = count;
		}
		if (row + k < n && col - k >= 0 && board[row + k][col - k] == 0) {
			board[row + k][col - k] = count;
		}
		if (row + k < n && col + k < n && board[row + k][col + k] == 0) {
			board[row + k][col + k] = count;
		}
	}
	//boardPrint(board, n);
}

void boardUnoccupy(int** board, int n, int row, int col, int count) {
	//printf("Unoccupying board for %i row, %i column, %i queen, size is %i\n", row, col, count, n);
	//boardPrint(board, n);
	for (int j = 0; j < n; j++) {
		if (board[row][j] == count) {
			board[row][j] = 0;
		}
	}
	for (int i = 0; i < n; i++) {
		if (board[i][col] == count) {
			board[i][col] = 0;
		}
	}
	for (int k = 0; k < n; k++) {
		if (row - k >= 0 && col - k >= 0 && board[row - k][col - k] == count) {
			board[row - k][col - k] = 0;
		}
		if (row - k >= 0 && col + k < n && board[row - k][col + k] == count) {
			board[row - k][col + k] = 0;
		}
		if (row + k < n && col - k >= 0 && board[row + k][col - k] == count) {
			board[row + k][col - k] = 0;
		}
		if (row + k < n && col + k < n && board[row + k][col + k] == count) {
			board[row + k][col + k] = 0;
		}
	}
	//boardPrint(board, n);
}

void placeQueens(int** board, int* queens, int cur, int n) {
	if (cur > n) {
		//printf("Found solution for num %i\n", cur);
		solved = 1;
		FILE* file = fopen("output.txt", "w");
		for (int i = 0; i < n; i++) {
			fprintf(file, "%i %i\n", i, queens[i]);
		}
		fclose(file);
		queensPrintMatrix(queens, n);
		return;
	}
	if (solved != 1) {
		//printf("Solution not found yet, finding the row with least squares: \n");
		int row = unoccupiedRowWithLeastFreeSquares(board, queens, n);
		//printf("Row with least squares is %i\n", row);
		for (int j = 0; j < n; j++) {
			if (board[row][j] == 0) {
				queens[row] = j;
				//printf("Placed the %i queen on %i\n", cur, j);
				boardOccupy(board, n, row, j, cur);
				placeQueens(board, queens, cur + 1, n);
				//printf("Queen %i was placed, the board: \n", cur + 1);
				//boardPrint(board, n);
				queens[row] = QUEENS_INIT_VALUE;
				boardUnoccupy(board, n, row, j, cur);
				if (solved == 1) {
					return;
				}
			}
		}
	}

}