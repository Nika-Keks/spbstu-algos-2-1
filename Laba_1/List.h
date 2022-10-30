
#pragma once

typedef struct List {
	char* str;
	int len;
	struct List* next;
} List;

FILE* OpenFile(char* name, char* mode);//�������� ����� ��� ������ � ���
void FileClose(FILE* file);//�������� �����
List* NewListFromFile(FILE* file, char* format);//�������� ���� �������� ������ �� �����
void PrintList(List* list);//����� ����
void Matching(List* current, int num);//����� ���� � ������������ ������
void Input(List* head);//������ � ������������ �����
void Printer(List* list, int n, int cnt);//����� ����
List* CreationFromFile(FILE* file);//�������� ������
int SizeOfString(char* str);//���������� ����� ������
