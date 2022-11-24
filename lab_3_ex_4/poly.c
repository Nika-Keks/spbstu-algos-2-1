#include <stdio.h>
#include <stdlib.h>

//Создание полинома
typedef struct Polinom {
	int* numbers; //Коэффициенты полинома
  int length; //Степень полинома
} Polinom;

int Is_number(char ch) {
  return ch >= '0' && ch <= '9';
}

int Max_int(int a, int b) {
  return a > b ? a : b;
}

// Создание полинома из строки
Polinom* Polynom_parse(char* string) {
  //Создаем новый пустой полином, который получится в результате
  Polinom* polynom = malloc(sizeof(Polinom));
  polynom->numbers = malloc(sizeof(int));
  polynom->length = -1;
  while (*string) {
    if (Is_number(*string) || ((*string == '-' || *string == '+') && Is_number(*(string+1)))) {
      int power = strtol(string, &string, 10);
      polynom->length++;
      polynom->numbers = realloc(polynom->numbers, sizeof(int) * (polynom->length + 1));
      polynom->numbers[polynom->length] = power;
    } else {
      string++;
    }
  }
  return polynom;
}

//Чтение полинома из файла
Polinom* Polynom_read(char* File_name) {
  FILE *File_stream = fopen(File_name, "r");
  if (!File_stream) {
    printf("Невозможно открыть файл %s", File_name);
    exit(0);
  }
  //Чтение файла в строку
  int length;
  char* content;
  fseek(File_stream, 0, SEEK_END);
  length = ftell(File_stream);
  fseek(File_stream, 0, SEEK_SET);
  content = malloc(length*sizeof(char));
  if (!content) {
    printf("Невозможно выделить память");
    exit(0);
  }
  fread(content, 1, length, File_stream);
  //Чтение полинома из файла
  Polinom* polynom = Polynom_parse(content);
  fclose(File_stream);
  return polynom;
}

//Сохранение полинома в файл
void Polynom_write(char* File_name, Polinom* polynom) {
  FILE* File_stream = fopen(File_name, "w");
  for (int i = 0; i < polynom->length + 1; i++) {
    fprintf(File_stream, "%d ", polynom->numbers[i]);
  }
  fclose(File_stream);
}

//Сумма двух полиномов
Polinom* Polynom_sum(Polinom* p1, Polinom* p2) {
  //Создаем новый пустой полином, который получится в результате
  Polinom* polynom = malloc(sizeof(Polinom));
  polynom->length = Max_int(p1->length, p2->length);
  polynom->numbers = malloc(sizeof(int) * (polynom->length + 1));
  //Создание первого полинома
  for (int i = 0; i < p1->length + 1; i++) {
    polynom->numbers[polynom->length - i] = p1->numbers[p1->length - i];
  }
  //Создание второго полинома
  for (int i = 0; i < p2->length + 1; i++) {
    polynom->numbers[polynom->length - i] += p2->numbers[p2->length - i];
  }
  return polynom;
}

//Вычитание полиномов
Polinom* Polynom_sub(Polinom* p1, Polinom* p2) {
  //Создаем новый пустой полином, который получится в результате
  Polinom* polynom = malloc(sizeof(Polinom));
  polynom->length = Max_int(p1->length, p2->length);
  polynom->numbers = malloc(sizeof(int) * (polynom->length + 1));
  //Аналогично создаем два полинома
  for (int i = 0; i < p1->length + 1; i++) {
    polynom->numbers[polynom->length - i] = p1->numbers[p1->length - i];
  }
  for (int i = 0; i < p2->length + 1; i++) {
    polynom->numbers[polynom->length - i] -= p2->numbers[p2->length - i];
  }
  return polynom;
}

//Умножение полиномов
Polinom* Polynom_mul(Polinom* p1, Polinom* p2) {
  //Создаем новый пустой полином, который получится в результате
  Polinom* p3 = malloc(sizeof(Polinom));
  p3->length = p1->length + p2->length;
  p3->numbers = malloc(sizeof(int) * p3->length);
  //Обнуляем все коэффициенты
  for (int i = 0; i < p3->length + 1; i++) {
    p3->numbers[i] = 0;
  }
  //Перемножаем полиномы
  for (int i = 0; i < p1->length + 1; i++) {
    for (int j = 0; j < p2->length + 1; j++) {
      p3->numbers[p3->length - i - j] += p1->numbers[p1->length - i] * p2->numbers[p2->length - j];
    }
  }
  return p3;
}

//Очистка памяти
void Polynom_destroy(Polinom* polynom) {
  free(polynom->numbers);
  free(polynom);
}