#include "shell.h"

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
		if (isatty(STDIN_FILENO))
			printf("($) ");

		nread = getline(&buffer, &size, stdin);



		/* EOF (Ctrl+D) */
		if (nread == -1)
		{
			break;
		}

		/* remove the new line */
		if (buffer[nread - 1] == '\n')
			buffer[nread - 1] = '\0';

	       	/* removing white spaces */
	       	rm_spaces(buffer);

		i++;

		/*if the user want to Exit*/
		if(strcmp(buffer, "exit") == 0)
				break;
		
		/*To check the file if it excuetable*/
		if (access(buffer, X_OK) == -1){
			fprintf(stderr, "hsh: %d: %s: not found\n", i,  buffer);
			continue;
		}

		pid = fork();
		if(pid == -1)
		{
			perror("fork");
				continue;
		}

		if(pid == 0)
		{
			char *argv[2];
			argv[0] = buffer;
			argv[1] = NULL;
			execve(buffer, argv, environ);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
			wait(NULL);
	}
	free(buffer);
	return(0);
}
