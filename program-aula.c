#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	//fork another process
	pid_t pid;
	pid = fork();
	wait(NULL);

	if(pid < 0)
	{
		//error occurred
		fprintf(stderr, "Fork failed");
		return 1;
	}
	else if(pid == 0)
	{
		//child process
		printf("I am the child %d\n", pid);
		execlp("/bin/ls", "ls", NULL);
		printf("Ola\n");
	}
	else
	{
		//parent process
		//parent will wait for the child
		//wait(NULL);
		printf("I am the parent %d\n", pid);
		printf("Child Complete\n");
	}
	return 0;
}
