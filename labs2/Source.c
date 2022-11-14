#include<stdio.h>
#include<stdlib.h>
#define INF 1000000000
#pragma warning (disable:4996)


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


int main(void) {
	printf("Enter the number of data blocks: ");
	int n;
	//������������ ������ ����������  �������� ������������
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++) {
		//�������� �����
		Listptr tmp = (Listptr)malloc(sizeof(List));
		if (tmp != NULL) {
			tmp->size = 0;
			tmp->tail = NULL;
			tmp->head = NULL;
		}
		else { printf("No memory available\n"); }//������ �� ��������
		//������������ ������ �������� ������ ������ ���������� ��� ��������
		//��� ������� ����� ������ ������ � ������
		int m;
		printf("Enter the number of memory blocks: ");
		scanf_s("%d", &m);
		printf("Enter blocks of memory: ");
		for (int j = 0; j < m; j++) {
			int size;
			void* memory;
			scanf_s("%d", &size);
			memory = (void*)malloc(size);
			Insert(tmp, j-1, size, memory);
		}
		//������������ ������ �������� ���������
		printf("Enter the number of processes: ");
		scanf_s("%d", &m);
		printf("Enter processes: ");
		for (int j = 0; j < m; j++)
		{
			int value;//��������� ������� �������� ���������� � ������
			scanf_s("%d", &value);
			bestfit(tmp, value);
		}
		if (tmp != NULL) {
			PrintList(tmp->head);
		}
		DeleteList(&tmp);
	}
	return 0;
}


