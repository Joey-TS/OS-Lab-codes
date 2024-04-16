//Create a c program that implements ipc using pipes to accept a string from user
//and validate it based on the following conditions:
//1. The string should contain only alphanumeric characters
//2. The string should be between 5 and 8 characters in length
//The child does the validation process and returns the status to the parent process

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>


int main()
{
int p_p2c[2],p_c2p[2];

pipe(p_p2c);                                      //create a pipe for parent to child communication
pipe(p_c2p);                                      //create a pipe for child to parent communication

int pid=fork();
if (pid>0)
	{//parent process
	close(p_p2c[0]);
	close(p_c2p[1]);
	
	char str[1][10];
	printf("Enter the string to validate : ");
	scanf("%s",str[0]);
	write(p_p2c[1],&str,sizeof(str));                           //write the string to the child process
	
	int status;
	read(p_c2p[0],&status,sizeof(status));                      //read the status from the child process    
	if (status==0)
		{printf("String is valid\n");}
	else if (status==1)
		{printf("String exceeds max character length");}
	else if (status==2)
		{printf("String below min character length");}
	else if (status==3)
		{printf("String contains non alpha-numeric values");}
	else
		{printf("Error");}
	
	wait(NULL);
	}
else
	{//child process
	close(p_p2c[1]);
	close(p_c2p[0]);
	
	int status=0;
	char str[1][10];
	read(p_p2c[0],&str,sizeof(str));
	int size=strlen(str[0]);
	bool alphanum;
	
	for(int i=0;i<size;i++)
		{alphanum=isalnum(str[0][i]);                   //check for alphanumeric characters
		if (!alphanum)
			{
			status=3;
			write(p_c2p[1],&status,sizeof(status));
			close(p_c2p[1]);                            //close the write end of the pipe (to prevent being overwritten)
			}
		}
	if (size<5)                                         //check for min character length
		{
		status=2;
		write(p_c2p[1],&status,sizeof(status));
		close(p_c2p[1]);                                //close the write end of the pipe (to prevent being overwritten)
		}
	else if (size>8)                                    //check for max character length
		{
		status=1;
		write(p_c2p[1],&status,sizeof(status));
		close(p_c2p[1]);                                //close the write end of the pipe (to prevent being overwritten)
		}
	}



return 0;
}