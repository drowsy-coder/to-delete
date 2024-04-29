#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_BLOCKS 5
#define N_REQUESTS 4

// Helper function to print memory blocks
void printBlocks(int memory[], int n_blocks) {
    printf("Memory Blocks: ");
    for (int i = 0; i < n_blocks; i++) {
        printf("%d ", memory[i]);
    }
    printf("\n");
}

// First-fit Algorithm
void firstFit(int blocks[], int n_blocks, int requests[], int n_requests) {
    int allocation[N_REQUESTS];

    for (int i = 0; i < n_requests; i++) {
        allocation[i] = -1;  // Initialize allocations
    }

    for (int i = 0; i < n_requests; i++) {
        for (int j = 0; j < n_blocks; j++) {
            if (blocks[j] >= requests[i]) {
                allocation[i] = j;  // Allocate block j to request i
                blocks[j] -= requests[i];  // Reduce available memory in block
                break;
            }
        }
    }

    printf("First-Fit Allocation:\n");
    printBlocks(blocks, n_blocks);
}

// Best-fit Algorithm
void bestFit(int blocks[], int n_blocks, int requests[], int n_requests) {
    int allocation[N_REQUESTS];

    for (int i = 0; i < n_requests; i++) {
        allocation[i] = -1;  // Initialize allocations
    }

    for (int i = 0; i < n_requests; i++) {
        int bestIdx = -1;
        for (int j = 0; j < n_blocks; j++) {
            if (blocks[j] >= requests[i]) {
                if (bestIdx == -1 || blocks[j] < blocks[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blocks[bestIdx] -= requests[i];
        }
    }

    printf("Best-Fit Allocation:\n");
    printBlocks(blocks, n_blocks);
}

// Worst-fit Algorithm
void worstFit(int blocks[], int n_blocks, int requests[], int n_requests) {
    int allocation[N_REQUESTS];

    for (int i = 0; i < n_requests; i++) {
        allocation[i] = -1;  // Initialize allocations
    }

    for (int i = 0; i < n_requests; i++) {
        int worstIdx = -1;
        for (int j = 0; j < n_blocks; j++) {
            if (blocks[j] >= requests[i]) {
                if (worstIdx == -1 || blocks[j] > blocks[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blocks[worstIdx] -= requests[i];
        }
    }

    printf("Worst-Fit Allocation:\n");
    printBlocks(blocks, n_blocks);
}

int main() {
    int blocks[N_BLOCKS] = {100, 500, 200, 300, 600};
    int requests[N_REQUESTS] = {212, 417, 112, 426};

    int blocksCopy[N_BLOCKS];

    // First-fit
    memcpy(blocksCopy, blocks, sizeof(blocks));
    firstFit(blocksCopy, N_BLOCKS, requests, N_REQUESTS);

    // Best-fit
    memcpy(blocksCopy, blocks, sizeof(blocks));
    bestFit(blocksCopy, N_BLOCKS, requests, N_REQUESTS);

    // Worst-fit
    memcpy(blocksCopy, blocks, sizeof(blocks));
    worstFit(blocksCopy, N_BLOCKS, requests, N_REQUESTS);

    return 0;
}
