#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./main.h"

void printItem(char* word) {
  printf("%s\n", word);
}

int main() {
  const char* firstFilename = "./mockData/romeo-and-juliet.txt";
  const char* secondFilename = "./mockData/othello.txt";

  Node* firstArray = readFile(firstFilename);
  Node* secondArray = readFile(secondFilename);
  Node* mergedArray = mergeArrays(firstArray, secondArray);

  insertionSort(mergedArray);

  listForEach(mergedArray, printItem);

  return 0;
}
