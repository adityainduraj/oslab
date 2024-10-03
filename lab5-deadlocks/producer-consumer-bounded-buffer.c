#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Size of the buffer

int buffer[BUFFER_SIZE];  // Bounded buffer
int in = 0;               // Index for the next produced item
int out = 0;              // Index for the next consumed item

sem_t empty;  // Semaphore to count empty slots
sem_t full;   // Semaphore to count full slots
pthread_mutex_t mutex; // Mutex for mutual exclusion

// Function for the producer thread
void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {  // Produce 10 items
        // Produce an item
        int item = rand() % 100;  // Random item
        sem_wait(&empty);          // Wait for an empty slot
        pthread_mutex_lock(&mutex); // Enter critical section

        // Add item to buffer
        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE; // Circular buffer

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&full);              // Signal that a new item is produced

        sleep(rand() % 2); // Simulate variable production time
    }
    pthread_exit(0);
}

// Function for the consumer thread
void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {  // Consume 10 items
        sem_wait(&full);             // Wait for a full slot
        pthread_mutex_lock(&mutex);  // Enter critical section

        // Remove item from buffer
        int item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE; // Circular buffer

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&empty);             // Signal that an item is consumed

        sleep(rand() % 2); // Simulate variable consumption time
    }
    pthread_exit(0);
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE); // All slots are empty initially
    sem_init(&full, 0, 0);            // No slots are full initially
    pthread_mutex_init(&mutex, NULL); // Initialize mutex

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Clean up
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
