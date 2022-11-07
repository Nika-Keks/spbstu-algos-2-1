//#pragma once
///*Данная команда переименовывает тип нашей структуры struct listNode в просто listNode */
//typedef struct listNode listNode;
//
///*Данная команда переименовывает тип указателя на структуру listNode* в  просто ListNodePtr*/
//typedef listNode* ListNodePtr;
//
///*Структура предназначенная для того что чтобы хранить данные в узле списка и указатель на следующий узел*/
//struct listNode {
//	listNode* nextptr;
//	char* string;
//	int n;
//};
//
///*Функция вставки нового узла в список*/
//void insert(ListNodePtr* sPtr, char* a, int lenght);
//
///*Функция проверяет является ли список пустым*/
//int isEmpty(ListNodePtr sPtr);
//
///*печатает одно слово которое находится в узле*/
//void Print(char* a, int n);
//
///*Функция печатает связанный список, то есть все слова в списке */
//void printList(ListNodePtr currentPtr);
//
///*Проверяет является символ буквой или разделяющим символом*/
//int IsAlNum(char c);
//
///*сравнивает слова в лексикографическом порядке(используя таблицу ASKII)*/
//int Compare(char* a, char* b, int c);
//
///*вы вводите число и функция выводит все слова имеющие длину большую этого числа*/
//void first(ListNodePtr currentPtr, int N);
//
///*вы вводите число и функция выводит все слова имеющие длину вавную этому числу*/
//void second(ListNodePtr currentPtr, int N);
//
///*осуществлет посимвольное чтение из файла*/
//ListNodePtr ReadText(char const* filename);
//
