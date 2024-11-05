#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>

// Message structure
struct msg_buffer {
    long msg_type;
    int number;
} message;

// Function to check palindrome
int isPalindrome(int num) {
    int rev = 0, temp = num;
    while (temp > 0) {
        rev = rev * 10 + temp % 10;
        temp /= 10;
    }
    return (num == rev);
}

int main() {
    key_t key = ftok("msgq", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    // Fork to create two processes
    int pid = fork();

    if (pid > 0) {  // Parent Process (Process A)
        message.msg_type = 1;
        printf("Process A - Enter number: ");
        scanf("%d", &message.number);

        // Send message
        msgsnd(msgid, &message, sizeof(message), 0);
        printf("Process A sent: %d\n", message.number);

    } else if (pid == 0) {  // Child Process (Process B)
        // Receive message
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        printf("Process B received: %d\n", message.number);

        // Check palindrome
        if(isPalindrome(message.number))
            printf("Number is palindrome\n");
        else
            printf("Number is not palindrome\n");

        // Delete message queue
        msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}
