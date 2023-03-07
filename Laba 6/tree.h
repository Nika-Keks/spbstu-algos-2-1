#pragma once

#define CHILDREN_COUNT 8

/**
* —труктура дл€ представлени€ точки
*/
typedef struct Point {
	double x; 
	double y; 
	double z; 
} Point;

/**
* ”зел окто-дерева
*/
typedef struct Node {
	Point* top; 
	Point* bottom; 
	Point* point; 
	struct Node** children; 
	int isLeaf; // €вл€етс€ ли узел листом
	int depth; 
} Node;

/**
* —оздает точку в пространстве
*/
Point* pointCreate(double x, double y, double z);

/**
* ”дал€ет точку
*
*/
void pointDestroy(Point* point);

/**
* —оздает узел окто-дерева
*
* point - точка данного узла
* bottom - нижн€€ граница(-x, -y, -z)
* top - верхн€€ граница(x, y, z)
* depth - глубина узла
*/
Node* nodeCreate(Point* point, Point* bottom, Point* top, int depth);

/**
* ”дал€ет узел дерева
*/
void nodeDestroy(Node* node);

/**
* ¬ыводит информацию об узле и его дет€х
*/
void nodePrint(Node* node, int octant);

/**
* ¬озвращает номер октанта(подоктанта), к которому принадлежит точка
*
* node - узел, подоктанты которого рассматриваютс€
*/
int belongsToOctant(Node* node, Point* point);

/**
* Ќаходит сдвиг дл€ октанта
*
* ѕо номеру октанта и границам родительской области находит вектор, на который
* надо сдвинуть границы первого октанта, чтобы получить границы октанта, номер
* которого передали в функцию
*
* bottom - родительска€ нижн€€ граница
* top - родительска€ верхн€€ граница
*
*/
Point* boundaryShift(Point* bottom, Point* top, int octant);

/**
* ¬озвращает нижнюю и верхнюю границу переданного октанта
*/
Point** childBoundaries(Node* node, int octant);

/**
* ƒобавл€ет точку в дерево
*/
void nodeAdd(Node* tree, Point* point);

/**
* Ќаходит узел по точке
*/
Node* nodeFind(Node* tree, Point* point);

/**
* ”дал€ет узел по точке
*/
void nodeRemove(Node* tree, Point* point);