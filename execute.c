#include "shell.h"

/**
 * execute - executes a command using PATH
 * @args: array of command and arguments
 * @argv: program name (argv[0])
 * @cmd_count: command number (used in error messages)
 * Return: 1 to continue loop, 0 to exit shell
 */
int execute(char **args, char *argv, int cmd_count)
{
	pid_t pid;
	int status;
	char *cmd_path;

	if (args[0] == NULL)
		return (1);

	if (strcmp(args[0], "exit") == 0)
		return (0);

	if (strcmp(args[0], "env") == 0)
	{
		print_env();
		return (1);
	}

	cmd_path = find_path(args[0]);
	if (!cmd_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", argv, cmd_count, args[0]);
		return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, args, environ) == -1)
		{
			perror("execve");
			free(cmd_path);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		waitpid(pid, &status, 0);
	}

	free(cmd_path);
	return (1);
}

