#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

// typedef struct MemoryBlock {
//   int size;
//   struct MemoryBlock* nextPart;
// } MemoryBlock;

// typedef struct Process {
//   int blockIndex;
//   int size;
//   struct Process* nextPart;
// } Process;

int* bestFit(int* blocks, int blocksCount, int* processes, int processesCount) {
  int *allocations = malloc(sizeof(int) * processesCount);

  for (int processIndex = 0; processIndex < processesCount; processIndex += 1) {
    int processSize = processes[processIndex];
    int smallestIndex = -1;
    int smallestSize = -1;
    for (int blockIndex = 0; blockIndex < blocksCount; blockIndex += 1) {
      int blockRemainingSize = blocks[blockIndex];
      if (processIndex == 3)
        printf("%d, %d, %d\n", blockIndex, blockRemainingSize, processSize);
      if (blockRemainingSize < processSize)
        continue;
      if (smallestSize != -1 && smallestSize <= blockRemainingSize)
        continue;
      smallestSize = blockRemainingSize;
      smallestIndex = blockIndex;
    }
    allocations[processIndex] = smallestIndex;
    blocks[smallestIndex] -= processSize;
  }

  return allocations;
}

void displayAllocations(int* allocations, int* processes, int processesCount) {
  printf("Process number | Process size | Block number\n");
  printf("---------------+--------------+-------------\n");
  for (int processIndex = 0; processIndex < processesCount; processIndex += 1) {
    int processNumber = processIndex + 1;
    int processSize = processes[processIndex];
    char* blockNumber = allocations[processIndex] == -1
      ? "Not allocated"
      : intToString(allocations[processIndex] + 1);
    printf("%-15d| %-13d| %s\n", processNumber, processSize, blockNumber);
  }
}

int* getMemoryBlocks(int* count) {
  printf("Enter the number of blocks: ");
  scanf("%d", count);

  int* blocks = malloc(sizeof(int) * *count);

  for (int index = 0; index < *count; index += 1) {
    printf("Enter size of block number %d: ", index + 1);
    scanf("%d", &blocks[index]);
  }

  return blocks;
}

int* getProcesses(int* count) {
  printf("Enter the number of processes: ");
  scanf("%d", count);

  int* processes = malloc(sizeof(int) * *count);

  for (int index = 0; index < *count; index += 1) {
    printf("Enter size of process number %d: ", index + 1);
    scanf("%d", &processes[index]);
  }

  return processes;
}
