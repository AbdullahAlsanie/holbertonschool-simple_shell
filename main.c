#include "shell.h"

int main(int ac __attribute__((unused)), char **av)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    pid_t pid;
    char *argv[64];
    char *token;
    char *path_cmd;
    int i;
    int line_number = 0; /* to track line number for error msg */

    while (1)
    {
        line_number++;
        printf("($) ");
        fflush(stdout);

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            printf("\n");
            break;
        }
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        i = 0;
        token = strtok(line, " \t");
        while (token != NULL && i < 63)
        {
            argv[i++] = token;
            token = strtok(NULL, " \t");
        }
        argv[i] = NULL;

        if (argv[0] == NULL)
            continue;
	
	if (strcmp(argv[0], "exit") == 0)
	{
		free(line);
		exit(0);
	}

	if (strcmp(argv[0], "env") == 0)
	{
		int j;
		for (j = 0; environ[j]; j++)
			printf("%s\n", environ[j]);
		continue;
	}



       	path_cmd = find_path(argv[0]);
        if (path_cmd == NULL)
        {
	    fprintf(stderr, "%s: %d: %s: not found\n", av[0], line_number, argv[0]);
            continue;
        }

        pid = fork();
        if (pid == 0)
        {
            if (execve(path_cmd, argv, environ) == -1)
            {
                perror(path_cmd);
                free(path_cmd);
                exit(EXIT_FAILURE);
            }
        }
        else if (pid > 0)
        {
            wait(NULL);
            free(path_cmd);
        }
        else
        {
            perror("fork");
            free(path_cmd);
        }
    }
    free(line);
    return (0);
}


