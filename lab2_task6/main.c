#include <stdlib.h>
#include <stdio.h>
#include "utils.c"

#define MEMORY_BLOCKS_QUANTITY 4
#define MEMORY_BLOCK_SIZE 1024

typedef struct MemoryBlock {
  int id;
  size_t freeSpace;
  struct MemoryBlock* next;
} MemoryBlock;

typedef struct Process {
  int id;
  size_t size;
  struct Process* next;
  struct MemoryBlock* memoryBlock;
} Process;

MemoryBlock* memoryBlockHead;
Process* processHead;

MemoryBlock* getLastMemoryBlock() {
  MemoryBlock* head = memoryBlockHead;

  while (head->next) {
    head = head->next;
  }

  return head;
}

Process* getLastProcess() {
  Process* head = processHead;

  while (head->next) {
    head = head->next;
  }

  return head;
}

void initMemory() {
  for (int index = 0; index < MEMORY_BLOCKS_QUANTITY; index += 1) {
    MemoryBlock* memoryBlock = malloc(sizeof(MemoryBlock));
    memoryBlock->id = index;
    memoryBlock->freeSpace = MEMORY_BLOCK_SIZE;

    if (memoryBlockHead) {
      MemoryBlock *lastMemoryBlock = getLastMemoryBlock();
      lastMemoryBlock->next = memoryBlock;
    } else {
      memoryBlockHead = memoryBlock;
    }
  }
}

MemoryBlock* getBestFitMemoryBlock(size_t processSize) {
  MemoryBlock* bestBlock = NULL;
  MemoryBlock* currentBlock = memoryBlockHead;

  while (currentBlock) {
    if (currentBlock->freeSpace >= processSize && (!bestBlock || bestBlock->freeSpace > currentBlock->freeSpace)) {
      bestBlock = currentBlock;
    }
    currentBlock = currentBlock->next;
  }

  return bestBlock;
}

Process* newMalloc(size_t size) {
  if (!memoryBlockHead) {
    return NULL;
  }

  MemoryBlock* bestMemoryBlock = getBestFitMemoryBlock(size);

  if (!bestMemoryBlock) {
    printf("Could not allocate memory");
    exit(0);
  }

  Process* process = malloc(sizeof(Process));
  process->size = size;
  process->memoryBlock = bestMemoryBlock;
  bestMemoryBlock->freeSpace -= size;

  if (processHead) {
    Process* lastProcess = getLastProcess();
    lastProcess->next = process;
    process->id = lastProcess->id + 1;
  } else {
    processHead = process;
    process->id = 0;
  }

  return process;
}

void newFree(Process* node) {
  Process* previousNode = processHead;

  while (previousNode->next != node) {
    previousNode = previousNode->next;
  }

  previousNode->next = node->next;
  node->memoryBlock->freeSpace += node->size;
  free(node);
}

int integrityCheck() {
  size_t memorySum = 0;
  size_t freeSpaceSum = 0;
  Process* process = processHead;
  MemoryBlock* memoryBlock = memoryBlockHead;

  while (process) {
    memorySum += process->size;
    process = process->next;
  }

  while (memoryBlock) {
    freeSpaceSum += memoryBlock->freeSpace;
    memoryBlock = memoryBlock->next;
  }

  return memorySum + freeSpaceSum == MEMORY_BLOCKS_QUANTITY * MEMORY_BLOCK_SIZE;
}

void displayAllocations() {
  printf("Process ID | Process size | Block ID\n");
  printf("-----------+--------------+-----------\n");
  Process* process = processHead;
  while (process) {
    printf("%-11d| %-13zu| %d\n", process->id, process->size, process->memoryBlock->id);
    process = process->next;
  }
}
