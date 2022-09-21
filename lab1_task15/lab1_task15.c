#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming that words are not longer than 128 characters
#define MAX_WORD_LENGTH 128

char** readFile(char const *fileName, int* length) {
  FILE *fileStream = fopen(fileName, "r");

  if (!fileStream) {
    printf("Could not open the file %s", fileName);
    exit(0);
  }

  const int wordSize = sizeof(char) * MAX_WORD_LENGTH;
  char** wordsArray = malloc(0);
  char* buffer = malloc(wordSize);
  char* currentWord = malloc(wordSize);

  *length = 0;

  while (fscanf(fileStream, "%s", buffer) != EOF) {
    *length += 1;
    wordsArray = realloc(wordsArray, wordSize * (*length));
    memcpy(currentWord, buffer, wordSize);
    wordsArray[*length - 1] = currentWord;
    currentWord = malloc(wordSize);
  }

  fclose(fileStream);

  return wordsArray;
}

char** mergeArrays(
  const char** firstArray,
  const char** secondArray,
  const int firstLength,
  const int secondLength
) {
  const int wordSize = sizeof(char) * MAX_WORD_LENGTH;
  const char** mergedArray = malloc(wordSize * (firstLength + secondLength));

  for (int i = 0; i < firstLength; i += 1) {
    mergedArray[i] = firstArray[i];
  }
  for (int i = 0; i < secondLength; i += 1) {
    mergedArray[firstLength + i] = secondArray[i];
  }

  return mergedArray;
}

void insertionSort(char** array, const int length) {
  char* word;
  int j;

  for (int i = 1; i < length; i += 1) {
    word = array[i];
    j = i - 1;

    while (j >= 0 && strcmp(array[j], word) > 0) {
      array[j + 1] = array[j];
      j = j - 1;
    }

    array[j + 1] = word;
  }
}

void printArray(char** array, const int length) {
  for (int i = 0; i < length; i += 1) {
    printf("%s \n", array[i]);
  }
}

int main() {
  const char *firstFilename = "romeo-and-juliet.txt";
  const char *secondFilename = "othello.txt";

  int firstLength = 0;
  int secondLength = 0;

  const char** firstArray = readFile(firstFilename, &firstLength);
  const char** secondArray = readFile(secondFilename, &secondLength);

  const char **mergedArray = mergeArrays(
    firstArray,
    secondArray,
    firstLength,
    secondLength
  );
  const finalLength = firstLength + secondLength;

  insertionSort(mergedArray, finalLength);

  printArray(mergedArray, finalLength);

  return 0;
}
