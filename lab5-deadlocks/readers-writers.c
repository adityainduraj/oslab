#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t read_mutex;  // Semaphore for controlling access to the readers count
sem_t write_mutex; // Semaphore for controlling access to the writing process

int readers = 0;   // Number of readers currently reading
int shared_resource = 0; // Shared resource

// Function for the reader thread
void* reader(void* arg) {
    int id = *(int*)arg; // Reader ID
    while (1) {
        // Start reading
        sem_wait(&read_mutex); // Enter critical section for reader count
        readers++;
        if (readers == 1) { // First reader locks the writer
            sem_wait(&write_mutex);
        }
        sem_post(&read_mutex); // Exit critical section for reader count

        // Reading the shared resource
        printf("Reader %d: Reading shared resource: %d\n", id, shared_resource);
        sleep(1); // Simulate reading time

        // Stop reading
        sem_wait(&read_mutex); // Enter critical section for reader count
        readers--;
        if (readers == 0) { // Last reader unlocks the writer
            sem_post(&write_mutex);
        }
        sem_post(&read_mutex); // Exit critical section for reader count

        sleep(rand() % 3); // Simulate time before reading again
    }
    pthread_exit(0);
}

// Function for the writer thread
void* writer(void* arg) {
    int id = *(int*)arg; // Writer ID
    while (1) {
        sem_wait(&write_mutex); // Wait for access to write

        // Writing to the shared resource
        shared_resource++;
        printf("Writer %d: Writing shared resource: %d\n", id, shared_resource);
        sleep(1); // Simulate writing time

        sem_post(&write_mutex); // Release access after writing

        sleep(rand() % 3); // Simulate time before writing again
    }
    pthread_exit(0);
}

int main() {
    pthread_t readers_thread[5], writer_thread[2]; // Thread IDs
    int reader_ids[5], writer_ids[2];

    // Initialize semaphores
    sem_init(&read_mutex, 0, 1); // Binary semaphore for reader count
    sem_init(&write_mutex, 0, 1); // Binary semaphore for writing access

    // Create reader threads
    for (int i = 0; i < 5; i++) {
        reader_ids[i] = i + 1; // Assign reader IDs
        pthread_create(&readers_thread[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++) {
        writer_ids[i] = i + 1; // Assign writer IDs
        pthread_create(&writer_thread[i], NULL, writer, &writer_ids[i]);
    }

    // Wait for threads to finish (they won't in this case)
    for (int i = 0; i < 5; i++) {
        pthread_join(readers_thread[i], NULL);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(writer_thread[i], NULL);
    }

    // Clean up
    sem_destroy(&read_mutex);
    sem_destroy(&write_mutex);

    return 0;
}
