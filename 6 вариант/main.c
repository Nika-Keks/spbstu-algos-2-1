#include <stdio.h>
#include <stdlib.h>

typedef struct line_t {
    struct {
        int day;
        int month;
        int year;
    }data;
    double temperatur;
    struct line_t *next;
}line_t;
/**
 * Создание списка
 * @param line - первый элемент для создания
 * @return указатель на голову списка
 */
line_t *create(line_t line)
{
    line_t *tmp = (line_t*)malloc(sizeof(line_t));
    tmp->data = line.data;
    tmp->temperatur = line.temperatur;
    tmp -> next = NULL;
    return(tmp);
}
/**
 * Дописывает узел в начало списка
 * @param line - новый узел
 * @param head - голова
 * @return - голова
 */
line_t *add_element_start(line_t line, line_t *head)
{
    line_t *tmp = (line_t*)malloc(sizeof(line_t));
    tmp->data = line.data;
    tmp->temperatur = line.temperatur;
    tmp -> next = head;
    return(tmp);
}
/**
 * Сравнение по дате
 * @param First
 * @param Second
 * @return 1||0 Если 1 раньше 2
 */
int Comparison(struct line_t* First, struct line_t Second){
    if (First->data.year > Second.data.year) {
        return 1;
    }
    if (First->data.year == Second.data.year && First->data.month > Second.data.month) {
        return 1;
    }
    if (First->data.year == Second.data.year && First->data.month == Second.data.month && First->data.day >= Second.data.day){
        return 1;
    }
    else{
        return 0;
    }
}
/**
 * Добавление узла в список
 * @param line новый узел
 * @param begunok будет перед новым узлом
 */
void add_element_vstavka(line_t line, line_t* begunok){
    line_t *tmp = (line_t*)malloc(sizeof(line_t));
    tmp->data = line.data;
    tmp->temperatur = line.temperatur;
    tmp->next = begunok->next;
    begunok->next = tmp;
}
/**
 * Определение нужной позиции и вставка элемента в список
 * @param line
 * @param head
 * @return
 */
line_t *add_element_position(line_t line, line_t *head)
{
    line_t *begunok = head;
    line_t *begunok_2 = begunok;
    while (begunok->next != NULL && begunok->temperatur < line.temperatur){
        begunok_2 = begunok;
        begunok = begunok -> next;
    }
    while (begunok->next != NULL && (begunok->temperatur == line.temperatur && Comparison(begunok, line))){
        begunok_2 = begunok;
        begunok = begunok -> next;
    }
    if (begunok->next == NULL){
        if (begunok->temperatur < line.temperatur){
            add_element_vstavka(line, begunok);
            return head;
        }
        if (begunok->temperatur == line.temperatur && Comparison(begunok, line)){
            add_element_vstavka(line, begunok);
            return head;
        }
        else{
            add_element_vstavka(line, begunok_2);
            return head;
        }
    }
    else{
        add_element_vstavka(line, begunok_2);
        return head;
    }
}
/**
 * Проверка отсутсвия файла
 * @param ptr -
 */
void Error(FILE* ptr){
    if (ptr == EOF){
        printf("\nYps\n");
        exit(1);
    }
}
/**
 * Считывание данных с файла и запись в список
 * @param filename
 * @return
 */
line_t* Processing(char const *filename){
    line_t* Start = NULL;
    FILE* ptr = fopen(filename, "r");
    Error(ptr);
    line_t New;
    fscanf(ptr, "%d-%d-%d %lf", &New.data.year, &New.data.month, &New.data.day, &New.temperatur);
    Error(ptr);
    Start = create(New);
    while ( fscanf(ptr, "%d-%d-%d %lf", &New.data.year, &New.data.month, &New.data.day, &New.temperatur)!=EOF){
        if (New.temperatur < Start->temperatur || (New.temperatur == Start->temperatur && Comparison(Start, New)==0)){
            Start = add_element_start(New, Start);
        }
        else{
            Start = add_element_position(New, Start);
        }
    }
    fclose(ptr);
    return Start;
}
/**
 * Вывод всего списка
 * @param head
 */
void Print_all(line_t *head){
    line_t *begunok = head;
    printf("All spisok:\n");
    while (begunok->next != NULL){
        printf("%.2d %.2d %.4d  -  %lf\n", begunok->data.day, begunok->data.month, begunok->data.year, begunok->temperatur);
        begunok = begunok->next;
    }
    printf("%.2d %.2d %.4d  -  %lf\n", begunok->data.day, begunok->data.month, begunok->data.year, begunok->temperatur);
}
/**
 * Вывод дат отрицательных температур
 * @param head
 */
void Print_Negative(line_t *head){
    line_t *begunok = head;
    int N = 0;
    printf("\nNegative temperatur:\n");
    while (begunok->next != NULL){
        if (begunok->temperatur < 0){
            printf("%.2d %.2d %.4d  -  %lf\n", begunok->data.day, begunok->data.month, begunok->data.year, begunok->temperatur);
            N++;
        }
        begunok = begunok->next;
    }
    if (begunok->temperatur < 0){
        printf("%.2d %.2d %.4d  -  %lf\n", begunok->data.day, begunok->data.month, begunok->data.year, begunok->temperatur);
        N++;
    }
    if (N == 0){
        printf("Not found :(\n");
    }
}
/**
 * Проверка наличия даты с заданной температурой
 * @param head
 */
void Proverka_Temperatur(line_t *head){
    line_t *begunok = head;
    int n = 0;
    double T;
    printf("\nEnter temperatur :");
    scanf("%lf", &T);
    while (begunok->next != NULL){
        if (begunok->temperatur == T){
            if (n == 0){
                printf("Yes!:\n");
            }
            n++;
            printf("%d %d %d  -  %lf\n", begunok->data.day, begunok->data.month, begunok->data.year, begunok->temperatur);
        }
        begunok = begunok->next;
    }
    if (n == 0){
        printf("Oh, no...\n");
    }
    printf("Found %d days!\n", n);
}

int main() {
    printf("\nDmitriev Mikhail, 5030102/10002, <1 laba> \n");
    char* cEname="Test.txt";
    line_t* Spisok = Processing(cEname);
    //Print_all(Spisok);
    Print_Negative(Spisok);
    Proverka_Temperatur(Spisok);
    printf("\nWork completed :)\n");
    return 0;
}
