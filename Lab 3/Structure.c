#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <malloc.h>
#include <locale.h>
#include "./Lib.h"

#pragma warning(disable:4996)
FILE* OpenFile(char* name, char* mode)// function for safe file's opening
{
	FILE* fp;
	if ((fp = fopen(name, mode)) == NULL)
	{
		printf("Failed to open file");
		exit(1);
	}
	return fp;
}

void FileClose(FILE* file)// function for file's closing
{
	fclose(file);
}

Point* NewPoint(float x, float y)// creation the new point by 2 values
{
	Point* point;
	if (!(point = (Point*)malloc(sizeof(Point))))
	{
		printf("Allocation error.");
		exit(1);
	}
	point->x = x;
	point->y = y;
	return point;
}

List* NewList(Point* point)// creation the new list
{
	List* list;
	if (!(list = (List*)malloc(sizeof(List))))
	{
		printf("Allocation error.");
		exit(1);
	}
	list->point = point;
	list->next = NULL;
	return list;
}

List* GetLast(List* head)// getting the lat pointer
{
	if(head == NULL) 
	{
		return NULL;
	}
	while (head->next != NULL) 
	{
		head = head->next;
	}
	return head;
}

void PushBack(List* head, Point* a)// addition the new point in the end of the list
{
	List* head1 = head;
	List* last = GetLast(head1);
	List* tmp = (List*)malloc(sizeof(List));
	if (tmp)
	{
		tmp->point = a;
		tmp->next = NULL;
		last->next = tmp;
	}	
}

Point* NewPointFromFile(FILE* file, char* format)// creattion the new point from file
{
	int x;
	int y;
	if ((fscanf(file, format, &x, &y)) != EOF)
	{
		return NewPoint((float)x, (float)y);
	}
	return NULL;
}

List* CreationFromFile(FILE* file)// getting all points from file and writing them to the list
{
	List* head = NULL;
	List* current = NULL;
	char* format = "%d %d";
	Point* p = NewPointFromFile(file, format);
	current = NewList(p);
	head = current;
	while ((p = NewPointFromFile(file, format)) !=  NULL)
	{		
		PushBack(current, p);
	}
	return head;
}

int roundermax(float a)// getting a round of number with bigger abs
{
	if (a != 0)
	{
		return((fabs(a) / a) * ceil(fabs(a)));
	}
	else
		return 0;
}

int roundermin(float a)// getting a round of number with lower abs
{
	if (a != 0)
	{
		return((fabs(a) / a) * floor(fabs(a)));
	}
	else
		return 0;
}

Point* Rangey(List* head)//getting a range from y-axis
{

	float min = head->point->y;
	float max = head->point->y;
	head = head->next;
	while (head != NULL)
	{	
		if (min > head->point->y)
		{
			min = head->point->y;
		}
		if (max < head->point->y)
		{
			max = head->point->y;
		}		
		head = head->next;
	}
	
	 return NewPoint((float)roundermax(min),(float)roundermax(max));
}
Point* Rangex(List* head)//getting a range from x-axis
{
	float min = head->point->x;
	float max = GetLast(head)->point->x;
	return NewPoint((float)roundermax(min), (float)roundermax(max));
}

Point* Dot(int y, Point* a1, Point* a2)// getting section with horizontal
{
	float x1 = a1->x;
	float x2 = a2->x;
	float y1 = a1->y;
	float y2 = a2->y;
	float x;
	if (y1 != y2)
	{
		x = (y - y1) * (x2 - x1) / (y2 - y1) + x1;// straight line equation through 2 points
	}
	else
	{
		x = (x1 >= x2) ? x2 : x1;
	}
	return(NewPoint(x,(float)y));
}

