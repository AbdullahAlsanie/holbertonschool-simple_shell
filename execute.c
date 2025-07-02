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
	char *cmd;

	if (args[0] == NULL)
		return (1);

	/* Handle built-in exit */
	if (strcmp(args[0], "exit") == 0)
		exit(0);

	/* Handle built-in env */
	if (strcmp(args[0], "env") == 0)
	{
		print_env();
		return (1);
	}

	/* Find full path */
	cmd = find_path(args[0]);
	if (!cmd)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", argv, cmd_count, args[0]);
		/*Exit with 127 only in non-interactive mode */
		if (!isatty(STDIN_FILENO))
			exit(127);
		return (1); /* Keep shell running in interactive mode */
	}

	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		execve(cmd, args, environ);
		perror("execve");
		free(cmd);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		/* Fork failed */
		perror("fork");
		free(cmd);
		return (1);
	}
	else
	{
		/* Parent process */
		waitpid(pid, &status, 0);
		free(cmd);
	}

	return (1);
}

