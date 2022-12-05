#include <stdio.h>
#include <stdlib.h>
#include "header.h"

#pragma warning(disable:4996)

int Size_X(FILE* file) {
    char x = 0;
    int length_col = 0;
    while (!feof(file)) {
        x = fgetc(file);
        if (x == '\n') {
            fseek(file, 0, SEEK_SET);
            return length_col;
        }
        if (x == '1' || x == '0') length_col++;
    }
}

int Size_Y(FILE* file) {
    char y = 0;
    int length_row = 0;
    while (!feof(file)) {
        y = fgetc(file);
        if (y == '\n') length_row++;
    }
    fseek(file, 0, SEEK_SET);
    return length_row;
}

int CheckNode(int x, int y, int** visited, int** matrix, int n, int m) {
    if (x < 0 || y < 0 || x >= n || y >= m) return 0;
    if (matrix[x][y] == 0 || visited[x][y] == 1) return 0;

    return 1;
}

void Visit(int x, int y, int end_x, int end_y, int** visited, int length, int** matrix, int* min_length) {
    if (x == (end_x - 1) && y == (end_y - 1)) {
        if (length < *min_length) *min_length = length;
        return;
    }
    visited[x][y] = 1;
    length++;

    //направо
    if (CheckNode(x + 1, y, visited, matrix, end_x, end_y)) {
        Visit(x + 1, y, end_x, end_y, visited, length, matrix, min_length);
    }

    //вниз
    if (CheckNode(x, y + 1, visited, matrix, end_x, end_y)) {
        Visit(x, y + 1, end_x, end_y, visited, length, matrix, min_length);
    }

    //налево
    if (CheckNode(x - 1, y, visited, matrix, end_x, end_y)) {
        Visit(x - 1, y, end_x, end_y, visited, length, matrix, min_length);
    }

    //вверх
    if (CheckNode(x, y - 1, visited, matrix, end_x, end_y)) {
        Visit(x, y - 1, end_x, end_y, visited, length, matrix, min_length);
    }

    visited[x][y] = 0;
    length--;
}

int** CreateArray(int n, int m) {
    int** Array = (int**)malloc(n * sizeof(int*));
    if (Array == NULL) {
        printf("memory allocation error\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        Array[i] = (int*)malloc(m * sizeof(int));
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
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%i ", Matrix[i][j]);
        }
        printf("\n");
    }
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

void FindPath(char const* filename) {
    FILE* file;

    if ((file = fopen(filename, "r")) == NULL) {
        printf("cannot open file\n");
        exit(1);
    }

    int n = Size_X(file);
    int m = Size_Y(file);

    int** matrix = CreateArrayFromFile(file, n, m);
    printf("the maze:\n\n");
    PrintMatrix(matrix, n, m);

    int** visited = CreateArray(n, m);

    int start_x = 0;
    int start_y = 0;
    int length = 0;
    int min_length = n * m;

    Visit(start_x, start_y, n, m, visited, length, matrix, &min_length);
    printf("\nminimal length of path through the maze is %i\n\n", min_length);
    FreeArray(visited, n);
    FreeArray(matrix, n);
    fclose(file);

}
