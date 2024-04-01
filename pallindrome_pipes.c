#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 100

// Function to check if a string is a palindrome
int isPalindrome(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1])
            return 0;
    }
    return 1;
}

int main() {
    int pipefd[2]; // File descriptors for the pipe
    pid_t pid;
    char buffer[BUFFER_SIZE];

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { // Parent process
        close(pipefd[0]); // Close the reading end of the pipe

        int n;
        printf("Enter the number of strings: ");
        scanf("%d", &n);

        printf("Enter %d strings:\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%s", buffer);
            write(pipefd[1], buffer, strlen(buffer) + 1); // Write to the pipe
        }

        close(pipefd[1]); // Close the writing end of the pipe

        printf("\nPalindromes received from child process:\n");
        while (read(pipefd[0], buffer, BUFFER_SIZE) > 0) { // Read from the pipe
            printf("%s\n", buffer);
        }

        close(pipefd[0]); // Close the reading end of the pipe
    } else { // Child process
        close(pipefd[1]); // Close the writing end of the pipe
        while (read(pipefd[0], buffer, BUFFER_SIZE) > 0) { // Read from the pipe
            if (isPalindrome(buffer)) {
                printf("Palindrome found: %s\n", buffer);
                write(pipefd[1], buffer, strlen(buffer) + 1); // Write palindromes back to the pipe
            }
        }

        close(pipefd[0]); // Close the reading end of the pipe
        exit(EXIT_SUCCESS);
    }

    return 0;
}