#include "shell.h"

/**
 * read_line - reads a line from stdin
 * Return: pointer to input line
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t nread;

	nread = getline(&line, &bufsize, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/**
 * split_line - splits a line into tokens
 * @line: input string
 * Return: array of tokens
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
 * free_args - frees tokens array
 * @args: token array
 */
void free_args(char **args)
{
	int i = 0;

	while (args[i])
		free(args[i++]);
	free(args);
}

/**
 * print_env - prints environment
 */
void print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}



/**
 * execute - forks and executes a command
 * @args: array of arguments (NULL-terminated)
 * @argv: argv[0] from main, shell executable path
 * @cmd_count: command count (line number)
 * Return: 1 to continue shell, or exits on 'exit'
 */
/**
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
}*/
