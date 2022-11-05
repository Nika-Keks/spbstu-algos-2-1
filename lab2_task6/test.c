#include "main.c"

int main() {
  initMemory();

  Process* pointer1 = newMalloc(228);
  Process* pointer2 = newMalloc(1000);
  Process* pointer3 = newMalloc(125);
  Process* pointer4 = newMalloc(1000);
  Process* pointer5 = newMalloc(300);
  Process* pointer6 = newMalloc(100);

  newFree(pointer2);

  displayAllocations();

  printf("\n");

  if (integrityCheck()) {
    printf("Memory is consistent :)");
  } else {
    printf("Memory is not consistent :(");
  }

  return 0;
}
