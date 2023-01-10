#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#pragma warning(disable:4996)

/**
 * Структура размера матрицы
 */
typedef struct sizee_t {
    int stolb;
    int strok;
} sizee_t;
/**
 * Структура для списка (где один список - столбик)
 * index - номер сторки элемента
 */
typedef struct stolbec_t {
    int elem;
    int index;
    struct stolbec_t* next;
} stolbec_t;

/**
 * Функция проверки файла
 * @param ptr - файл
 */
void Error(FILE* ptr) {
    if (ptr == EOF) {
        printf("\nYps\n");
        exit(0);
    }
}

/**
 * Функция создания нулевой головы списка
 * @return - ссылка на голову
 */
stolbec_t* create(void) {
    stolbec_t* tmp = (stolbec_t*)malloc(sizeof(stolbec_t));
    tmp->elem = 0;
    tmp->index = 0;
    tmp->next = NULL;
    return (tmp);
}

/**
 * Добавление не нулевого элемента в списков
 * @param head - голова списка (столбец)
 * @param value - значение нового элемента
 * @param index - номер строки нового элемента
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
 * Считывание матрицы из файла
 * @param filename - название файла
 * @param Size - размер матрицы
 * @return - массив списков не нулевых элементов
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
 * Поиск элементы с заданной строкой
 * @param head - голова списка (столбец)
 * @param index - заданный номер строки
 * @return - значение элемента в этой строке в этом столбце
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
 * Функция произведения двух матриц
 * @param Matrix1 - первая матрица
 * @param Size1 - размер первой матрицы
 * @param Matrix2 - вторая матрица
 * @param Size2 - размер второй матрицы
 * @param Size3 - размер матрицы результата
 * @return - результат произведения (массив списков)
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
 * Дополнительная функция вывода матрицы
 * @param Matrix - массив списков
 * @param Size - размер матрицы
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