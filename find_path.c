#include "shell.h"
#include <sys/stat.h>  /* لإضافة تعريف struct stat, stat() */
#include <string.h>    /* لتضمين دوال مثل strchr, strdup, strtok */
#include <stdlib.h>    /* لتضمين malloc, free */

char *find_path(char *command)
{
    char *path_env = NULL, *path_env_dup, *dir;
    char *full_path = NULL;
    size_t len;
    struct stat st;
    int i;  /* عرف المتغير خارج الحلقة */

    if (command == NULL)
        return (NULL);

    if (strchr(command, '/'))
    {
        if (access(command, X_OK) == 0)
            return (strdup(command));
        return (NULL);
    }

    for (i = 0; environ[i]; i++)  /* عرّف i قبل الحلقة */
    {
        if (strncmp(environ[i], "PATH=", 5) == 0)
        {
            path_env = environ[i] + 5;
            break;
        }
    }

    if (path_env == NULL)
        return (NULL);

    path_env_dup = strdup(path_env);
    if (path_env_dup == NULL)
        return (NULL);

    dir = strtok(path_env_dup, ":");
    while (dir != NULL)
    {
        len = strlen(dir) + 1 + strlen(command) + 1;
        full_path = malloc(len);
        if (full_path == NULL)
        {
            free(path_env_dup);
            return (NULL);
        }

        strcpy(full_path, dir);
        strcat(full_path, "/");
        strcat(full_path, command);

        if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
        {
            free(path_env_dup);
            return (full_path);
        }

        free(full_path);
        full_path = NULL;

        dir = strtok(NULL, ":");
    }

    free(path_env_dup);
    return (NULL);
}


