#include "shell.h"

int main(int argc, char **argv)
{
	char *line = NULL;
	char **args = NULL;
	int status = 1;
	int cmd_count = 0;
	(void)argc;

	do {
		if (isatty(STDIN_FILENO))
			printf("($) ");
		line = read_line();
		if (!line)
			break;
		cmd_count++;
		args = split_line(line);
		if (args[0])
			status = execute(args, argv[0], cmd_count);
		free(line);
		free_args(args);
	} while (status);
	return (0);
}

/**
 * free_args - frees the memory
 * @args: the array to free
 * Return: nothing
 */
void free_args(char **args)
{
	int i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}
