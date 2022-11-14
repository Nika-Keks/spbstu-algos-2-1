#include<stdio.h>
#include<stdlib.h>
#define INF 1000000000
#pragma warning (disable:4996)


//узел списка который хранит память,
//которая у нас имеется чтобы выполнить какой-либо процесс
//и размер в байтах куска выделенной памяти
//указатели на след и предыдущий узел списка
typedef struct Node {
	void* memory;
	int size;
	struct Node* next;
	struct Node* prev;
}Node;
typedef Node* Nodeptr;


//Структура "Двусвязный Список" будет хранить свой размер (чтобы не пересчитывать количество элементов каждый раз),
//а также указатель head, ссылающийся на первый элемент, и указатель tail, ссылающийся на последний элемент
typedef struct List {
	size_t size;
	Nodeptr tail;
	Nodeptr head;
}List;
typedef struct List* Listptr;

//функция создает наш лист
Listptr CreateList() {
	Listptr tmp = (Listptr)malloc(sizeof(List));
	if (tmp != NULL) {
		tmp->size = 0;
		tmp->tail = tmp->head = NULL;
	}
	return tmp;
}

// Заодно опишем функцию, которая удаляет список
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


//функция нужна для того что бы вставить элемент в начало списка
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


//функция нужна для того что бы вставить элемент в конец списка

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

//Получение n-го элемента в списке
Nodeptr GetNth(Listptr list, int index) {
	Nodeptr tmp = list->head;
	int i = 0;
	while (tmp != NULL && i < index) {
		tmp = tmp->next;
		i++;
	}
	return tmp;
}


//универсальная функция вставки узла в список которая принимает на вход 
//указатель на лист, позицию куда надо вставить узел и память выделенную под процесс с ее размером
void Insert(Listptr list, int index, int size, void* value) {
	Nodeptr elm = NULL;//указатель на элемент после котрого мы будем вставлять новый узел
	Nodeptr ins = NULL;//указатель на новый узел
	if (list->size == 0) {//если размер списка 0 то вызываем функцию 
						  //pushfront которая добавляет узел в начало списка
		pushFront(list, value, size);
	}
	else {

		elm = GetNth(list, index);
		if (elm == NULL) {//если функция возвращает указатель на NULL то вставляем узел в конец списка
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

//функция принтует наш список
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

//проверяет является ли список пустым
int IsEmpty(Nodeptr Sptr) {
	return (int)(Sptr == NULL);
}

//функция которая занимается выделением памяти под некоторые процессы,
//на которые требуется память, память, расходуемая на эти процессы 
//выделяется под них по принципу best fit
void bestfit(Listptr list, int value)
{
	Nodeptr ptr = NULL;
	int min = INF;
	int tmp;
	Nodeptr currentPtr = list->head;
	//в этом цикле мы пытаемся определить какой блок памяти имеет наименьший размер в байтах
	//и при этом у него все равно не меньше памяти чем требуется под процесс
	while (currentPtr != NULL) {
		tmp = currentPtr->size - value;
		if (min > tmp && tmp >= 0) {
			min = tmp;
			ptr = currentPtr;
		}
		currentPtr = currentPtr->next;
	}
	if (min == INF) { printf("No suitable memory block\n"); }
	//здесь мы у того блока который прошел описанный выше отбор отнимаем количество памяти в байтах
	//расходуемое под процесс
	else {
		ptr->size = ptr->size - value;
		if (ptr->size == 0) {
			ptr->memory = NULL;
		}
		else {
			//перевыделяем память, чтобы котролировать количство памяти которое остается
			void* PTR = (void*)realloc(ptr->memory, ptr->size);
			if (PTR != NULL) {
				ptr->memory = PTR;
			}
			else { printf("Memory is not reallocted\n"); }
		}
	}
}