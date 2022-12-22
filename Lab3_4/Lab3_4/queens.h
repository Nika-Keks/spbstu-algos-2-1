#pragma once

/**
* ������� ����� ������� n �� n � ������
* 
* @param n ������ �����
* 
* @return ��������� �����
*/
int** boardCreate(int n);

/**
* ������� ����� �� ������
* 
* @param board �����
* @param n ������ �����
*/
void boardDestroy(int** board, int n);

/**
* ������� ������ � ����������, ���������� -1(��� ��� �� ����������)
* 
* @param n ���������� �������
* 
* @return ������ �������
*/
int* queensCreate(int n);

/**
* ������� ������ �������
* 
* @param queens ������ �������
*/
void queensDestroy(int* queens);

/**
* ������ ������� �� �����
* 
* �������� ���������� ������� � ���� output.txt � ��������� ������������� ������� � ���� matrixOutput.txt
* 
* @param board �����
* @param queens ������ �������
* @param cur ����� ������� ��������
* @param n ������ ����� � ���������� �������
*/
void placeQueens(int** board, int* queens, int cur, int n);