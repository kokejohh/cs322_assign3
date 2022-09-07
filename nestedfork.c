#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("wrong argument\n");
		exit(1);
	}
	int	n = atoi(argv[1]);
	pid_t	pid;
	pid_t	mypid;
	int	status;

	for (int i = 0; i < n; i++)
	{
		if ((pid = fork()) < 0)
		{	
			printf("fork error\n");
			exit(1);
		}
		else if (pid == 0)
		{
			mypid = getpid();
			printf("child pid : %d\n", mypid);
		}
		else
		{
			waitpid(pid, &status, 0);
			printf("waitpid pid : %d\n", pid);
			exit(0);
		}
	}
	exit(0);
}
