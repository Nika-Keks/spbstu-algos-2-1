//#include<stdlib.h>
//#include<stdio.h>
//#include<locale.h>
//#pragma warning(disable:4996)
//
//typedef struct listNode listNode;
//typedef listNode* ListNodePtr;
//struct listNode {
//	listNode* nextptr;
//	char* string;
//	int n;
//};
//
///*функция вставляет новый узел в наш список
//вставка происходит сразу с учетом длины слова
//если слова одинаковой длины то вставка просиходит в лексикографической порядке
//*/
//
//void insert(ListNodePtr* sPtr, char* a, int lenght) {
//	ListNodePtr newPtr;
//	ListNodePtr previousPtr;
//	ListNodePtr currentPtr;
//
//	newPtr = (ListNodePtr)malloc(sizeof(listNode));
//
//	if (newPtr != NULL)//если удалось выделить память записываем в структуру строку и длину строки
//	{
//		newPtr->string = a;
//		newPtr->n = lenght;
//		newPtr->nextptr = NULL;
//
//		previousPtr = NULL;
//		currentPtr = *sPtr;
//		while (currentPtr != NULL && lenght > currentPtr->n)// пробегаемся по списку пока длина нашего слова больше длины в узле
//
//		{
//			previousPtr = currentPtr;
//			currentPtr = currentPtr->nextptr;
//		}
//		while (currentPtr != NULL && !Compare(a, currentPtr->string, lenght) && lenght == currentPtr->n)
//		{
//			previousPtr = currentPtr;
//			currentPtr = currentPtr->nextptr;
//		}
//		if (previousPtr == NULL) {
//			newPtr->nextptr = *sPtr;
//			*sPtr = newPtr;
//		}
//		else {
//			previousPtr->nextptr = newPtr;
//			newPtr->nextptr = currentPtr;
//		}
//	}
//	else {
//		printf("No memory available.\n");
//	}
//}
//
///*Функция проверяет является ли список пустым*/
//int isEmpty(ListNodePtr sPtr) {
//	return sPtr == NULL;
//}
//
///*Функция печатает связанный список, то есть все слова в списке */
//void printList(ListNodePtr currentPtr) {
//	if (isEmpty(currentPtr)) {
//		puts("List is empty.\n");
//	}
//	else {
//		puts("The list is:");
//		while (currentPtr != NULL) {
//			Print(currentPtr->string, currentPtr->n);
//			currentPtr = currentPtr->nextptr;
//		}
//	}
//}
//
///*сравнивает слова в лексикографическом порядке(используя таблицу ASKII)*/
//int Compare(char* a, char* b, int c) {
//	for (int i = 0; i < c; i++) {
//		if (a[i] < b[i]) {
//			return 1;
//		}
//		if (a[i] > b[i]) {
//			return 0;
//		}
//	}
//	return 0;
//}
//
///*печатает одно слово которое находится в узле*/
//void Print(char* a, int n) {
//	for (int i = 0; i < n; i++) {
//		printf("%c", a[i]);
//	}
//	puts("");
//}
//
///*осуществлет посимвольное чтение из файла*/
//ListNodePtr ReadText(char const* filename) {
//	ListNodePtr StartPtr = NULL;
//	FILE* f;
//	int length = 0;
//	char* a = NULL;
//	char t;
//	f = fopen(filename, "r+");
//	if (f != NULL) {//если удалось открыть файл
//		a = (char*)malloc(sizeof(char));
//		if (a != NULL) {//если выделилась память 
//			while (fscanf(f, "%c", &t) == 1) {
//				if (IsAlNum(t)) {//если символ является буквой
//					length++;
//					char* p = (char*)realloc(a, length * sizeof(char));
//					if (p == NULL) {
//						return NULL;
//					}
//					a = p;
//					a[length - 1] = t;
//				}
//				else {
//					if (IsAlNum(a[0])) {//вслучае если символ является разделителем проверяет можно ли нам вставить слово в узел
//						insert(&StartPtr, a, length);
//						length = 0;
//						a = (char*)malloc(sizeof(char));
//
//						if (a == NULL) {
//							return NULL;
//						}
//					}
//				}
//			}
//			if (IsAlNum(a[0])) {//если нет разделителей то нужно прописать отдельно проверку
//				insert(&StartPtr, a, length);
//				length = 0;
//				a = (char*)malloc(sizeof(char));
//
//				if (a == NULL) {
//					return NULL;
//				}
//			}
//		}
//		fclose(f);
//	}
//	else {
//		printf("Error.");//если файл не удалось открыть
//	}
//	return StartPtr;
//}
//
///*Проверяет является символ буквой или разделяющим символом
//если да то возвращаем ноль если нет то 1*/
//int IsAlNum(char c) {
//	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))return 1;
//	return 0;
//}
//
///*вы вводите число и функция выводит все слова имеющие длину большую этого числа*/
//void first(ListNodePtr currentPtr, int N)
//{
//	if (isEmpty(currentPtr)) {
//		puts("List is empty.\n");
//	}
//	else {
//		puts("The list is:");
//		while (currentPtr != NULL) {
//			if (currentPtr->n > N)
//				Print(currentPtr->string, currentPtr->n);
//			currentPtr = currentPtr->nextptr;
//		}
//	}
//}
//
///*вы вводите число и функция выводит все слова имеющие длину вавную этому числу*/
//void second(ListNodePtr currentPtr, int N)
//{
//	if (isEmpty(currentPtr)) {//проверка на то является ли список пустым
//		puts("List is empty.\n");
//	}
//	else {
//		puts("The list is:");
//		while (currentPtr != NULL) {
//			if (currentPtr->n == N)
//				Print(currentPtr->string, currentPtr->n);
//			currentPtr = currentPtr->nextptr;
//		}
//	}
//}