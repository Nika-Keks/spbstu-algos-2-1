#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
/**
 * Проверка ошибки файла
 * @param ptr - входной файл
 */
void Error(FILE *ptr) {
    if (ptr == EOF) {
        printf("\nYps :(\n");
        exit(1);
    }
}
/**
 * Считывание размера шахматной доски
 * @param filename - файл входных данных
 * @return - размер шахматной доски
 */
int Read_size(char const *filename) {
    FILE *ptr = fopen(filename, "r");
    Error(ptr);
    int N;
    fscanf(ptr, "%d", &N);
    fclose(ptr);
    return N;
}
/**
 * Структура координат ферзя
 */
typedef struct ferz_t {
    int x;
    int y;
} ferz_t;
/**
 * Поиск столбика с неибольшим количестов забитых клеток
 * @param m - сколько ферзей поставлено на доску + 1
 * @param Ferz - массив координат всех ферзей
 * @param N - размер доски
 * @return номер столбца с наибольшей забитостью
 */
int Stolbik_s_maxY(int m, ferz_t *Ferz, int N) {
    int Max = 0;
    int Index_s_max = 0;
    for (int colon = 0; colon < N; colon++) {
        int flag_colon = 0;
        for (int begun_Ferz = 0; begun_Ferz < m; begun_Ferz++) {
            if (Ferz[begun_Ferz].x == colon) {
                flag_colon = 1;
                break;
            }
        }
        if (flag_colon != 1) {
            int Sum_Colon = 0;
            for (int begun_y = 0; begun_y < N; begun_y++) {
                for (int begun_Ferz = 0; begun_Ferz < m; begun_Ferz++) {
                    if (Ferz[begun_Ferz].x == colon || Ferz[begun_Ferz].y == begun_y ||
                        abs(colon - Ferz[begun_Ferz].x) == abs(begun_y - Ferz[begun_Ferz].y)) {
                        Sum_Colon++;
                        break;
                    }
                }
            }
            if (Max < Sum_Colon) {
                Max = Sum_Colon;
                Index_s_max = colon;
            }
        }
    }
    return Index_s_max;
}
/**
 * Главная часть программы, расстановка ферзей рекурсией
 * @param m - шаг рекурсии (сколько ферзей уже поствили + 1)
 * @param Ferz - массив координат всех ферзей
 * @param N - размер доски
 * @param flag - флаг окончания рекурсии
 * @return - массив заполненнных координат всех ферзей
 */
ferz_t *Recurs(int m, ferz_t *Ferz, int N, int *flag) {
    if (m == N) {
        *flag = 1;
        return Ferz;
    } else {
        if (m < 3) {
            Ferz[m].x = m;
        } else {
            Ferz[m].x = Stolbik_s_maxY(m, Ferz, N);
        }
        for (int j = 0; j < N; j++) {
            Ferz[m].y = j;
            int biot = 0;
            for (int begun_arr = 0; begun_arr < m; begun_arr++) {
                if (Ferz[begun_arr].y == Ferz[m].y ||
                    abs(Ferz[m].x - Ferz[begun_arr].x) == abs(Ferz[m].y - Ferz[begun_arr].y)) {
                    biot = 1;
                    break;
                }
            }

            if (biot == 0) {
                Recurs(m + 1, Ferz, N, flag);
            }
            if (*flag == 1) {
                return Ferz;
            }
        }
    }
}
/**
 * Функция записи координат ферзей в файл
 * @param filename - файл, куда записываем
 * @param Ferz - массив координат всех ферзей
 * @param N - размер доски
 */
void Print_File(char const *filename, ferz_t *Ferz, int N) {
    FILE *ptr = fopen(filename, "w");
    Error(ptr);
    for (int i = 0; i < N; i++) {
        fprintf(ptr, "%d %d\n", Ferz[i].x, Ferz[i].y);
    }
    fclose(ptr);
}
/**
 * Дополнительная функция вывода шахмотной доски с расставленными ферзями в консоль
 * @param Ferz - массив координат всех ферзей
 * @param N - размер доски
 * 1 - стоит ферзь
 * 0 - ферзя нет
 */
void Print(ferz_t *Ferz, int N) {
    printf("Doska:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int flag = 0;
            for (int begun_Ferz = 0; begun_Ferz < N; begun_Ferz++) {
                if (j == Ferz[begun_Ferz].x && i == Ferz[begun_Ferz].y) {
                    printf("1 ");
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                printf("0 ");
            }
        }
        printf("\n");

    }
}
/**
 * Дополнительный вывод координат в консоль
 * @param Ferz - массив координат всех ферзей
 * @param N - размер доски
 */
void Print_coord_Ferz(ferz_t *Ferz, int N) {
    printf("Coordinaty Ferzey:\n");
    for (int i = 0; i < N; i++) {
        printf("%d %d\n", Ferz[i].x, Ferz[i].y);
    }
}
int main() {
    printf("\nDmitriev Mikhail, 5030102/10002, <4.13 laba> \n");
    char *cEname = "input.txt";
    int N = Read_size(cEname);  //Считали размер
    ferz_t *Ferz = calloc(N, sizeof(ferz_t));   //Создали пустой массив координат ферзей
    int fku = 0;    //флаг выхода рекурсии
    Ferz = Recurs(0, Ferz, N, &fku);    // Основная часть программы, расстановка ферзей
    char *cEname_2 = "output.txt"; //Файл, куда запишем координаты
    Print_File(cEname_2, Ferz, N); //Записываем координаты в файл

    // Дополнительный вывод в консоль
    Print_coord_Ferz(Ferz, N);
    printf("Size: %d * %d\n", N, N);
    Print(Ferz, N);
    printf("\nWork completed :)\n");
    return 0;
}
