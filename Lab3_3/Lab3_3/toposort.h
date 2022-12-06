#pragma once

/**
* Структура для описания узлов для отображения
*/
typedef struct Node {
	char name; ///< название узла
	struct Order* order; ///< список с указателями на узлы, которым предшествует данный
	int refs; ////< количество предшествующих элементов
	struct Node* next; ///< следующий узел
} Node;

/**
* Структура для описания порядка следования узлов(условия)
*/
typedef struct Order {
	struct Node* front; ///< узел, который следует за тем, который ссылается на это условие
	struct Order* next; ///< следующее условие
} Order;

/**
* Создает новое условие
* 
* @param front узел, который идет после узла, к которому относится данное условие
* 
* @return новое условие
*/
Order* orderCreate(Node* front);

/**
* Удаляет одно условие и уменьшает количество ссылок в узле, на который указывает данное условие.
* 
* @param order условие для удаления
*/
void orderDestroy(Order* order);

/**
* Удаляет список условий
* 
* @param head список(голова списка)
*/
void orderDestroyList(Order* head);

/**
* Создает новый узел
* 
* @param name название узла
*/
Node* nodeCreate(char name);

/**
* Удаляет узел и соответствующие ему условия
* 
* @param node узел для удаления
*/
void nodeDestroy(Node* node);

/**
* Вставляет узел в список узлов
* 
* @param head список узлов
* @param node узел для вставки
*/
Node* insertNode(Node* head, Node* node);

/**
* Находит узел по имени узла
* 
* @param head список узлов
* @param name название узла, который надо найти
* 
* @return найденный узел
*/
Node* findNode(Node* head, char name);

/**
* Добавляет условие для предшествующего и следующего узла
* 
* @param behind предшествующий узел
* @param front следующий узел
*/
void addCondition(Node* behind, Node* front);

/**
* Возвращает узлы с условиями из файла с указанным названием.
* 
* @param name название файла
*/
Node* conditionsFromFileByName(char* name);

/**
* Печатает первый узел с 0 ссылок, удаляет его и возвращает новый список узлов
* 
* @param head список узлов
*/
Node* printTopological(Node* head);

/**
* Печатает узлы с учетом условий.
* 
* @param head список с узлами
*/
void printTopologicalList(Node* head);