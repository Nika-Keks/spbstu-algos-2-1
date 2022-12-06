#pragma once

#define CHILDREN_COUNT 8

/**
* Точка в пространстве
*/
typedef struct Point {
	double x; ///< координата x
	double y; ///< координата y
	double z; ///< координата z
} Point;

/**
* Узел окто-дерева
*/
typedef struct Node {
	Point* top; ///< верхняя граница области
	Point* bottom; ///< нижняя граница области
	Point* point; ///< точка, соответствующая области
	struct Node** children; ///< массив дочерних элементов в данной области
	int isLeaf; ///< является ли узел листом: 1 - да, 0 - нет
	int depth; ///< глубина узла
} Node;

/**
* Создает точку в пространстве
* 
* @param x координата x
* @param y координата y
* @param z координата z
* 
* @return точка в пространстве
*/
Point* pointCreate(double x, double y, double z);

/**
* Удаляет точку
* 
* @param point точка для удаления
*/
void pointDestroy(Point* point);

/**
* Создает узел окто-дерева
* 
* @param point точка данного узла
* @param bottom нижняя граница(-x, -y, -z)
* @param top верхняя граница(x, y, z)
* @param depth глубина узла
* 
* @return узел дерева
*/
Node* nodeCreate(Point* point, Point* bottom, Point* top, int depth);

/**
* Удаляет узел дерева
* 
* @param node узел для удаления
*/
void nodeDestroy(Node* node);

/**
* Печатает информацию об узле и его детях
* 
* @parm node узел для печати
* @param octant октант, в котором узел находится
*/
void nodePrint(Node* node, int octant);

/**
* Возвращает номер октанта(подоктанта), к которому принадлежит точка
* 
* @param node узел, подоктанты которого рассматриваются
* @param point точка, для которой определяется октант
* 
* @return номер октанта
*/
int belongsToOctant(Node* node, Point* point);

/**
* Находит сдвиг для октанта
* 
* По номеру октанта и границам родительской области находит вектор, на который
* надо сдвинуть границы первого октанта, чтобы получить границы октанта, номер
* которого передали в функцию
* 
* @param bottom родительская нижняя граница
* @param top родительская верхняя граница
* @param octant номер октанта
* 
* @return сдвиг для границ этого октанта
*/
Point* boundaryShift(Point* bottom, Point* top, int octant);

/**
* Возвращает нижнюю и верхнюю границу переданного октанта
* 
* @param node узел дерева
* @param octant номер подоктанта
* 
* @return нижняя и верхняя граница подоктанта
*/
Point** childBoundaries(Node* node, int octant);

/**
* Добавляет точку в дерево
* 
* @param tree дерево
* @param point точка для добавления
*/
void nodeAdd(Node* tree, Point* point);

/**
* Находит узел по точке
* 
* @param tree дерево 
* @param point точка, узел которой надо найти
* 
* @return найденный узел
*/
Node* nodeFind(Node* tree, Point* point);

/**
* Удаляет узел по точке
* 
* @param tree дерево
* @param point точка, которую удаляют
*/
void nodeRemove(Node* tree, Point* point);