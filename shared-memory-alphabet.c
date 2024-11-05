#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main() {
    // Create shared memory
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666|IPC_CREAT);
    char *shared_memory = shmat(shmid, NULL, 0);

    // Fork process
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        exit(1);
    }

    // Parent process
    else if (pid > 0) {
        char alphabet = 'F';

        // Write to shared memory
        shared_memory[0] = alphabet;
        printf("Parent sent: %c\n", alphabet);

        // Wait for child to respond
        wait(NULL);

        // Read child's response
        printf("Parent received from child: %c\n", shared_memory[0]);

        // Detach and remove shared memory
        shmdt(shared_memory);
        shmctl(shmid, IPC_RMID, NULL);
    }

    // Child process
    else {
        // Read from shared memory
        char received = shared_memory[0];

        // Send next alphabet
        shared_memory[0] = received + 1;
        printf("Child received: %c, sending: %c\n", received, received + 1);

        // Detach shared memory
        shmdt(shared_memory);
        exit(0);
    }

    return 0;
}
