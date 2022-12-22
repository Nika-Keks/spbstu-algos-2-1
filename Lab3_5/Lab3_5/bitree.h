#pragma once

/**
* —труктура дл€ элемента дерева
*/
typedef struct Node {
	int data; ///< число, €вл€ющеес€ ключом
	struct Node* parent; ///< родительский узел
	struct Node* left; ///< левый ребенок(ключ меньше текущего)
	struct Node* right; ///< правый ребенок(ключ больше текущего)
} Node;

/**
* —оздает новый узел
* 
* @param data ключ узла
* 
* @return созданный узел
*/
Node* nodeCreate(int data);

/**
* ”дал€ет узел из пам€ти
* 
* @param node узел дл€ удалени€
*/
void nodeDestroy(Node* node);

/**
* ƒобавл€ет узел в дерево
* 
* @param tree дерево
* @param node узел дл€ добавлени€
* 
* @return обновленное дерево
*/
Node* nodeAdd(Node* tree, Node* node);

/**
* ѕечатает узел и его родственников: родител€ и детей
* 
* @param node узел дл€ печати
*/
void printNodeAndItsRelatives(Node* node);

/**
* ¬озвращает левого ребенка узла или сам узел, если левый ребенок NULL
* 
* @param node узел
* 
* @return левый ребенок или переданный узел
*/
Node* leftChild(Node* node);

/**
* ¬озвращает правого ребенка узла или сам узел, если правый ребенок NULL
*
* @param node узел
*
* @return правый ребенок или переданный узел
*/
Node* rightChild(Node* node);

/**
* ¬озвращает родител€ узла или сам узел, если родитель NULL
* 
* @param node узел
* 
* @return родитель или переданный узел
*/
Node* parent(Node* node);

/**
* ”дал€ет переданный узел из дерева
* 
* @param node узел дл€ удалени€
*/
void nodeRemove(Node* node);