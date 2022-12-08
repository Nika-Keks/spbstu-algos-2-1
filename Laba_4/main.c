#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"


void main() {

    FILE* file = fopen("matrix_test.txt", "r");

    if ((file = fopen("matrix_test.txt", "r")) == NULL) {
        printf("can't open file\n");
        exit(1);
    }
    printf("Maze with cells 0 or 1\n 0 - wall\n 1 - pass\n");

    int n = CountOfColumns(file);
    int m = CountOfLines(file);

    int** matrix = CreateArrayFromFile(file, n, m);
    PrintMatrix(matrix, n, m);

    int** Road = CreateArray(n, m);

    int start_x = 0;
    int start_y = 0;
    int end_x = n;
    int end_y = m;
    int len = 0;
    int min_len = n * m;
    short flag = 0;

    Steps(start_x, start_y, end_x, end_y, Road, len, matrix, &min_len,&flag);
    if (min_len == n * m) {
        printf("\nUnfortunetully, it's impossible to reach the finish - Check finish coordinates");
    }
    else { printf("\nminimal length of path through the maze is %i\n\n", min_len); }

    FreeArray(Road, n);
    FreeArray(matrix, n);
    fclose(file);

    return 0;
}