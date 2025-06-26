#include "shell.h"
#define UNUSED(x) (void)(x)

/*
 * main - the main shell program
 *
 * Return: Void
 */
int main(void)
{
	char *buffer = NULL;
	size_t size = 0;
	ssize_t nread;
	pid_t pid;
	int i = 0;

	while (1)
	{
		printf(";)$ ");
		nread = getline(&buffer, &size, stdin);
		i++;

		/* EOF (Ctrl+D) */
		if (nread == -1)
			break;
		/* remove the new line */
		if (buffer[nread - 1] == '\n')
			buffer[nread - 1] = '\0';

		if (access(buffer, X_OK) == -1)
			printf("hsh: %d: %s: not found\n", i,  buffer);
		else
		{
		pid = fork();

		if(pid == 0)
		{
			char *argv[2];
			argv[0] = buffer;
			argv[1] = NULL;
			execve(buffer, argv, environ);
			perror("execve");
			exit(1);
		}
		else
			wait(NULL);
		}
	}
	free(buffer);
	return(0);
}
