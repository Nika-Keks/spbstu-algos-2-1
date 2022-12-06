#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include "Laba2.h"
#pragma warning(disable:4996)


int main() {
    setlocale(LC_ALL, "Rus");
    List Mylist = Create_List();
    int n;
    printf("¬ведите кол-во блоков: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int bytes;
        printf("%d) блок = ", i + 1);
        scanf("%d", &bytes);
        void* memory = (void*)malloc(bytes);
        Insert(Mylist, Mylist->size, memory, bytes);
    }
    printf("¬ведите кол-во процессов: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int bytes;
        printf("%d) процесс = ", i + 1);
        scanf("%d", &bytes);
        BestFit(Mylist, bytes);
    }
    Print_List(Mylist);
    Delete_List(&Mylist);
    return 0;
}