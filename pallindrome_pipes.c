#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#include<sys/wait.h>

void toLower(char *str) {
    int len = strlen(str);
    for(int i = 0; i < len; i++) {
        str[i] = tolower(str[i]);
    }
}

int checkPalindrome(char *str) {
    int len = strlen(str);
    for(int i = 0; i < len / 2; i++) {
        if(str[i] != str[len - i - 1]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int size_pipe[2], size_pipe_2[2], arr_pipe[2], arr_pipe_2[2];
    pipe(size_pipe);
    pipe(size_pipe_2);
    pipe(arr_pipe);
    pipe(arr_pipe_2);    
    
    int pid = fork();
    
    if(pid == 0) { // Child process
        close(size_pipe[1]);
        close(size_pipe_2[0]);    
        close(arr_pipe[1]);
        close(arr_pipe_2[0]);
        
        char name[10][20];
        int count = 0;
        read(size_pipe[0], &count, sizeof(count));
        read(arr_pipe[0], &name, sizeof(name));
        
        char palindromes[10][20];
        int pal_count = 0;
        for(int i = 0; i < count; i++) {
            toLower(name[i]);
            if(checkPalindrome(name[i])) {
                strcpy(palindromes[pal_count], name[i]);
                pal_count++;
            }
        }
        write(size_pipe_2[1], &pal_count, sizeof(pal_count));
        write(arr_pipe_2[1], &palindromes, sizeof(palindromes));
    } else { // Parent process
        close(size_pipe[0]);
        close(size_pipe_2[1]);    
        close(arr_pipe[0]);
        close(arr_pipe_2[1]);
        
        int count = 0;
        printf("Enter no of names:\n");
        scanf("%d", &count);
        
        write(size_pipe[1], &count, sizeof(count));
        printf("Enter names:\n");
        char name[10][20];
        for(int i = 0; i < count; i++) {
            scanf("%s", name[i]);
        }
        write(arr_pipe[1], &name, sizeof(name));
        
        int pal_count;
        read(size_pipe_2[0], &pal_count, sizeof(pal_count));
        printf("The no of palindromes in the sequence is: %d\n", pal_count);

        char palindromes[10][20];
        read(arr_pipe_2[0], &palindromes, sizeof(palindromes));
        printf("The palindromes are:\n");
        for(int i = 0; i < pal_count; i++) {
            printf("%s\n", palindromes[i]);
        }

        wait(NULL);
    }
    
    return 0;
}
