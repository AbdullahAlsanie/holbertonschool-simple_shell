#include "shell.h"

/**
 * execute_command - Parses and executes a command line
 * @line: The input line to parse and execute
 * Return: Status code
 */

int execute_command(char *line)
{
    pid_t pid;
    int status, i = 0, j = 0;
    char *argv[64], *token, *full_path;

    token = strtok(line, " \t\n");
    if (token == NULL)
        return (0);
    while (token != NULL && i < 63)
    {
        argv[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    argv[i] = NULL;

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
            return WEXITSTATUS(status);
        else
            return (1);
    }

    return (0);
}

