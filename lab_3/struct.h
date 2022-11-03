#pragma once
typedef struct list
{
	char* group;
	char* surname;
	char* name;
	char* patronymic;
	int mark1;
	int mark2;
	int mark3;
	struct list* next;
}list;


list* Create_Node(char* group, char* surname, char* name, char* patronymic, int mark1, int mark2, int mark3);
list* Create_Node_From_File(FILE* file, char* format);
list* Insert(list* list_1, list* list_2);
list* Create_List_From_File(FILE* file);
void Print_List(list* head);
void Print_Massive_List(list** head, int q);
void Push_Back(list* head_ref, char* group, char* surname, char* name, char* patronymic, int mark1, int mark2, int mark3);
list** Create_And_Print_Massive_List(list* head);
void Add_Student(list* head);
void Delete_Student(list* head);
void Stipendia(list* head);
void Otchislenie(list* head);
void All_Operations(FILE* file);
