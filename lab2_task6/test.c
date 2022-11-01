#include "main.h"

int main() {
  int blocksCount;
  int processesCount;
  int* blocks = getMemoryBlocks(&blocksCount);
  int* processes = getProcesses(&processesCount);
  int* allocations = bestFit(blocks, blocksCount, processes, processesCount);

  displayAllocations(allocations, processes, processesCount);

  return 0;
}
