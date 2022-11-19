#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"Header.h"
#pragma warning(disable:4996)


//функция вставляет элемент в дерево 
//дерево реализовано как двоичное дерево поиска
//поэтому если элемент меньше предка то он отправляется в левый узел
void InsertNode(TreeNodePtr* TreePtr, int value) {

	if (*TreePtr == NULL) {
		*TreePtr = (TreeNodePtr)malloc(sizeof(TreePtr));
		if (*TreePtr != NULL) {
			(*TreePtr)->data = value;
			(*TreePtr)->Right = NULL;
			(*TreePtr)->Left = NULL;
		}
		else {
			printf("NO memory available");
			return;
		}

	}
	else {
		if (value <= ((*TreePtr)->data)) {
			InsertNode(&((*TreePtr)->Left), value);
		}
		if (value > ((*TreePtr)->data)) {
			InsertNode(&((*TreePtr)->Right), value);
		}
	}
}

/*
Функция preOrder выполняет обход в три этапа :
1) обрабатывает значение узла;
2) вызывает preOrder для обхода левого поддерева;
3) вызывает preOrder для обхода правого поддерева;
*/
void Preorder(TreeNodePtr TreePtr) {
	if (TreePtr != NULL) {
		printf("%d ", TreePtr->data);
		Preorder(TreePtr->Left);
		Preorder(TreePtr->Right);
	}
}

/*
Функция preOrder2 выполняет обход в три этапа :
1) обрабатывает значение узла;
2) вызывает preOrder для обхода левого поддерева;
3) вызывает preOrder для обхода правого поддерева;
она выводит количество листьев для каждого узла 
*/
void Preorder2(TreeNodePtr TreePtr) {
	if (TreePtr != NULL) {
		printf("for %d a %d lists\n", TreePtr->data, TreePtr->lists);
		Preorder2(TreePtr->Left);
		Preorder2(TreePtr->Right);
	}
}

//функция рекурсивно считает количество листьев для каждого узла
int leafSum(TreeNodePtr TreePtr) {
	if (TreePtr == NULL) {
		return 0;
	}
	if (TreePtr->Left == NULL && TreePtr->Right == NULL) {
		TreePtr->lists = 1;
		return 1;
	}
	else {
		TreePtr->lists = leafSum(TreePtr->Left) + leafSum(TreePtr->Right);
		return TreePtr->lists;
	}
}


//функция заполняет матрицу размер которой равен наибольшему значению из всех
//которые мы могли бы получить используя rand()
//mas[i][j] = 1 if i is ancestor of j
//mas[i][j] = 0, otherwise

int ancestorMatrixRec(TreeNodePtr TreePtr, int mas[][Inf])
{
	if (TreePtr == NULL) return 0;;

	int l = ancestorMatrixRec(TreePtr->Left, mas);
	int r = ancestorMatrixRec(TreePtr->Right, mas);
	if (TreePtr->Left != NULL) {
		mas[TreePtr->data][l] = 1;
	}
	if (TreePtr->Right != NULL) {
		mas[TreePtr->data][r] = 1;
	}
	return TreePtr->data;
}

//функция выводит матрицу предков
void ancestorMatrix(TreeNodePtr TreePtr, int mas[][Inf])
{
	for (int i = 0; i < Inf; i++)
	{
		for (int j = 0; j < Inf; j++) {
			printf("%d ", mas[i][j]);
		}
		puts("");
	}
}

