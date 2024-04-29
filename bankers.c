#include <stdio.h>  

int main() {  
    // Define the number of processes and resources
    int n = 5; // Number of processes  
    int m = 3; // Number of resources  

    // Allocation matrix: Current allocation for each process
    int alloc[5][3] = {
        {0, 1, 0}, // P0
        {2, 0, 0}, // P1
        {3, 0, 2}, // P2
        {2, 1, 1}, // P3
        {0, 0, 2}  // P4
    };

    // Maximum demand matrix for each process
    int max[5][3] = {
        {7, 5, 3}, // P0
        {3, 2, 2}, // P1
        {9, 0, 2}, // P2
        {2, 2, 2}, // P3
        {4, 3, 3}  // P4
    };

    // Available instances of resources
    int avail[3] = {3, 3, 2};

    // Finish flag for each process, 0 means not finished
    int f[n], ans[n], ind = 0;
    for (int k = 0; k < n; k++) {
        f[k] = 0;
    }

    // Need matrix: Remaining needs of each process
    int need[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Try to find a safe sequence
    for (int k = 0; k < 5; k++) {
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {  // Process has not finished
                int flag = 0;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {  // If needs cannot be met
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {  // If the process can be given resources
                    ans[ind++] = i;  // Add this process to safe sequence
                    for (int y = 0; y < m; y++) {
                        avail[y] += alloc[i][y];  // Release resources
                    }
                    f[i] = 1;  // Mark process as finished
                }
            }
        }
    }

    // Check if all processes are finished
    int flag = 1;
    for (int i = 0; i < n; i++) {
        if (f[i] == 0) {
            flag = 0;
            printf("The following system is not safe\n");
            break;
        }
    }

    // If all processes are finished, print the safe sequence
    if (flag == 1) {
        printf("Following is the SAFE Sequence\n");
        for (int i = 0; i < n - 1; i++) {
            printf(" P%d ->", ans[i]);
        }
        printf(" P%d\n", ans[n - 1]);
    }

    return 0;  
}
