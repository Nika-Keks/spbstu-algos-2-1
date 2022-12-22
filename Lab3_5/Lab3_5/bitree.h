#pragma once

/**
* ��������� ��� �������� ������
*/
typedef struct Node {
	int data; ///< �����, ���������� ������
	struct Node* parent; ///< ������������ ����
	struct Node* left; ///< ����� �������(���� ������ ��������)
	struct Node* right; ///< ������ �������(���� ������ ��������)
} Node;

/**
* ������� ����� ����
* 
* @param data ���� ����
* 
* @return ��������� ����
*/
Node* nodeCreate(int data);

/**
* ������� ���� �� ������
* 
* @param node ���� ��� ��������
*/
void nodeDestroy(Node* node);

/**
* ��������� ���� � ������
* 
* @param tree ������
* @param node ���� ��� ����������
* 
* @return ����������� ������
*/
Node* nodeAdd(Node* tree, Node* node);

/**
* �������� ���� � ��� �������������: �������� � �����
* 
* @param node ���� ��� ������
*/
void printNodeAndItsRelatives(Node* node);

/**
* ���������� ������ ������� ���� ��� ��� ����, ���� ����� ������� NULL
* 
* @param node ����
* 
* @return ����� ������� ��� ���������� ����
*/
Node* leftChild(Node* node);

/**
* ���������� ������� ������� ���� ��� ��� ����, ���� ������ ������� NULL
*
* @param node ����
*
* @return ������ ������� ��� ���������� ����
*/
Node* rightChild(Node* node);

/**
* ���������� �������� ���� ��� ��� ����, ���� �������� NULL
* 
* @param node ����
* 
* @return �������� ��� ���������� ����
*/
Node* parent(Node* node);

/**
* ������� ���������� ���� �� ������
* 
* @param node ���� ��� ��������
*/
void nodeRemove(Node* node);