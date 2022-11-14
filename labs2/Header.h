#pragma once


//���� ������ ������� ������ ������,
//������� � ��� ������� ����� ��������� �����-���� �������
//� ������ � ������ ����� ���������� ������
//��������� �� ���� � ���������� ���� ������
typedef struct Node {
	void* memory;
	int size;
	struct Node* next;
	struct Node* prev;
}Node;
typedef Node* Nodeptr;


//��������� "���������� ������" ����� ������� ���� ������ (����� �� ������������� ���������� ��������� ������ ���),
//� ����� ��������� head, ����������� �� ������ �������, � ��������� tail, ����������� �� ��������� �������
typedef struct List {
	size_t size;
	Nodeptr tail;
	Nodeptr head;
}List;
typedef struct List* Listptr;


Listptr CreateList();
void DeleteList(Listptr* list);
void pushFront(Listptr list, void* data, int size);
void pushBack(Listptr list, void* value, int size);
Nodeptr GetNth(Listptr list, int index);
void Insert(Listptr list, int index, int size, void* value);
void PrintList(Nodeptr current);
int IsEmpty(Nodeptr Sptr);
void bestfit(Listptr list, int value);






