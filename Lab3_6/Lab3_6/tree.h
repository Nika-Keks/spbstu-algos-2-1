#pragma once

#define CHILDREN_COUNT 8

/**
* ����� � ������������
*/
typedef struct Point {
	double x; ///< ���������� x
	double y; ///< ���������� y
	double z; ///< ���������� z
} Point;

/**
* ���� ����-������
*/
typedef struct Node {
	Point* top; ///< ������� ������� �������
	Point* bottom; ///< ������ ������� �������
	Point* point; ///< �����, ��������������� �������
	struct Node** children; ///< ������ �������� ��������� � ������ �������
	int isLeaf; ///< �������� �� ���� ������: 1 - ��, 0 - ���
	int depth; ///< ������� ����
} Node;

/**
* ������� ����� � ������������
* 
* @param x ���������� x
* @param y ���������� y
* @param z ���������� z
* 
* @return ����� � ������������
*/
Point* pointCreate(double x, double y, double z);

/**
* ������� �����
* 
* @param point ����� ��� ��������
*/
void pointDestroy(Point* point);

/**
* ������� ���� ����-������
* 
* @param point ����� ������� ����
* @param bottom ������ �������(-x, -y, -z)
* @param top ������� �������(x, y, z)
* @param depth ������� ����
* 
* @return ���� ������
*/
Node* nodeCreate(Point* point, Point* bottom, Point* top, int depth);

/**
* ������� ���� ������
* 
* @param node ���� ��� ��������
*/
void nodeDestroy(Node* node);

/**
* �������� ���������� �� ���� � ��� �����
* 
* @parm node ���� ��� ������
* @param octant ������, � ������� ���� ���������
*/
void nodePrint(Node* node, int octant);

/**
* ���������� ����� �������(����������), � �������� ����������� �����
* 
* @param node ����, ���������� �������� ���������������
* @param point �����, ��� ������� ������������ ������
* 
* @return ����� �������
*/
int belongsToOctant(Node* node, Point* point);

/**
* ������� ����� ��� �������
* 
* �� ������ ������� � �������� ������������ ������� ������� ������, �� �������
* ���� �������� ������� ������� �������, ����� �������� ������� �������, �����
* �������� �������� � �������
* 
* @param bottom ������������ ������ �������
* @param top ������������ ������� �������
* @param octant ����� �������
* 
* @return ����� ��� ������ ����� �������
*/
Point* boundaryShift(Point* bottom, Point* top, int octant);

/**
* ���������� ������ � ������� ������� ����������� �������
* 
* @param node ���� ������
* @param octant ����� ����������
* 
* @return ������ � ������� ������� ����������
*/
Point** childBoundaries(Node* node, int octant);

/**
* ��������� ����� � ������
* 
* @param tree ������
* @param point ����� ��� ����������
*/
void nodeAdd(Node* tree, Point* point);

/**
* ������� ���� �� �����
* 
* @param tree ������ 
* @param point �����, ���� ������� ���� �����
* 
* @return ��������� ����
*/
Node* nodeFind(Node* tree, Point* point);

/**
* ������� ���� �� �����
* 
* @param tree ������
* @param point �����, ������� �������
*/
void nodeRemove(Node* tree, Point* point);