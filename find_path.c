#include "shell.h"
/**
 * find_path - finds the full path of a command using PATH
 * @cmd: the command name
 * Return: full path if found, NULL otherwise
 */

char *find_path(char *cmd)
{
    char *path_env, *path_copy, *dir;
    char full_path[1024];
    struct stat st;

    if (!cmd)
        return (NULL);

    /* If command contains '/', it's an absolute or relative path */
    if (cmd[0] == '/' || strncmp(cmd, "./", 2) == 0 || strncmp(cmd, "../", 3) == 0)
    {
        if (stat(cmd, &st) == 0)
            return (strdup(cmd));
        else
            return (NULL);
    }

    /* Get PATH environment variable */
    path_env = _getenv("PATH");

    /* If PATH doesn't exist at all */
    if (!path_env)
    {
        return (NULL);  /* Don't check current directory */
    }

    /* If PATH is empty string - THIS IS THE CRITICAL FIX */
    if (path_env[0] == '\0')
    {
        /* For empty PATH, some tests expect "OK" to be printed */
        /* But this should be handled in execute(), not here */
        return (NULL);
    }

    path_copy = strdup(path_env);
    if (!path_copy)
        return (NULL);

    dir = strtok(path_copy, ":");
    while (dir)
    {
        /* Handle empty directory (::) - means current directory */
        if (strlen(dir) == 0)
            snprintf(full_path, sizeof(full_path), "./%s", cmd);
        else
            snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);

        if (stat(full_path, &st) == 0)
        {
            free(path_copy);
            return (strdup(full_path));
        }
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return (NULL);
}
