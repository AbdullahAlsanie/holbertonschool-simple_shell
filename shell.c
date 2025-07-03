#include "shell.h"

/**
 * main - entry point of shell
 * @argc: argument count (unused)
 * @argv: argument vector
 * Return: exit status
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
        if (!line) /* EOF */
            break;

        args = split_line(line);

        if (!args[0]) /* empty line or spaces only */
        {
            free(line);
            free_args(args);
            continue;
        }

        cmd_count++;
        status = execute(args, argv[0], cmd_count);

        free(line);
        free_args(args);

        if (!isatty(STDIN_FILENO)) /* non-interactive mode */
            exit(status);
    }

    free(line);
    return (status);
}

/**
 * free_args - free the array of strings
 * @args: null-terminated string array
 */
void free_args(char **args)
{
    int i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}
