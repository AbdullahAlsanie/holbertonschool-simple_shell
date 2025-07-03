#include "shell.h"

/**
 * main - Entry point for the shell
 * @argc: Argument count (unused)
 * @argv: Argument vector
 *
 * Return: 0 always
 */
int main(int argc, char **argv)
{
    char *line = NULL;
    char **args = NULL;
    int status = 0;
    int cmd_count = 0;
    (void)argc;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("($) ");

        line = read_line();
        if (!line)
            break;

        cmd_count++;
        args = split_line(line);

        status = execute(args, argv[0], cmd_count);

        free(line);
        free_args(args);

        /* If shell is not interactive, exit with command status */
        if (!isatty(STDIN_FILENO))
            exit(status);
    }

    free(line);
    return (status);
}

/**
 * free_args - Frees memory used by args array
 * @args: Null-terminated array of strings
 */
void free_args(char **args)
{
    int i = 0;
    while (args[i])
        free(args[i++]);
    free(args);
}

