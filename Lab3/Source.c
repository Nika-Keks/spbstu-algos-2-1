#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#pragma warning(disable:4996)

/**
 * Matrix size Structure
 */
typedef struct sizee_t {
    int stolb;
    int strok;
} sizee_t;
/**
 * Structure for a list (where one list is a column)
 * index - the line number of the element
 */
typedef struct stolbec_t {
    int elem;
    int index;
    struct stolbec_t* next;
} stolbec_t;

/**
 * File verification function
 */
void Error(FILE* ptr) {
    if (ptr == EOF) {
        printf("\nYps\n");
        exit(0);
    }
}

/**
 * The function of creating the zero head of the list
 */
stolbec_t* create(void) {
    stolbec_t* tmp = (stolbec_t*)malloc(sizeof(stolbec_t));
    tmp->elem = 0;
    tmp->index = 0;
    tmp->next = NULL;
    return (tmp);
}

/**
 * Adding a non-zero element to lists
 */
void add_element_vstavka(stolbec_t* head, int value, int index) {
    stolbec_t* begunok = head;
    while (begunok->next != NULL) {
        begunok = begunok->next;
    }
    stolbec_t* tmp = (stolbec_t*)malloc(sizeof(stolbec_t));
    tmp->elem = value;
    tmp->index = index;
    begunok->next = tmp;
    tmp->next = NULL;
}

/**
 * Reading a matrix from a file
 */
stolbec_t* ReadFile(char const* filename, sizee_t* Size) {
    FILE* ptr = fopen(filename, "r+");
    //Error(ptr);
    fscanf(ptr, "%d %d\n", &Size->strok, &Size->stolb);
    stolbec_t* Arr = malloc(sizeof(stolbec_t) * Size->stolb);
    for (int i = 0; i < Size->stolb; i++) {
        Arr[i] = *create();
    }
    int buf = 0;
    for (int j = 0; j < Size->strok; j++) {
        for (int i = 0; i < Size->stolb; i++) {
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
int Poisk(stolbec_t* head, int index) {
    if (head->next == NULL) {
        return 0;
    }
    stolbec_t* begunok = head;
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
stolbec_t* Multi(stolbec_t* Matrix1, sizee_t Size1, stolbec_t* Matrix2, sizee_t Size2, sizee_t* Size3) {
    Size3->strok = Size1.strok;
    Size3->stolb = Size2.stolb;
    stolbec_t* Arr = malloc(sizeof(stolbec_t) * Size3->stolb * Size3->strok);
    for (int i = 0; i < Size3->stolb; i++) {
        Arr[i] = *create();
    }
    for (int Begun_Strok1 = 0; Begun_Strok1 < Size1.strok; Begun_Strok1++) {
        for (int Begun_Stolb2 = 0; Begun_Stolb2 < Size2.stolb; Begun_Stolb2++) {
            int S = 0;
            for (int Begun_v_stroke1 = 0; Begun_v_stroke1 < Size1.stolb; Begun_v_stroke1++) {
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
void Print(stolbec_t* Matrix, sizee_t Size) {
    int a;
    for (int Begun_Strok = 0; Begun_Strok < Size.strok; Begun_Strok++) {
        for (int Begun_Stolb = 0; Begun_Stolb < Size.stolb; Begun_Stolb++) {
            a = Poisk(Matrix + Begun_Stolb, Begun_Strok + 1);
            printf("%d ", a);
        }
        printf("\n");
    }
}

int main() {
    sizee_t Size1;
    sizee_t Size2;
    sizee_t Size3;
    stolbec_t* Matrix1 = ReadFile("Matrix1.txt", &Size1);
    printf("Matrix 1:\n");
    Print(Matrix1, Size1);

    stolbec_t* Matrix2 = ReadFile("Matrix2.txt", &Size2);
    printf("Matrix 2:\n");
    Print(Matrix2, Size2);

    stolbec_t* Matrix3 = Multi(Matrix1, Size1, Matrix2, Size2, &Size3);
    printf("Multi (Size: %d*%d): \n", Size3.strok, Size3.stolb);
    Print(Matrix3, Size3);


    return 0;
}