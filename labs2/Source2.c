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

//������� ������� ��� ����
Listptr CreateList() {
	Listptr tmp = (Listptr)malloc(sizeof(List));
	if (tmp != NULL) {
		tmp->size = 0;
		tmp->tail = tmp->head = NULL;
	}
	return tmp;
}

// ������ ������ �������, ������� ������� ������
void DeleteList(Listptr* list) {
	Nodeptr tmp = (*list)->head;
	Nodeptr next = NULL;
	while (tmp != NULL) {
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(*list);
	(*list) = NULL;
}


//������� ����� ��� ���� ��� �� �������� ������� � ������ ������
void pushFront(Listptr list, void* data, int size) {
	Nodeptr tmp = (Nodeptr)malloc(sizeof(Node));
	if (tmp == NULL) {
		printf("no memory available.\n");
	}
	else {
		tmp->memory = data;
		tmp->size = size;
		tmp->prev = NULL;
		tmp->next = list->head;

		if (list->head) {
			list->head->prev = tmp;
		}
		list->head = tmp;
		if (list->tail == NULL) {
			list->tail = tmp;
		}
		list->size++;
	}
}


//������� ����� ��� ���� ��� �� �������� ������� � ����� ������

void pushBack(Listptr list, void* value, int size) {
	Nodeptr tmp = (Nodeptr)malloc(sizeof(Node));
	if (tmp == NULL) {
		printf("No memory available.");
	}
	else {
		tmp->memory = value;
		tmp->size = size;
		tmp->next = NULL;
		tmp->prev = list->tail;
		if (list->tail) {
			list->tail->next = tmp;
		}
		list->tail = tmp;

		if (list->head == NULL) {
			list->head = tmp;
		}
		list->size++;
	}
}

//��������� n-�� �������� � ������
Nodeptr GetNth(Listptr list, int index) {
	Nodeptr tmp = list->head;
	int i = 0;
	while (tmp != NULL && i < index) {
		tmp = tmp->next;
		i++;
	}
	return tmp;
}


//������������� ������� ������� ���� � ������ ������� ��������� �� ���� 
//��������� �� ����, ������� ���� ���� �������� ���� � ������ ���������� ��� ������� � �� ��������
void Insert(Listptr list, int index, int size, void* value) {
	Nodeptr elm = NULL;//��������� �� ������� ����� ������� �� ����� ��������� ����� ����
	Nodeptr ins = NULL;//��������� �� ����� ����
	if (list->size == 0) {//���� ������ ������ 0 �� �������� ������� 
						  //pushfront ������� ��������� ���� � ������ ������
		pushFront(list, value, size);
	}
	else {

		elm = GetNth(list, index);
		if (elm == NULL) {//���� ������� ���������� ��������� �� NULL �� ��������� ���� � ����� ������
			pushBack(list, value, size);
		}
		else {
			ins = (Nodeptr)malloc(sizeof(Node));
			if (ins != NULL) {
				ins->memory = value;
				ins->size = size;
				ins->prev = elm;
				ins->next = elm->next;
				if (elm->next) {
					elm->next->prev = ins;
				}
				elm->next = ins;

				if (!elm->prev) {
					list->head = elm;
				}
				if (!elm->next) {
					list->tail = elm;
				}
			}
			else {
				printf("No memory available.");
			}
		}
	}
	list->size++;
}

//������� �������� ��� ������
void PrintList(Nodeptr current) {
	if (IsEmpty(current)) {
		printf("The list is empty.\n");
	}
	else {
		printf("The list is: ");
		while (current != NULL) {
			printf("%d ", current->size);
			current = current->next;
		}
		puts("");
	}
}

//��������� �������� �� ������ ������
int IsEmpty(Nodeptr Sptr) {
	return (int)(Sptr == NULL);
}

//������� ������� ���������� ���������� ������ ��� ��������� ��������,
//�� ������� ��������� ������, ������, ����������� �� ��� �������� 
//���������� ��� ��� �� �������� best fit
void bestfit(Listptr list, int value)
{
	Nodeptr ptr = NULL;
	int min = INF;
	int tmp;
	Nodeptr currentPtr = list->head;
	//� ���� ����� �� �������� ���������� ����� ���� ������ ����� ���������� ������ � ������
	//� ��� ���� � ���� ��� ����� �� ������ ������ ��� ��������� ��� �������
	while (currentPtr != NULL) {
		tmp = currentPtr->size - value;
		if (min > tmp && tmp >= 0) {
			min = tmp;
			ptr = currentPtr;
		}
		currentPtr = currentPtr->next;
	}
	if (min == INF) { printf("No suitable memory block\n"); }
	//����� �� � ���� ����� ������� ������ ��������� ���� ����� �������� ���������� ������ � ������
	//����������� ��� �������
	else {
		ptr->size = ptr->size - value;
		if (ptr->size == 0) {
			ptr->memory = NULL;
		}
		else {
			//������������ ������, ����� ������������� ��������� ������ ������� ��������
			void* PTR = (void*)realloc(ptr->memory, ptr->size);
			if (PTR != NULL) {
				ptr->memory = PTR;
			}
			else { printf("Memory is not reallocted\n"); }
		}
	}
}