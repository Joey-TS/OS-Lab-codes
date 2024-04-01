#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_NUMBERS 100

int main() {
    int pipefd[2]; // File descriptors for the pipe
    pid_t pid; // Process ID
    int numbers[MAX_NUMBERS];
    int n, i;

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { // Parent process
        close(pipefd[0]); // Close reading end of pipe in parent

        // Prompt the user for the number of numbers
        printf("Enter the number of numbers: ");
        scanf("%d", &n);

        // Prompt the user for the numbers
        printf("Enter %d numbers:\n", n);
        for (i = 0; i < n; i++) {
            scanf("%d", &numbers[i]);
        }

        // Write the numbers to the pipe
        write(pipefd[1], numbers, sizeof(int) * n);

        close(pipefd[1]); // Close writing end of pipe in parent
    } else { // Child process
        close(pipefd[1]); // Close writing end of pipe in child

        // Read numbers from the pipe
        printf("Child process: Numbers received from parent:\n");
        while (read(pipefd[0], &n, sizeof(int)) > 0) {
            printf("%d\n", n);
        }

        close(pipefd[0]); // Close reading end of pipe in child
        printf("Child process: All numbers received.\n");
    }

    return 0;
}
