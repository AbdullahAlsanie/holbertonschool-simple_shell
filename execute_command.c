#include "shell.h"

/**
 * parse_arguments - Splits a line into arguments
 * @line: Input line
 * @argv: Argument vector to populate
 *
 * Return: argument count
 */
int parse_arguments(char *line, char **argv)
{
	int i = 0;
	char *token;

	token = strtok(line, " \t\n");
	while (token != NULL && i < 63)
	{
		argv[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	argv[i] = NULL;
	return (i);
}

/**
 * handle_builtins - handles built-in commands (exit/env)
 * @argv: arguments
 *
 * Return: -1 if not builtin, otherwise 0
 */
int handle_builtins(char **argv)
{
	int j = 0;

	if (strcmp(argv[0], "exit") == 0)
		exit(0);

	if (strcmp(argv[0], "env") == 0)
	{
		while (environ[j])
		{
			write(STDOUT_FILENO, environ[j], strlen(environ[j]));
			write(STDOUT_FILENO, "\n", 1);
			j++;
		}
		return (0);
	}

	return (-1);
}

/**
 * run_external - runs an external command
 * @argv: argument list
 * @full_path: resolved path
 *
 * Return: status code
 */
int run_external(char **argv, char *full_path)
{
	pid_t pid;
	int status;

	if (access(full_path, X_OK) != 0)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
		if (full_path != argv[0])
			free(full_path);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		if (full_path != argv[0])
			free(full_path);
		return (1);
	}

	if (pid == 0)
	{
		if (execve(full_path, argv, environ) == -1)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
			exit(127);
		}
	}
	else
	{
		wait(&status);
		if (full_path != argv[0])
			free(full_path);

		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (1);
	}

	return (0);
}

/**
 * execute_command - Parses and executes a command line
 * @line: The input line to parse and execute
 *
 * Return: Status code
 */
int execute_command(char *line)
{
	char *argv[64];
	char *full_path;
	int status;

	if (parse_arguments(line, argv) == 0)
		return (0);

	if (handle_builtins(argv) == 0)
		return (0);

	if (strchr(argv[0], '/'))
		full_path = argv[0];
	else
	{
		full_path = find_in_path(argv[0]);
		if (!full_path)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
			return (127);
		}
	}

	status = run_external(argv, full_path);
	return (status);
}

