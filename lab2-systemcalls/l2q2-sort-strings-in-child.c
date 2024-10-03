#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // we check if there are enough arguments for the code to run 
  if (argc < 2) {
    printf("Please provide 3 or more arguments\n");
    return 1;
  }

  // we create the child process
  pid_t pid = fork(); 

  // if there is an error in the fork
  if (pid < 0) {
    perror("fork failed");
    return 1;
  }

  // code for the child process 
  if (pid == 0) {
    printf("Child Process -> Sorted Strings:\n");

    // sorting logic
    for (int i = 1; i < argc - 1; i++) {
      for (int j = i + 1; j < argc; j++) {
        if (strcmp(argv[i], argv[j]) > 0) {
          // swap the strings 
          char *temp = argv[i];
          argv[i] = argv[j];
          argv[j] = temp;
        }
      }
    }

    // still in the child process, now we print the strings that the child process sorted 
    for (int i = 1; i < argc; i++) {  
      printf("%s\n", argv[i]);
    }
    // now we end the child process 
    exit(0);
  } else {
    // code for the parent process goes here
    wait(NULL); // wait until the child process has ended 
    printf("Parent Process: Unsorted Strings\n");
    for (int i = 1; i < argc; i++) {
      printf("%s\n", argv[i]);
    }
  }

  return 0;
}
