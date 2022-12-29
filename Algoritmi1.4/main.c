#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 255 // размер строки

struct Person // Структура "Человек"
{
	char surname[MAX]; // Фамилия
	char name[MAX]; // Имя
	char patr[MAX]; // Отчество
};

// Сравнение двух людей
int personCmp(struct Person p1, struct Person p2)
{
	// Сравнение фамилий
	int surCmp = strcmp(p1.surname, p2.surname);
	// Если фамилии равны
	if (surCmp == 0)
	{
		// Сравнение имен
		int nameCmp = strcmp(p1.name, p2.name);
		// Если имена равны
		if (nameCmp == 0)
			// Позже в списке тот, чье отчество позже по алфавиту
			return strcmp(p1.patr, p2.patr);
		// Если имена не равны - то позже в списке тот, чье имя позже по алфавиту
		return nameCmp;
	}
	// Если фамилии не равны - то позже в списке тот, чья фамилия позже по алфавиту
	return surCmp;
}

struct Node // Структура "Узел списка"
{
	struct Person value; // Значение в узле
	struct Node* next; // Следующий узел
};

struct Node* head = NULL; // Первый элемент в списке

// Добавление человека в список
void add(struct Person p);
// Добавление человека в список, начиная с узла n
void _add(struct Node** n, struct Person p);
// Вывод всех фамилий
void print();
// Вывод всех фамилий, начиная с узла n
void _print(struct Node* n);
// Проверка того, что строка a начинается со строки b
int startsWith(const char* a, const char* b);
// Нахождение всех людей, чьи ФИО соответствуют маске
void checkStarts(char* mask);
// Нахождение всех людей, чьи ФИО соответствуют маске, начиная с узла n
void _checkStarts(struct Node* n, char* surname, char* name, char* patr);

// Добавление человека в список
void add(struct Person p)
{
	// Добавление человека в список, начиная с первого узла
	_add(&head, p);
}

// Добавление человека в список, начиная с узла n
void _add(struct Node** n, struct Person p)
{
	// Если текущий узел пуст
	if (!(*n))
	{
		// Создается узел
		*n = (struct Node*)malloc(sizeof(struct Node));
		(*n)->value = p;
		(*n)->next = NULL;
	}
	// Если человек в текущем узле идет раньше по алфавиту, чем новый
	else if (personCmp((*n)->value, p) < 0)
		// Переход к следующему узлу списка
		_add(&((*n)->next), p);
	// Иначе
	else
	{
		// Создается новый узел
		struct Node* n1 = (struct Node*)malloc(sizeof(struct Node));
		n1->value = p;
		// Текущий узел становится следующим для нового
		n1->next = *n;
		*n = n1;
	}
}

// Вывод всех фамилий
void print()
{
	printf("Список всех фамилий:\n");
	// Вывод всех фамилий, начиная с первого узла
	_print(head);
}

// Вывод всех фамилий, начиная с узла n
void _print(struct Node* n)
{
	// Если текущий узел пуст
	if (!n)
		// Завершение вывода
		return;
	// Вывод фамилии
	printf("%s\n", n->value.surname);
	// Переход к следующему узлу списка
	_print(n->next);
}

// Проверка того, что строка a начинается со строки b
int startsWith(const char* a, const char* b)
{
	return strncmp(a, b, strlen(b)) == 0;
}

// Нахождение всех людей, чьи ФИО соответствуют маске
void checkStarts(char* mask)
{
	// Расщепление маски по пробелу на начальные
	// буквы фамилии, имени и отчества
	char* surname = strtok(mask, " ");
	// Т.к. маска имеет "Ф" "И" "О",
	// требуется удалить кавычки слева и справа
	char* surname2 = malloc(strlen(surname) - 2);
	strncpy(surname2, surname + 1, strlen(surname) - 2);
	char* name = strtok(NULL, " ");
	char* name2 = malloc(strlen(name) - 2);
	strncpy(name2, name + 1, strlen(name) - 2);
	char* patr = strtok(NULL, " ");
	char* patr2 = malloc(strlen(patr) - 2);
	strncpy(patr2, patr + 1, strlen(patr) - 2);

	printf("Подходящие по маске:\n");
	// Поиск людей с подходящим ФИО
	_checkStarts(head, surname2, name2, patr2);
}

// Нахождение всех людей, чьи ФИО соответствуют маске, начиная с узла n
void _checkStarts(struct Node* n, char* surname, char* name, char* patr)
{
	// Если текущий узел пуст
	if (!n)
		// Завершение поиска
		return;
	// Если и фамилия, и имя, и отчество начинаются с требуемых букв 
	if (startsWith(n->value.surname, surname) && startsWith(n->value.name, name)
		&& startsWith(n->value.patr, patr))
		// Вывод фамилии
		printf("%s\n", n->value.surname);
	// Переход к следующему узлу списка
	_checkStarts(n->next, surname, name, patr);
}

int main()
{
	// Открытие файла names.txt на чтение
	FILE* fp = fopen("names.txt", "r");
	// Буфер
	char buf[MAX];
	// Пока в файле есть непрочитанные строки
	while (fgets(buf, MAX, fp))
	{
		// Выделение памяти для структуры
		struct Person* p = (struct Person*)malloc(sizeof(struct Person));
		// Расщепление прочитанной строки по пробелу
		// на фамилию, имя и отчество
		char* ptr = strtok(buf, " ");
		strcpy(p->surname, ptr);
		ptr = strtok(NULL, " ");
		strcpy(p->name, ptr);
		ptr = strtok(NULL, " ");
		strcpy(p->patr, ptr);
		// Добавление человека в список
		add(*p);
	}
	// Закрытие файла
	fclose(fp);

	// Вывод всех фамилий
	print();

	// Ввод маски
	char* mask = malloc(MAX);
	printf("\nВведите маску поиска в формате \"Ф\" \"И\" \"О\": ");
	scanf("%[^\n]", mask);
	// Вывод всех фамилий, соответствующих маске
	checkStarts(mask);

	return 0;
}