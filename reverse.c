//NOTE : when invoking this program, the arguements are given in the command line, along with the invocation.
//Example: ./a.out source.txt dest.txt


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* args[])
{
char buff;
int source, dest;

source=open(args[1],O_RDONLY);
dest=open(args[2],O_WRONLY|O_CREAT);
if (source<0)
	{printf("source filecannot be opened");
	exit(0);
	}
if (dest<0)
	{printf("destination filecannot be opened");
	exit(0);
	}
	
int filesize=lseek(source,(off_t) 0,SEEK_END);
for (int i=filesize-1;i>0;i--)
	{
	lseek(source,(off_t) i,SEEK_SET);
	read(source,&buff,1);
	write(dest,&buff,1);
	}
	
printf("The file has been reversed successfully");
close(source);
close(dest);

return 0;
}