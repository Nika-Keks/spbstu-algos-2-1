#pragma once

/**
* ��������� ��� �������� ����.
*/
typedef struct {
	unsigned int day; ///< ����
	unsigned int month; ///< �����
	unsigned int year; ///< ���
} Date;

/**
* ��������� ��� �������� ����������� �� ����.
*/
typedef struct Stats {
	Date* date; ///< ����
	float temp; ///< �����������
	struct Stats* next; ///< ��������� ������� � ������
} Stats;

/**
* ������� ����� ����.
* 
* @param day ����
* @param month �����
* @param year ���
* 
* @return ��������� ����
*/
Date* newDate(unsigned char day, unsigned char month, unsigned int year);

/**
* ������� �� ������ ����.
* 
* @param date ���� ��� ��������
*/
void destroyDate(Date* date);

/**
* ������� ����� ������ ����������.
* 
* @param date ����
* @param temp �����������
* 
* @return ��������� ������
*/
Stats* newStats(Date* date, float temp);

/**
* ������� ������ �� ������.
* 
* @param stats ������ ��� ��������
*/
void destroyStats(Stats* stats);

/**
* ������� �� ������ ������ ������� �� �����������.
* 
* @param head ������ ������
*/
void destroyStatsList(Stats* head);

/**
* ��������� ����� ������ � ������ ����� � ������.
* 
* @param head ������ ������
* @param stats ������, ������� ����� ��������
* 
* @return ����� ������ ������
*/
Stats* insertStats(Stats* head, Stats* stats);

/**
* ���������� ������ ������� �� �����.
* 
* @param file ���� ��� ������
* @param format ������ ������ ������
*/
Stats* statsListFromFile(char* name);

/**
* �������� ������ ������.
* 
* @param stats ������ ��� ������
*/
void printStats(Stats* stats);

/**
* �������� ������ ������ � ��������� ������������
* 
* @param head ������ �������
* @param input �����������, � ������� ���� ����������
*/
void printMatchingTemp(Stats* head, float input);

/**
* �������� ������ ������ � ��������� ������������ � �������� � �������� �����������.
* 
* @param head ������ �������
*/
void printMatchingTempPrompted(Stats* head);

/**
* ��������� ��������� � ���������� ��������� �����.
* 
* @param name �������� �����
*/
void actionOnFile(char* name);