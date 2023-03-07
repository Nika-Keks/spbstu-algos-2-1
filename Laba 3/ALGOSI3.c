#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#pragma warning(disable:4996)

/*
 * Size of the matrix
 */
typedef struct size_matrix {
    int columns;
    int lines;
} size_matrix;
/**
 * Structure for column which count as list
 * Indexing by line number of element
 */
typedef struct column {
    int elem;
    int index;
    struct column* next;
} column;

/**
 * File verification function
 */
void Error(FILE* ptr) {
    if (ptr == EOF) {
        printf("\nError\n");
        exit(0);
    }
}

/**
 * The function of creating the zero head of the list
 */
column* create(void) {
    column* tmp = (column*)malloc(sizeof(column));
    tmp->elem = 0;
    tmp->index = 0;
    tmp->next = NULL;
    return (tmp);
}

/**
 * Adding a non-zero element to lists
 */
void add_element_vstavka(column* head, int value, int index) {
    column* begunok = head;
    while (begunok->next != NULL) {
        begunok = begunok->next;
    }
    column* tmp = (column*)malloc(sizeof(column));
    tmp->elem = value;
    tmp->index = index;
    begunok->next = tmp;
    tmp->next = NULL;
}

/**
 * Reading a matrix from a file
 */
column* ReadFile(char const* filename, size_matrix* Size) {
    FILE* ptr = fopen(filename, "r+");
    //Error(ptr);
    fscanf(ptr, "%d %d\n", &Size->lines, &Size->columns);
    column* Arr = malloc(sizeof(column) * Size->columns);
    for (int i = 0; i < Size->columns; i++) {
        Arr[i] = *create();
    }
    int buf = 0;
    for (int j = 0; j < Size->lines; j++) {
        for (int i = 0; i < Size->columns; i++) {
            fscanf(ptr, "%d\n", &buf);
            if (buf != 0) {
                add_element_vstavka(&Arr[i], buf, j + 1);
            }
        }
    }
    fclose(ptr);
    return Arr;
}

/**
 * Search for items with a given string
 */
int Poisk(column* head, int index) {
    if (head->next == NULL) {
        return 0;
    }
    column* begunok = head;
    while (begunok->index < index && begunok->next != NULL) {
        begunok = begunok->next;
    }
    if (begunok->index == index) {
        return begunok->elem;
    }
    else {
        return 0;
    }
}

/**
 * The function of the product of two matrices
 */
column* Multi(column* Matrix1, size_matrix Size1, column* Matrix2, size_matrix Size2, size_matrix* Size3) {
    Size3->lines = Size1.lines;
    Size3->columns = Size2.columns;
    column* Arr = malloc(sizeof(column) * Size3->columns * Size3->lines);
    for (int i = 0; i < Size3->columns; i++) {
        Arr[i] = *create();
    }
    for (int Begun_Strok1 = 0; Begun_Strok1 < Size1.lines; Begun_Strok1++) {
        for (int Begun_Stolb2 = 0; Begun_Stolb2 < Size2.columns; Begun_Stolb2++) {
            int S = 0;
            for (int Begun_v_stroke1 = 0; Begun_v_stroke1 < Size1.columns; Begun_v_stroke1++) {
                S = S + Poisk(Matrix1 + Begun_v_stroke1, Begun_Strok1 + 1) *
                    Poisk(Matrix2 + Begun_Stolb2, Begun_v_stroke1 + 1);
            }
            add_element_vstavka(Arr + Begun_Stolb2, S, Begun_Strok1 + 1);
        }
    }
    return Arr;
}

/**
 * Additional matrix output function
 */
void Print(column* Matrix, size_matrix Size) {
    int a;
    for (int Begun_Strok = 0; Begun_Strok < Size.lines; Begun_Strok++) {
        for (int Begun_Stolb = 0; Begun_Stolb < Size.columns; Begun_Stolb++) {
            a = Poisk(Matrix + Begun_Stolb, Begun_Strok + 1);
            printf("%d ", a);
        }
        printf("\n");
    }
}

int main() {
    size_matrix Size1;
    size_matrix Size2;
    size_matrix Size3;
    column* Matrix1 = ReadFile("Matrix_1.txt", &Size1);
    printf("Matrix 1:\n");
    Print(Matrix1, Size1);

    column* Matrix2 = ReadFile("Matrix_2.txt", &Size2);
    printf("Matrix 2:\n");
    Print(Matrix2, Size2);

    column* Matrix3 = Multi(Matrix1, Size1, Matrix2, Size2, &Size3);
    printf("Multi (Size: %d*%d): \n", Size3.lines, Size3.columns);
    Print(Matrix3, Size3);


    return 0;
}