#include <stdio.h>
#include <stdlib.h>
#include "header.h"

#pragma warning(disable:4996)

/*
* enter - (0;0)
* exit - (9;9)
*/

 int main() {
     char* file = "mazeMatrix.txt";
     FindPath(file);

     return 0;
 }