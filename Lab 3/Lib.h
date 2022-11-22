#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include <math.h> 
#pragma warning(disable:4996)

typedef struct {// point 
	float x;
	float y;
} Point;

typedef struct List// list of points
{
	Point* point;
	struct List* next;
} List;

FILE* OpenFile(char* name, char* mode);// function for safe file's opening
void FileClose(FILE* file);// function for file's closing
Point* NewPoint(float x, float y);// creation the new point by 2 values
List* NewList(Point* point);// creation the new list
List* GetLast(List* head);// getting the lat pointer
void PushBack(List* head, Point* a);// addition the new point in the end of the list
Point* NewPointFromFile(FILE* file, char* format);// creattion the new point from file
List* CreationFromFile(FILE* file);// getting all points from file and writing them to the list
int roundermax(float a);// getting a round of number with bigger abs
int roundermin(float a);// getting a round of number with lower abs
Point* Rangex(List* head);//getting a range from y-axis
Point* Rangey(List* head);//getting a range from x-axis
Point* Dot(int y, Point* a1, Point* a2);// getting section with horizontal
void Rasterize(List* apex);// rasterization

