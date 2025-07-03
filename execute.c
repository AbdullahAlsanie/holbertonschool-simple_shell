#include "shell.h"
/**
 * execute - executes a command using PATH
 * @args: array of command and arguments
 * @argv: program name (argv[0])
 * @cmd_count: command number (used in error messages)
 * Return: exit status of executed command or 127 if not found
 */
int execute(char **args, char *argv, int cmd_count)
{
    pid_t pid;
    int status;
    char *cmd;

    if (args[0] == NULL)
        return (0);

    if (strcmp(args[0], "exit") == 0)
        exit(0);

    if (strcmp(args[0], "env") == 0)
    {
        extern char **environ;
        int i = 0;
        while (environ[i])
            printf("%s\n", environ[i++]);
        return (0);
    }

    cmd = find_path(args[0]);
    if (!cmd)
    {
        fprintf(stderr, "%s: %d: %s: not found\n", argv, cmd_count, args[0]);
        if (!isatty(STDIN_FILENO))
            exit(127);
        return (127);
    }

    if (access(cmd, X_OK) != 0)
    {
        fprintf(stderr, "%s: %d: %s: not found\n", argv, cmd_count, args[0]);
        free(cmd);
        if (!isatty(STDIN_FILENO))
            exit(127);
        return (127);
    }

    pid = fork();
    if (pid == 0)
    {
        execve(cmd, args, environ);
        perror("execve");
        free(cmd);
        exit(EXIT_FAILURE);
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
        free(cmd);
    }
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (status);
}

