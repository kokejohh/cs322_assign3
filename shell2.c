#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

enum {MAXLINE = 256, MAXARGS = 48};

void sig_int(int n)
{
	printf("interrupted\n");
}

int main()
{
	char	buf[MAXLINE];
	pid_t	pid;
	int	status;
	char	*token;
	char	*args[MAXARGS];

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
			int i = 0;
			token = strtok(buf, " ");
			while (token != NULL)
			{
				args[i] = token;
				token = strtok(NULL, " ");
				i++;
			}
			args[i] = NULL;
			execvp(args[0], args);
			printf("couldn't execute: %s\n", buf);
			exit(1);
		}
		if ((pid = waitpid(pid, &status, 0)) < 0)
			printf("waitpid error\n");
		printf("%% ");
	}
	exit(0);
}
