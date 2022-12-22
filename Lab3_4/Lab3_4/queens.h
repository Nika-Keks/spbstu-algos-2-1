#pragma once

/**
* Создает доску размера n на n с нулями
* 
* @param n размер доски
* 
* @return созданная доска
*/
int** boardCreate(int n);

/**
* Удаляет доску из памяти
* 
* @param board доска
* @param n размер доски
*/
void boardDestroy(int** board, int n);

/**
* Создает массив с королевами, заполенный -1(они еще не поставлены)
* 
* @param n количество королев
* 
* @return массив королев
*/
int* queensCreate(int n);

/**
* Удаляет массив королев
* 
* @param queens массив королев
*/
void queensDestroy(int* queens);

/**
* Ставит королев на доску
* 
* Печатает координаты королев в файл output.txt и наглядное представление матрицы в файл matrixOutput.txt
* 
* @param board доска
* @param queens массив королев
* @param cur номер текущей королевы
* @param n размер доски и количество королев
*/
void placeQueens(int** board, int* queens, int cur, int n);