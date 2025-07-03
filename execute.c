#include "shell.h"

/**
 * execute - runs a command
 * @args: argument array
 * @argv: argv[0]
 * @cmd_count: line count
 * Return: 1 to continue, 0 to exit
 */
int execute(char **args, char *argv, int cmd_count)
{
	pid_t pid;
	int status;
	char *cmd;

	if (!args[0])
		return (1);

	if (strcmp(args[0], "exit") == 0)
		exit(0);

	if (strcmp(args[0], "env") == 0)
	{
		print_env();
		return (1);
	}

	cmd = find_path(args[0]);
	if (!cmd)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", argv, cmd_count, args[0]);
		if (!isatty(STDIN_FILENO))
			exit(127);
		return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		execve(cmd, args, environ);
		perror("execve");
		free(cmd); /* فقط لو فشل execve */
		exit(127);
	}
	else if (pid < 0)
	{
		perror("fork");
		free(cmd);
		return (1);
	}
	else
	{
		waitpid(pid, &status, 0);
		free(cmd); /* parent always frees */
	}

	return (1);
}

