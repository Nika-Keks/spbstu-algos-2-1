#pragma once

int* bestFit(int* blocks, int blocksCount, int* processes, int processesCount);

void displayAllocations(int* allocations, int* processes, int processesCount);

int* getMemoryBlocks(int* count);

int* getProcesses(int* count);
