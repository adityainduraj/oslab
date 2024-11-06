#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 5
#define MAX_PROCESSES 3

// Define the memory blocks and processes for allocation
int memoryBlocks[MAX_BLOCKS] = {100, 500, 200, 300, 600}; // Memory block sizes
int processSizes[MAX_PROCESSES] = {120, 200, 300};         // Process sizes to allocate

void firstFit() {
    int allocation[MAX_PROCESSES] = {-1, -1, -1}; // Stores block assigned to each process

    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_BLOCKS; j++) {
            if (memoryBlocks[j] >= processSizes[i]) { // First block that fits
                allocation[i] = j;
                memoryBlocks[j] -= processSizes[i];  // Reduce available memory in block // check if necessary
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (allocation[i] != -1) {
            printf("Process %d of size %d -> Block %d\n", i+1, processSizes[i], allocation[i] + 1);
        } else {
            printf("Process %d of size %d -> Not Allocated\n", i+1, processSizes[i]);
        }
    }
}

void bestFit() {
    int allocation[MAX_PROCESSES] = {-1, -1, -1}; // Stores block assigned to each process

    for (int i = 0; i < MAX_PROCESSES; i++) {
        int bestIdx = -1;

        for (int j = 0; j < MAX_BLOCKS; j++) {
            if (memoryBlocks[j] >= processSizes[i]) {
                if (bestIdx == -1 || memoryBlocks[j] < memoryBlocks[bestIdx]) {
                    bestIdx = j; // Find the smallest block that fits
                }
            }
        }

        if (bestIdx != -1) { // Allocate the best fit block found
            allocation[i] = bestIdx;
            memoryBlocks[bestIdx] -= processSizes[i]; // check if necessary
        }
    }

    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (allocation[i] != -1) {
            printf("Process %d of size %d -> Block %d\n", i+1, processSizes[i], allocation[i] + 1);
        } else {
            printf("Process %d of size %d -> Not Allocated\n", i+1, processSizes[i]);
        }
    }
}

int main() {
    // Run the First Fit algorithm
    firstFit();

    // Reset memory blocks for next allocation strategy
    int originalBlocks[MAX_BLOCKS] = {100, 500, 200, 300, 600};
    for (int i = 0; i < MAX_BLOCKS; i++) {
        memoryBlocks[i] = originalBlocks[i];
    }

    // Run the Best Fit algorithm
    bestFit();

    return 0;
}
