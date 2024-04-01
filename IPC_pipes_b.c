
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> // Include the header file for wait()

#define MAX_NUMBERS 100

int main() {
    int pipefd[2]; // File descriptors for the pipe to send numbers from parent to child
    int pipefd_result[2]; // File descriptors for the pipe to send result from child to parent
    pid_t pid; // Process ID
    int numbers[MAX_NUMBERS];
    int n, i;
    int sum = 0; // Variable to store the sum of numbers

    // Create the pipe to send numbers from parent to child
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create the pipe to send result from child to parent
    if (pipe(pipefd_result) == -1) {
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
        close(pipefd[0]); // Close reading end of pipe in parent for sending numbers
        close(pipefd_result[1]); // Close writing end of pipe in parent for receiving result

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

        // Wait for child process to finish
        wait(NULL);

        // Read the sum sent by child process
        read(pipefd_result[0], &sum, sizeof(int));

        printf("Parent process: Sum of numbers received from child: %d\n", sum);

        close(pipefd_result[0]); // Close reading end of pipe in parent for receiving result
    } else { // Child process
        close(pipefd[1]); // Close writing end of pipe in child for receiving numbers
        close(pipefd_result[0]); // Close reading end of pipe in child for sending result

        // Read numbers from the pipe and calculate sum
        while (read(pipefd[0], &n, sizeof(int)) > 0) {
            sum += n;
        }

        close(pipefd[0]); // Close reading end of pipe in child

        // Write the sum to the pipe
        write(pipefd_result[1], &sum, sizeof(int));

        close(pipefd_result[1]); // Close writing end of pipe in child for sending result
    }

    return 0;
}
