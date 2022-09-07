#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAXLINE 1000

void sig_int(int n)
{
	printf("interrupted\n");
}

int main()
{
	char	buf[MAXLINE];
	pid_t	pid;
	int	status;

	if (signal(SIGINT, sig_int) == SIG_ERR)
		printf("signal error\n");
	printf("%% ");
	while (fgets(buf, MAXLINE, stdin) != NULL)
	{
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0;
		if (strcmp(buf, "myexit") == 0)
			exit(0);
		if ((pid = fork()) < 0)
		{
			printf("fork error\n");
		}
		else if (pid == 0)
		{
			execlp(buf, buf, NULL);
			printf("couldn't execute: %s\n", buf);
			exit(1);
		}
		if ((pid = waitpid(pid, &status, 0)) < 0)
			printf("waitpid error\n");
		printf("%% ");
	}
	exit(0);
}
