#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	//fork another process
	pid_t pid;
	pid = fork();
	if(pid < 0)
	{
		//error occurred
		fprintf(stderr, "Fork failed");
		return 1;
	}
	else if(pid == 0)
	{
		//child process
		execlp("/bin/ls", "ls", NULL);
	}
	else
	{
		//parent process
		//parent will wait for the chi
		printf("Child Complete\n");
	}
	return 0;
}
