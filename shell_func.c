#include "shell.h"

/**
 * read_line - reads a line of input from stdin
 * Return: pointer to the line read
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/**
 * split_line - splits a line into tokens
 * @line: string to tokenize
 * Return: array of strings
 */
char **split_line(char *line)
{
	int bufsize = 64, i = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
		exit(EXIT_FAILURE);

	token = strtok(line, " \t\r\n");
	while (token)
	{
		tokens[i++] = strdup(token);
		if (i >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
				exit(EXIT_FAILURE);
		}
		token = strtok(NULL, " \t\r\n");
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * execute - forks and executes a command
 * @args: array of arguments (NULL-terminated)
 * @argv: argv[0] from main, shell executable path
 * @cmd_count: command count (line number)
 * Return: 1 to continue shell, or exits on 'exit'
 */
int execute(char **args, char *argv, int cmd_count)
{
	pid_t pid;
	int status;

	if (strcmp(args[0], "exit") == 0)
		exit(0);

	pid = fork();
	if (pid == 0)
	{
		char *cmd = args[0];

		if (!cmd)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", argv, cmd_count, args[0]);
			exit(127);
		}
		execve(cmd, args, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		waitpid(pid, &status, 0);
	}

	return (1);
}
