#pragma once

/**
* Структура для описания даты.
*/
typedef struct {
	unsigned int day; ///< день
	unsigned int month; ///< месяц
	unsigned int year; ///< год
} Date;

/**
* Структура для описания температуры по дням.
*/
typedef struct Stats {
	Date* date; ///< дата
	float temp; ///< температура
	struct Stats* next; ///< следующий элемент в списке
} Stats;

/**
* Создает новую дату.
* 
* @param day день
* @param month месяц
* @param year год
* 
* @return созданная дата
*/
Date* newDate(unsigned char day, unsigned char month, unsigned int year);

/**
* Удаляет из памяти дату.
* 
* @param date дата для удаления
*/
void destroyDate(Date* date);

/**
* Создает новую запись статистики.
* 
* @param date дата
* @param temp температура
* 
* @return созданная запись
*/
Stats* newStats(Date* date, float temp);

/**
* Удаляет запись из памяти.
* 
* @param stats запись для удаления
*/
void destroyStats(Stats* stats);

/**
* Удаляет из памяти список записей со статистикой.
* 
* @param head начало списка
*/
void destroyStatsList(Stats* head);

/**
* Вставляет новую запись в нужное место в списке.
* 
* @param head начало списка
* @param stats запись, которую нужно вставить
* 
* @return новое начало списка
*/
Stats* insertStats(Stats* head, Stats* stats);

/**
* Возвращает список записей из файла.
* 
* @param file файл для чтения
* @param format формат чтения данных
*/
Stats* statsListFromFile(char* name);

/**
* Печатает данные записи.
* 
* @param stats запись для печати
*/
void printStats(Stats* stats);

/**
* Печатает первую запись с совпавшей температурой
* 
* @param head список записей
* @param input температура, с которой ищут совпадение
*/
void printMatchingTemp(Stats* head, float input);

/**
* Печатает первую запись с совпавшей температурой с просьбой о введении температуры.
* 
* @param head список записей
*/
void printMatchingTempPrompted(Stats* head);

/**
* Запускает программу с переданным названием файла.
* 
* @param name название файла
*/
void actionOnFile(char* name);