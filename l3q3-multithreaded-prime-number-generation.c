#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Structure to hold the range for each thread
typedef struct {
    int start;  // Starting number
    int end;    // Ending number
} Range;

// Function to check if a number is prime
int isPrime(int num) {
    if (num <= 1) return 0;  // 0 and 1 are not prime
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;  // Not prime if divisible
    }
    return 1;  // It is prime
}

// Thread function to find and print prime numbers in a given range
void* findPrimes(void* arg) {
    Range* range = (Range*)arg;  // Cast argument to Range type
    printf("Prime numbers between %d and %d:\n", range->start, range->end);
    for (int i = range->start; i <= range->end; i++) {
        if (isPrime(i)) {
            printf("%d ", i);  // Print the prime number
        }
    }
    printf("\n");  // New line after listing primes
    return NULL;  // Return from thread
}

int main() {
    int start, end;  // Variables to hold the range input

    // Prompt user for input
    printf("Enter the starting number: ");
    scanf("%d", &start);  // Read starting number
    printf("Enter the ending number: ");
    scanf("%d", &end);  // Read ending number

    // Validate input
    if (start < 0 || end < 0 || start > end) {
        printf("Invalid range! Please enter non-negative numbers where starting number <= ending number.\n");
        return 1;  // Exit with error
    }

    // Create a Range structure for the thread
    Range range = {start, end};  

    pthread_t thread;  // Thread identifier

    // Create a thread to find prime numbers in the specified range
    if (pthread_create(&thread, NULL, findPrimes, (void*)&range) != 0) {
        printf("Error creating thread!\n");
        return 1;  // Exit with error
    }

    // Wait for the thread to complete
    pthread_join(thread, NULL);

    return 0;  // Return success
}

