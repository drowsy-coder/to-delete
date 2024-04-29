#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int burst_time;
    int arrival_time;
    int priority; // Only used for Priority Scheduling
} Process;

void printProcesses(Process p[], int size) {
    printf("ID\tBurst\tArrival\tPriority\n");
    for (int i = 0; i < size; i++) {
        printf("%d\t%d\t%d\t%d\n", p[i].id, p[i].burst_time, p[i].arrival_time, p[i].priority);
    }
}

void FCFS(Process processes[], int n) {
    int wait_time = 0, total_wait_time = 0;
    int turnaround_time = 0, total_turnaround_time = 0;

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        turnaround_time = processes[i].burst_time + wait_time;
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burst_time, wait_time, turnaround_time);

        total_wait_time += wait_time;
        total_turnaround_time += turnaround_time;
        wait_time += processes[i].burst_time;
    }

    printf("Average Waiting Time: %.2f\n", (float)total_wait_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int compareByBurstTime(const void *a, const void *b) {
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;
    return p1->burst_time - p2->burst_time;
}

void SJF(Process processes[], int n) {
    qsort(processes, n, sizeof(Process), compareByBurstTime);
    FCFS(processes, n); // Reusing FCFS since SJF is simply FCFS with sorted input
}

void RoundRobin(Process processes[], int n, int quantum) {
    int remaining_burst[n];
    for (int i = 0; i < n; i++) {
        remaining_burst[i] = processes[i].burst_time;
    }

    int current_time = 0, completed = 0;
    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (remaining_burst[i] > 0) {
                if (remaining_burst[i] > quantum) {
                    current_time += quantum;
                    remaining_burst[i] -= quantum;
                } else {
                    current_time += remaining_burst[i];
                    printf("Process %d finishes at %d\n", processes[i].id, current_time);
                    remaining_burst[i] = 0;
                    completed++;
                }
            }
        }
    }
}

int compareByPriority(const void *a, const void *b) {
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;
    return p1->priority - p2->priority; // Ascending order of priority
}

void PriorityScheduling(Process processes[], int n) {
    qsort(processes, n, sizeof(Process), compareByPriority);
    FCFS(processes, n); // Reusing FCFS since Priority Scheduling is simply FCFS with sorted input
}



int main() {
    Process processes[] = {
        {1, 6, 1, 2}, {2, 8, 1, 1}, {3, 7, 2, 3}, {4, 3, 3, 2}
    };
    int n = sizeof(processes) / sizeof(processes[0]);

    printf("FCFS Scheduling:\n");
    FCFS(processes, n);

    printf("\nSJF Scheduling:\n");
    SJF(processes, n);

    printf("\nRound Robin Scheduling (Quantum = 4):\n");
    RoundRobin(processes, n, 4);

    printf("\nPriority Scheduling:\n");
    PriorityScheduling(processes, n);

    return 0;
}
