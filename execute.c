#include "shell.h"

/**
 * execute - Executes a command with PATH resolution and built-ins
 * @args: Array of command and its arguments
 * @argv: Program name (argv[0]) for error messages
 * @cmd_count: Current command count (used for precise error output)
 * Return: The actual exit status of the command,
 *         127 if command not found,
 *         or 1 if fork/exec fails
 */
int execute(char **args, char *argv, int cmd_count)
{
    pid_t pid;
    int status;
    char *cmd;

    /* No command entered */
    if (args[0] == NULL)
        return (0);

    /* Handle built-in "exit" */
    if (strcmp(args[0], "exit") == 0)
        exit(0);

    /* Handle built-in "env" */
    if (strcmp(args[0], "env") == 0)
    {
        print_env();
        return (0);
    }

    /* Try to resolve command using PATH */
    cmd = find_path(args[0]);
    if (!cmd)
    {
        /* Command not found error with proper format */
        fprintf(stderr, "%s: %d: %s: not found\n", argv, cmd_count, args[0]);
        if (!isatty(STDIN_FILENO))
            exit(127);
        return (127);
    }

    /* Check if the resolved path is executable */
    if (access(cmd, X_OK) != 0)
    {
        fprintf(stderr, "%s: %d: %s: not found\n", argv, cmd_count, args[0]);
        free(cmd);
        if (!isatty(STDIN_FILENO))
            exit(127);
        return (127);
    }

    /* Fork the child process to execute the command */
    pid = fork();
    if (pid == 0)
    {
        /* In child: execute the command */
        execve(cmd, args, environ);
        perror("execve");
        free(cmd);
        exit(2); /* Execve failed */
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
        /* In parent: wait for child and return its exit status */
        waitpid(pid, &status, 0);
        free(cmd);
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
        else
            return (1);
    }
}

