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
	pid_t	pid[n];
	pid_t	mypid[n];
	int	status;
	for (int i = 0; i < n; i++)
	{
		if ((pid[i] = fork()) < 0)
		{
			printf("fork error\n");
			exit(1);
		}	
		else if (pid[i] == 0)
		{
			mypid[i] = getpid();
			printf("child pid = %d\n", mypid[i]);	
			exit(0);
		}
	}
	for (int i = 0; i < n; i++)
	{
		waitpid(pid[i], &status, 0);			
		printf("waitpid pid = %d\n", pid[i]);
	}
	exit(0);
}