void Rasterize(List* apex)
{
	List* head0 = apex;
	List* head1 = apex;
	List* head2; List* head3;
	int pl = abs(roundermax(Rangey(head1)->x));//diplacement
	head1 = head0;
	int n = abs(roundermax(Rangey(head1)->y)) - pl;//height
	head1 = head0;
	int m = abs(roundermax(Rangex(head1)->y)) - abs(roundermax(Rangex(head1)->x));//wide
	head1 = head0;
	Point* a1 = head1->point;//first apex
	Point* a0 = a1;
	Point* a2;
	int i = 0;
	float x1, x2,r;
	int counter= 0;
	float zeros = (int)pow(9, 7)- 0.1;//symbol of absence 
	Point* zerosp = NewPoint(zeros, zeros);
	List** mass = (List**)malloc((n + 1) * sizeof(List*));//array of lists of sections with horizontals
	int** A = (int**)malloc(n * sizeof(int*));//matrix of squares for output on grid
	int k = 0; int j = 0;
	for (k = 0; k < n; k++) //memory allocation
	{
		A[k] = (int*)malloc(m * sizeof(int));
	}
	k = 0;
	for (k = 0; k < n; k++)//zero padding
	{
		for (j = 0; j < m; j++)
		{
			A[k][j] = 0;
		}
	}
	k = 0;j = 0;
	do
	{
		head1 = head1->next;
		a2 = head1->point;//second apex of увпу
		for (i = 0;i <= n;i++)//searching sections with all avaliable horizontal lines
		{
			if ((a1->y >= i + pl && i + pl >= a2->y) || (a1->y <= i + pl && i + pl <= a2->y))
			{
				if (counter == 0)//for the first edge
				{
					mass[i] = NewList(Dot(i+pl, a1, a2));
				}
				else//futher edges
				{
					PushBack(mass[i], Dot(i + pl, a1, a2));
				}
			}
			else
			{
				if (counter == 0 )//for the first edge
				{
					mass[i] = NewList(zerosp);
				}
				else//futher edges
				{
					PushBack(mass[i], zerosp);
				}
			} 		
			if (i !=0)//interpretation sections to squares on grid 
			{		
				head2 = mass[i - 1];
				head3 = mass[i];
				for (j = 0;j < counter;j++)//moving the pointer
				{
					head2 = head2->next;
					head3 = head3->next;
				}
				j = 0;
				x1 = (head2->point->x);
				x2 = (head3->point->x);				
				x1 -= pl;
				x2 -= pl;
				if (head2->point != zerosp && head3->point != zerosp)//checking the maching with the symbol of absence				
				{
					if (a1->x <= x1 && x1 <= a2->x && a1->x <= x2 && x2 <= a2->x )//checking ccontaining section in a range
					{
						if (x2 < x1)//changing order
						{
							r = x2;
							x2 = x1;
							x1 = r;
						}
						x1 = roundermin(x1);
						x2 = roundermax(x2);
						for (j = x1; j < x2;j++)//filling
						{
							A[i - 1][j] = 1;
						}
					}
				}
				
			}
		}	
		a1 = a2;
		counter++;
	} while (head1->next);

	//begin of  actions with the last edge (272 line - 332 line). All actions are similar 
	a1 = a0;
	for (i = 0;i <= n;i++)
	{
		if ((a1->y >= i + pl && i + pl >= a2->y) || (a1->y <= i + pl && i + pl <= a2->y))
		{
			if (counter == 0)
			{
				mass[i] = NewList(Dot(i + pl, a1, a2));
			}
			else
			{
				PushBack(mass[i], Dot(i + pl, a1, a2));
			}
		}
		else
		{
			if (counter == 0)
			{
				mass[i] = NewList(zerosp);
			}
			else
			{
				PushBack(mass[i], zerosp);
			}
		}
		if (i != 0)
		{
			head2 = mass[i - 1];
			head3 = mass[i];
			for (j = 0;j < counter;j++)
			{
				head2 = head2->next;
				head3 = head3->next;
			}
			j = 0;
			x1 = (head2->point->x);
			x2 = (head3->point->x);
			x1 -= pl;
			x2 -= pl;
			if (head2->point != zerosp && head3->point != zerosp)
			{	
				if (a1->x <= x1 && x1 <= a2->x && a1->x <= x2 && x2 <= a2->x)
				{
					if (x2 < x1)
					{
						r = x2;
						x2 = x1;
						x1 = r;
					}
					x1 = roundermin(x1);
					x2 = roundermax(x2);
					for (j = x1; j <= x2;j++)
					{
						A[i - 1][j] = 1;
					}
				}
			}
		}
	}
	//end of actions with the last edge
	//filling squares inside edges
	/*Algorithm for filling operation. Moving along the line, we find a filled square.
	Next, look for an unfilled square.
	If one is found, it will be suspicious for painting. To determine,
	whether this square is really inside the polygon, you need to check that in the same line to the right
	a filled square was found, as well as below and above the current column.
	If everything is done, then the current cell paint over.
	*/
	int flag1x = 0;
	for (int k_y = n - 1; k_y >= 0; k_y--)//moving in column
	{
		for (int k_x = 0; k_x < m; k_x++)//moving in line
		{
			if ((A[k_y][k_x] == 1)) flag1x = 0;
			if (A[k_y][k_x] == 0 && flag1x == 0)
			{
				for (int k_2x = k_x; k_2x < m; k_2x++)
				{
					if (A[k_y][k_2x] == 1)
					{
						for (int k_1y = k_y; k_1y <= n - 1; k_1y++)
						{
							if (A[k_1y][k_x] == 1)
							{
								for (int k_2y = k_y; k_2y >= 0; k_2y--)
								{
									if (A[k_2y][k_x] == 1)
									{
										A[k_y][k_x] = 1;
									}					
								}
							}
						}		
					}				
				}		
			}
		}
	}
	printf("\n");
	for (int k_y = n - 1; k_y >= 0; k_y--)//output
	{
		for (int k_x = 0; k_x < m; k_x++)
		{
			printf(" %d ", A[k_y][k_x]);
		}
		printf("\n");
	}

}


