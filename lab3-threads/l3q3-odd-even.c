#include <stdio.h>
#include <pthread.h>

#define SIZE 10  // Size of the array

// Global variables
int numbers[SIZE];      // Input array
int sum_even = 0;       // Sum of even numbers
int sum_odd = 0;        // Sum of odd numbers

// Function to sum even numbers
void* sum_even_numbers(void* arg) {
    for (int i = 0; i < SIZE; i++) {
        if (numbers[i] % 2 == 0) {
            sum_even += numbers[i];
        }
    }
    pthread_exit(0);
}

// Function to sum odd numbers
void* sum_odd_numbers(void* arg) {
    for (int i = 0; i < SIZE; i++) {
        if (numbers[i] % 2 != 0) {
            sum_odd += numbers[i];
        }
    }
    pthread_exit(0);
}

int main() {
    pthread_t tid_even, tid_odd;  // Thread IDs

    // Input: populate the array
    printf("Enter %d numbers:\n", SIZE);
    for (int i = 0; i < SIZE; i++) {
        scanf("%d", &numbers[i]);
    }

    // Create threads to calculate sums
    pthread_create(&tid_even, NULL, sum_even_numbers, NULL);
    pthread_create(&tid_odd, NULL, sum_odd_numbers, NULL);

    // Wait for both threads to finish
    pthread_join(tid_even, NULL);
    pthread_join(tid_odd, NULL);

    // Output the results
    printf("Sum of even numbers: %d\n", sum_even);
    printf("Sum of odd numbers: %d\n", sum_odd);

    return 0;
}
