#include <stdio.h>
#include <pthread.h>

#define MAX 100  // Maximum size of the Fibonacci sequence

int fib_series[MAX];  // Array to store the Fibonacci sequence
int num_fib;          // Number of Fibonacci numbers to generate

// Function to generate the Fibonacci sequence
void* generate_fibonacci(void* arg) {
    fib_series[0] = 0;
    if (num_fib > 1) {
        fib_series[1] = 1;
    }
    for (int i = 2; i < num_fib; i++) {
        fib_series[i] = fib_series[i - 1] + fib_series[i - 2];
    }
    pthread_exit(0);
}

int main() {
    pthread_t tid;  // Thread ID

    // Input: number of Fibonacci numbers to generate
    printf("Enter the number of Fibonacci numbers: ");
    scanf("%d", &num_fib);

    // Create a thread to generate the Fibonacci sequence
    pthread_create(&tid, NULL, generate_fibonacci, NULL);

    // Wait for the thread to finish
    pthread_join(tid, NULL);

    // Output the Fibonacci sequence
    printf("Fibonacci sequence: ");
    for (int i = 0; i < num_fib; i++) {
        printf("%d ", fib_series[i]);
    }
    printf("\n");

    return 0;
}
