#include <stdio.h>
#include <stdlib.h>

int* readNumbers(char* filename) {
  FILE* fileStream = fopen(filename, "r");

  if (!fileStream) {
    printf("Could not open the file %s", filename);
    exit(0);
  }

  int* numbers = malloc(sizeof(int) * 2);

  fscanf(fileStream, "%d\n%d", &numbers[0], &numbers[1]);

  fclose(fileStream);

  return numbers;
}
