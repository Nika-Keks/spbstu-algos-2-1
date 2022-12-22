#pragma once

/**
* ��������� ��� �������� ����� ��� �����������
*/
typedef struct Node {
	char name; ///< �������� ����
	struct Order* order; ///< ������ � ����������� �� ����, ������� ������������ ������
	int refs; ////< ���������� �������������� ���������
	struct Node* next; ///< ��������� ����
} Node;

/**
* ��������� ��� �������� ������� ���������� �����(�������)
*/
typedef struct Order {
	struct Node* front; ///< ����, ������� ������� �� ���, ������� ��������� �� ��� �������
	struct Order* next; ///< ��������� �������
} Order;

/**
* ������� ����� �������
* 
* @param front ����, ������� ���� ����� ����, � �������� ��������� ������ �������
* 
* @return ����� �������
*/
Order* orderCreate(Node* front);

/**
* ������� ���� ������� � ��������� ���������� ������ � ����, �� ������� ��������� ������ �������.
* 
* @param order ������� ��� ��������
*/
void orderDestroy(Order* order);

/**
* ������� ������ �������
* 
* @param head ������(������ ������)
*/
void orderDestroyList(Order* head);

/**
* ������� ����� ����
* 
* @param name �������� ����
*/
Node* nodeCreate(char name);

/**
* ������� ���� � ��������������� ��� �������
* 
* @param node ���� ��� ��������
*/
void nodeDestroy(Node* node);

/**
* ��������� ���� � ������ �����
* 
* @param head ������ �����
* @param node ���� ��� �������
*/
Node* insertNode(Node* head, Node* node);

/**
* ������� ���� �� ����� ����
* 
* @param head ������ �����
* @param name �������� ����, ������� ���� �����
* 
* @return ��������� ����
*/
Node* findNode(Node* head, char name);

/**
* ��������� ������� ��� ��������������� � ���������� ����
* 
* @param behind �������������� ����
* @param front ��������� ����
*/
void addCondition(Node* behind, Node* front);

/**
* ���������� ���� � ��������� �� ����� � ��������� ���������.
* 
* @param name �������� �����
*/
Node* conditionsFromFileByName(char* name);

/**
* �������� ������ ���� � 0 ������, ������� ��� � ���������� ����� ������ �����
* 
* @param head ������ �����
*/
Node* printTopological(Node* head);

/**
* �������� ���� � ������ �������.
* 
* @param head ������ � ������
*/
void printTopologicalList(Node* head);