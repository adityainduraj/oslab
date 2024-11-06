#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
} Process;

void resetRemainingTime(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }
}

void preemptive_SJF(Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    int prev = -1;

    while (completed < n) {
        int shortest = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (shortest == -1 || processes[i].remaining_time < processes[shortest].remaining_time) {
                    shortest = i;
                }
            }
        }

        if (shortest != -1 && shortest != prev) {
            if (prev != -1 && processes[prev].remaining_time == 0) {
                printf("Process %d completed at time %d\n", processes[prev].pid, current_time);
                completed++;
            }
            prev = shortest;
            printf("Process %d started at time %d\n", processes[shortest].pid, current_time);
        }

        if (shortest != -1) {
            processes[shortest].remaining_time--;
            current_time++;
        } else {
            current_time++;
        }

        if (shortest != -1 && processes[shortest].remaining_time == 0) {
            printf("Process %d completed at time %d\n", processes[shortest].pid, current_time);
            completed++;
            prev = -1;
        }
    }
}

void non_preemptive_priority(Process processes[], int n) {
    int current_time = 0;
    int completed = 0;

    while (completed < n) {
        int highest_priority = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (highest_priority == -1 || processes[i].priority > processes[highest_priority].priority) {
                    highest_priority = i;
                }
            }
        }

        if (highest_priority != -1) {
            printf("Process %d started at time %d\n", processes[highest_priority].pid, current_time);
            current_time += processes[highest_priority].remaining_time;
            processes[highest_priority].remaining_time = 0;
            printf("Process %d completed at time %d\n", processes[highest_priority].pid, current_time);
            completed++;
        } else {
            current_time++;
        }
    }
}

int main() {
    int n, choice;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter details for process %d:\n", i + 1);
        printf("Arrival time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);

        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }

    while (1) {
        printf("\nMenu:\n");
        printf("1. Preemptive SJF\n");
        printf("2. Non-preemptive priority\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                resetRemainingTime(processes, n);
                preemptive_SJF(processes, n);
                break;
            case 2:
                resetRemainingTime(processes, n);
                non_preemptive_priority(processes, n);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
