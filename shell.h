#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;

char *read_line(void);
char **split_line(char *line);
void free_args(char **args);
char *_getenv(const char *name);
char *find_path(char *cmd);
char *build_full_path(char *dir, char *cmd);
int execute(char **args, char *argv, int cmd_count);
void print_env(void);

#endif /* SHELL_H */

