#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include "Header.h"



int CountOfColumns(FILE* file) {
    char x;
    int cnt = 0;
    while (!feof(file)) {
        x = fgetc(file);
        if (x == '\n') {
            fseek(file, 0, SEEK_SET);
            return cnt;
        }
        if (x == '1' || x == '0') cnt++;
    }
    return 0;
}

int CountOfLines(FILE* file) {
    char y;
    int cnt = 0;
    while (!feof(file)) {
        y = fgetc(file);
        if (y == '\n') cnt++;
    }
    fseek(file, 0, SEEK_SET);
    return cnt;
}

int Is_Node(int x, int y, int** Road, int** matrix, int n, int m) {
    if (x < 0 || y < 0 || x >= n || y >= m) return 0;
    if (matrix[x][y] == 0 || Road[x][y] == 1) return 0;

    return 1;
}

void Steps(int x, int y, int end_x, int end_y, int** Road, int len, int** matrix, int* min_len, short* flag) {
    if (*flag == 0) {
        if (matrix[x][y] == 0) {
            printf("\nInvalid Enter (it can't be a 0)");
            exit(1);
        }
        if (matrix[x][y] == 1) {
            *flag=1;
        }
    }
    if (x == (end_x - 1) && y == (end_y - 1)) {
        if (len < *min_len) *min_len = len;
        return;
    }
    Road[x][y] = 1;
    len++;

    
    if (Is_Node(x + 1, y, Road, matrix, end_x, end_y)) {
        Steps(x + 1, y, end_x, end_y, Road, len, matrix, min_len,flag);
    }

    
    if (Is_Node(x, y + 1, Road, matrix, end_x, end_y)) {
        Steps(x, y + 1, end_x, end_y, Road, len, matrix, min_len, flag);
    }

    
    if (Is_Node(x - 1, y, Road, matrix, end_x, end_y)) {
        Steps(x - 1, y, end_x, end_y, Road, len, matrix, min_len, flag);
    }

    
    if (Is_Node(x, y - 1, Road, matrix, end_x, end_y)) {
        Steps(x, y - 1, end_x, end_y, Road, len, matrix, min_len, flag);
    }

    Road[x][y] = 0;
    len--;
}

int** CreateArray(int n, int m) {
    int** Array = malloc(n * sizeof(int*));
    if (Array == NULL) {
        printf("memory allocation error\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        Array[i] = malloc(m * sizeof(int));
        if (Array[i] == NULL) {
            printf("memory allocation error\n");
            exit(1);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Array[i][j] = 0;
        }
    }
    return Array;
}

void FreeArray(int** Array, int n) {
    for (int i = 0; i < n; i++) free(Array[i]);
    free(Array);
}

void PrintMatrix(int** Matrix, int n, int m) {
    printf("Enter ->");
    for (int i = 0; i < m; i++) {
        if (i == 0) {
            printf(" ");
        }
        else {
            printf("         ");
        }
        for (int j = 0; j < n; j++) {
            printf("%i ", Matrix[i][j]);
        }
        if (i < m-1) {
            printf("\n");
        }
    }
    printf("<- Exit\n");
 
}

int** CreateArrayFromFile(FILE* file, int n, int m) {
    int** Array = CreateArray(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char node = 0;
            if (!fscanf(file, "%c ", &node)) exit(1);
            if (node == '1') Array[i][j] = 1;
        }
    }
    return Array;
}
