#include "shell.h"

/**
 * check_access - Checks if the file is executable
 * @argv: Argument list
 * @full_path: Resolved path
 *
 * Return: 0 if OK, 127 if not executable
 */
int check_access(char **argv, char *full_path)
{
	if (access(full_path, X_OK) != 0)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
		if (full_path != argv[0])
			free(full_path);
		return (127);
	}
	return (0);
}

/**
 * child_process - Runs execve in child process
 * @full_path: Path to executable
 * @argv: Arguments
 */
void child_process(char *full_path, char **argv)
{
	if (execve(full_path, argv, environ) == -1)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
		exit(127);
	}
}

/**
 * parent_process - Waits for child and frees memory
 * @pid: Process ID
 * @full_path: Path to executable
 * @argv: Arguments
 *
 * Return: status code
 */
int parent_process(pid_t pid, char *full_path, char **argv)
{
	int status;

	wait(&status);
	if (full_path != argv[0])
		free(full_path);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (1);
}

/**
 * run_external - Runs an external command
 * @argv: Argument list
 * @full_path: Resolved path
 *
 * Return: status code
 */
int run_external(char **argv, char *full_path)
{
	pid_t pid;
	int status = check_access(argv, full_path);

	if (status != 0)
		return (status);

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		if (full_path != argv[0])
			free(full_path);
		return (1);
	}

	if (pid == 0)
		child_process(full_path, argv);
	else
		status = parent_process(pid, full_path, argv);

	return (status);
}

