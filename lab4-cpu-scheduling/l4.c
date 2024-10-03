#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;        // Process ID
    int arrival;   // Arrival time
    int burst;     // Burst time
    int waiting;   // Waiting time
    int turnaround; // Turnaround time
    int priority;   // Priority (for priority scheduling)
} Process;

// Function prototypes
void calculateWaitingTimeSJF(Process processes[], int n);
void calculateWaitingTimeRR(Process processes[], int n, int quantum);
void calculateWaitingTimePriority(Process processes[], int n);
void calculateTurnaroundTime(Process processes[], int n);
void printProcessDetails(Process processes[], int n);

// Function to calculate waiting time for Non-Preemptive SJF
void calculateWaitingTimeSJF(Process processes[], int n) {
    int completed = 0, currentTime = 0, minIndex;
    while (completed < n) {
        minIndex = -1;  // Reset minIndex
        int minBurst = 9999;  // Set high initial burst time

        // Find process with shortest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime && processes[i].waiting == -1) {
                if (processes[i].burst < minBurst) {
                    minBurst = processes[i].burst; // Update minimum burst time
                    minIndex = i; // Update index of the process
                }
            }
        }

        // If a process is found
        if (minIndex != -1) {
            processes[minIndex].waiting = currentTime - processes[minIndex].arrival; // Update waiting time
            currentTime += processes[minIndex].burst; // Move current time forward
            completed++; // Increment completed processes
            processes[minIndex].turnaround = processes[minIndex].waiting + processes[minIndex].burst; // Update turnaround time
        } else {
            currentTime++; // If no process is ready, increment time
        }
    }
}

// Function to calculate waiting time for Preemptive SJF
void calculateWaitingTimePreemptiveSJF(Process processes[], int n) {
    int completed = 0, currentTime = 0;
    int remaining[n];
    for (int i = 0; i < n; i++) {
        remaining[i] = processes[i].burst; // Initialize remaining burst times
        processes[i].waiting = -1; // Initialize waiting time
    }

    while (completed < n) {
        int minIndex = -1;
        int minBurst = 9999;

        // Find the process with the shortest remaining burst time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime && remaining[i] > 0 && remaining[i] < minBurst) {
                minBurst = remaining[i];
                minIndex = i;
            }
        }

        if (minIndex != -1) {
            remaining[minIndex]--; // Execute the process for 1 time unit
            if (remaining[minIndex] == 0) { // Process completed
                processes[minIndex].waiting = currentTime + 1 - processes[minIndex].arrival - processes[minIndex].burst;
                processes[minIndex].turnaround = currentTime + 1 - processes[minIndex].arrival;
                completed++;
            }
        }
        currentTime++; // Move time forward
    }
}

// Function to calculate waiting time for Round Robin
void calculateWaitingTimeRR(Process processes[], int n, int quantum) {
    int remaining[n];
    for (int i = 0; i < n; i++) {
        remaining[i] = processes[i].burst; // Initialize remaining burst times
        processes[i].waiting = -1; // Initialize waiting time
    }

    int completed = 0, currentTime = 0;
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime && remaining[i] > 0) {
                if (remaining[i] > quantum) {
                    remaining[i] -= quantum; // Execute process for quantum time
                    currentTime += quantum; // Move time forward
                } else {
                    currentTime += remaining[i]; // Execute remaining time
                    processes[i].waiting = currentTime - processes[i].arrival - processes[i].burst; // Calculate waiting time
                    remaining[i] = 0; // Process completed
                    completed++;
                }
            }
        }
        currentTime++; // Move time forward
    }
}

// Function to calculate waiting time for Non-Preemptive Priority Scheduling
void calculateWaitingTimePriority(Process processes[], int n) {
    int completed = 0, currentTime = 0;
    while (completed < n) {
        int minIndex = -1, minPriority = 9999;

        // Find the process with highest priority that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime && processes[i].waiting == -1) {
                if (processes[i].priority < minPriority) {
                    minPriority = processes[i].priority; // Update minimum priority
                    minIndex = i; // Update index of the process
                }
            }
        }

        // If a process is found
        if (minIndex != -1) {
            processes[minIndex].waiting = currentTime - processes[minIndex].arrival; // Update waiting time
            currentTime += processes[minIndex].burst; // Move current time forward
            completed++; // Increment completed processes
            processes[minIndex].turnaround = processes[minIndex].waiting + processes[minIndex].burst; // Update turnaround time
        } else {
            currentTime++; // If no process is ready, increment time
        }
    }
}

// Function to calculate turnaround time
void calculateTurnaroundTime(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround = processes[i].waiting + processes[i].burst; // Calculate turnaround time
    }
}

// Function to print process details
void printProcessDetails(Process processes[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tPriority\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].id,
               processes[i].arrival,
               processes[i].burst,
               processes[i].waiting,
               processes[i].turnaround,
               processes[i].priority);
    }
}

int main() {
    int n, choice;
    Process* processes;

    while (1) {
        printf("\nScheduling Algorithms Menu:\n");
        printf("1. Non-Preemptive SJF\n");
        printf("2. Preemptive SJF\n");
        printf("3. Round Robin\n");
        printf("4. Non-Preemptive Priority Scheduling\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 5) {
            break; // Exit the loop
        }

        printf("Enter the number of processes: ");
        scanf("%d", &n);
        processes = (Process*)malloc(n * sizeof(Process)); // Allocate memory for processes

        // Get process details from the user
        for (int i = 0; i < n; i++) {
            processes[i].id = i + 1; // Set process ID
            printf("Enter arrival time and burst time for Process %d: ", i + 1);
            scanf("%d %d", &processes[i].arrival, &processes[i].burst);
            processes[i].waiting = -1; // Initialize waiting time
            if (choice == 4) {
                printf("Enter priority for Process %d: ", i + 1);
                scanf("%d", &processes[i].priority); // Get priority for priority scheduling
            }
        }

        // Call appropriate scheduling function based on choice
        switch (choice) {
            case 1:
                calculateWaitingTimeSJF(processes, n);
                break;
            case 2:
                calculateWaitingTimePreemptiveSJF(processes, n);
                break;
            case 3:
                {
                    int quantum;
                    printf("Enter time quantum for Round Robin: ");
                    scanf("%d", &quantum);
                    calculateWaitingTimeRR(processes, n, quantum);
                }
                break;
            case 4:
                calculateWaitingTimePriority(processes, n);
                break;
            default:
                printf("Invalid choice!\n");
                free(processes);
                continue;
        }

        calculateTurnaroundTime(processes, n); // Calculate turnaround times
        printProcessDetails(processes, n); // Print process details
        free(processes); // Free allocated memory
    }

    return 0; // Return success
}


