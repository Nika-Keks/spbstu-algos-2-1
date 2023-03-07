#pragma once

#define CHILDREN_COUNT 8

/**
* ��������� ��� ������������� �����
*/
typedef struct Point {
	double x; 
	double y; 
	double z; 
} Point;

/**
* ���� ����-������
*/
typedef struct Node {
	Point* top; 
	Point* bottom; 
	Point* point; 
	struct Node** children; 
	int isLeaf; // �������� �� ���� ������
	int depth; 
} Node;

/**
* ������� ����� � ������������
*/
Point* pointCreate(double x, double y, double z);

/**
* ������� �����
*
*/
void pointDestroy(Point* point);

/**
* ������� ���� ����-������
*
* point - ����� ������� ����
* bottom - ������ �������(-x, -y, -z)
* top - ������� �������(x, y, z)
* depth - ������� ����
*/
Node* nodeCreate(Point* point, Point* bottom, Point* top, int depth);

/**
* ������� ���� ������
*/
void nodeDestroy(Node* node);

/**
* ������� ���������� �� ���� � ��� �����
*/
void nodePrint(Node* node, int octant);

/**
* ���������� ����� �������(����������), � �������� ����������� �����
*
* node - ����, ���������� �������� ���������������
*/
int belongsToOctant(Node* node, Point* point);

/**
* ������� ����� ��� �������
*
* �� ������ ������� � �������� ������������ ������� ������� ������, �� �������
* ���� �������� ������� ������� �������, ����� �������� ������� �������, �����
* �������� �������� � �������
*
* bottom - ������������ ������ �������
* top - ������������ ������� �������
*
*/
Point* boundaryShift(Point* bottom, Point* top, int octant);

/**
* ���������� ������ � ������� ������� ����������� �������
*/
Point** childBoundaries(Node* node, int octant);

/**
* ��������� ����� � ������
*/
void nodeAdd(Node* tree, Point* point);

/**
* ������� ���� �� �����
*/
Node* nodeFind(Node* tree, Point* point);

/**
* ������� ���� �� �����
*/
void nodeRemove(Node* tree, Point* point);