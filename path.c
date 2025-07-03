#include "shell.h"

extern char **environ;

/**
 * _getenv - Get the envrionment variables
 * @name: The path to read from
 *
 * Return: The list of paths
 */
char *_getenv(char *name)
{
	int i;
	size_t len = strlen(name);

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
	}
	return (NULL);
}


/**
 * find_in_path - Searches for a command in PATH
 * @command: Command to search
 *
 * Return: PATH to command if found and executable, or NULL if not found
 */
char *find_in_path(const char *command)
{
	char *path = _getenv("PATH");
	char *path_copy, *dir;
	char full_path[1024];

	if (path == NULL || *path == '\0')
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return strdup(full_path);
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

