#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	pid_t	pid;
	pid_t	mypid;
	int	status;

	if ((pid = fork()) < 0)
	{
		printf("fork error");
		exit(1);
	}
	else if (pid == 0)
	{
		mypid = getpid();
		printf("child pid = %d\n", mypid);	
	}
	else
	{
		mypid = getpid();
		printf("parent pid = %d\n", mypid);
		waitpid(pid, &status, 0);
	}
	exit(0);
}
