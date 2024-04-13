#include<stdio.h>          // Including standard input-output header file
#include<unistd.h>         // Including header file for POSIX operating system API
#include<string.h>         // Including header file for string manipulation functions
#include<ctype.h>          // Including header file for character handling functions
#include<sys/wait.h>       // Including header file for wait functions for processes

// Function to convert string to lowercase
void toLower(char *str) {
    int len = strlen(str);              // Calculate length of the string
    for(int i = 0; i < len; i++) {      // Loop through each character of the string
        str[i] = tolower(str[i]);       // Convert character to lowercase
    }
}

// Function to check if a string is palindrome
int checkPalindrome(char *str) {
    int len = strlen(str);                  // Calculate length of the string
    for(int i = 0; i < len / 2; i++) {      // Loop through half of the string
        if(str[i] != str[len - i - 1]) {    // Check characters at symmetric positions
            return 0;                       // If not equal, return 0 (not a palindrome)
        }
    }
    return 1;                               // If loop completes, return 1 (palindrome)
}

// Main function
int main() 
{
    int size_pipe[2], size_pipe_2[2], arr_pipe[2], arr_pipe_2[2];  // Declaration of pipe file descriptors
    
    pipe(size_pipe);        // Create pipe for communication between parent and child processes
    pipe(size_pipe_2);      // Create another pipe for communication
    pipe(arr_pipe);         // Create pipe for communication
    pipe(arr_pipe_2);       // Create another pipe for communication
    
    int pid = fork();       // Create a child process
    
    if(pid == 0) 
        {          // Child process
        close(size_pipe[1]);        // Close write end of pipe 1
        close(size_pipe_2[0]);      // Close read end of pipe 2
        close(arr_pipe[1]);         // Close write end of pipe 3
        close(arr_pipe_2[0]);       // Close read end of pipe 4
        
        char name[10][20];          // Declare array to store names
        int count = 0;              // Initialize count variable
        
        read(size_pipe[0], &count, sizeof(count));  // Read count of names from pipe
        read(arr_pipe[0], &name, sizeof(name));     // Read names from pipe
        
        char palindromes[10][20];   // Declare array to store palindromes
        int pal_count = 0;          // Initialize palindrome count
        
        for(int i = 0; i < count; i++) 
            {   // Loop through each name
            toLower(name[i]);                               // Convert name to lowercase
            if(checkPalindrome(name[i]))                    // Check if name is palindrome
                {
                strcpy(palindromes[pal_count], name[i]);    // Copy palindrome to array
                pal_count++;                                // Increment palindrome count
                }
            }
        
        write(size_pipe_2[1], &pal_count, sizeof(pal_count));       // Write palindrome count to pipe
        write(arr_pipe_2[1], &palindromes, sizeof(palindromes));    // Write palindromes to pipe
        } 
    else 
        { // Parent process
        close(size_pipe[0]);        // Close read end of pipe 1
        close(size_pipe_2[1]);      // Close write end of pipe 2
        close(arr_pipe[0]);         // Close read end of pipe 3
        close(arr_pipe_2[1]);       // Close write end of pipe 4
        
        int count = 0;                                                  // Declare variable to store count of names
        printf("Enter no of names:\n");                                 // Prompt user to enter count of names
        scanf("%d", &count);                                            // Read count of names from user
        
        write(size_pipe[1], &count, sizeof(count));                     // Write count of names to pipe
        printf("Enter names:\n");                                       // Prompt user to enter names
        
        char name[10][20];                                              // Declare array to store names
        for(int i = 0; i < count; i++)                                  // Loop through each name
            {scanf("%s", name[i]);}                                     // Read name from user
        
        write(arr_pipe[1], &name, sizeof(name));                        // Write names to pipe
        
        int pal_count;                                                  // Declare variable to store palindrome count
        read(size_pipe_2[0], &pal_count, sizeof(pal_count));            // Read palindrome count from pipe
        printf("The no of palindromes in the sequence is: %d\n", pal_count);  // Print palindrome count
        
        char palindromes[10][20];                                       // Declare array to store palindromes
        read(arr_pipe_2[0], &palindromes, sizeof(palindromes));         // Read palindromes from pipe
        printf("The palindromes are:\n");                               // Print header for palindromes
        for(int i = 0; i < pal_count; i++) 
            {                                                           // Loop through each palindrome
            printf("%s\n", palindromes[i]);                             // Print palindrome
            }

        wait(NULL);                                                     // Wait for child process to finish
    }
    
    return 0;                                                           // Return 0 to indicate successful termination of the program
}
