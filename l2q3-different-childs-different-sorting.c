#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// Function to sort strings using Bubble Sort
void bubbleSort(char *arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Compare adjacent strings and swap if needed
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                // Swap the strings
                char *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to sort strings using Selection Sort
void selectionSort(char *arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;  // Assume the first element is the smallest
        for (int j = i + 1; j < n; j++) {
            // Find the index of the smallest string
            if (strcmp(arr[j], arr[minIndex]) < 0) {
                minIndex = j;  // Update minIndex
            }
        }
        // Swap the found minimum string with the first element
        char *temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

int main() {
    int N;  // Number of strings
    printf("Enter the number of strings: ");
    scanf("%d", &N);  // Read the number of strings

    // Allocate memory for the strings
    char **strings = malloc(N * sizeof(char *));
    printf("Enter %d strings:\n", N);
    for (int i = 0; i < N; i++) {
        strings[i] = malloc(100 * sizeof(char));  // Allocate space for each string
        scanf("%s", strings[i]);  // Read each string
    }

    pid_t pid1 = fork();  // Create the first child process

    if (pid1 == 0) {  // Child process for Bubble Sort
        bubbleSort(strings, N);  // Sort using Bubble Sort
        printf("Bubble Sort Result:\n");
        for (int i = 0; i < N; i++) {
            printf("%s\n", strings[i]);  // Print sorted strings
        }
        exit(0);  // Exit child process
    } else {  // Parent process
        pid_t pid2 = fork();  // Create the second child process

        if (pid2 == 0) {  // Child process for Selection Sort
            selectionSort(strings, N);  // Sort using Selection Sort
            printf("Selection Sort Result:\n");
            for (int i = 0; i < N; i++) {
                printf("%s\n", strings[i]);  // Print sorted strings
            }
            exit(0);  // Exit child process
        } else {  // Back to parent process
            wait(NULL);  // Wait for one child process to finish
            printf("Parent process: One child has completed sorting.\n");
        }
    }

    // Free allocated memory for strings
    for (int i = 0; i < N; i++) {
        free(strings[i]);  // Free each string
    }
    free(strings);  // Free the array of string pointers

    return 0;  // Return success
}

