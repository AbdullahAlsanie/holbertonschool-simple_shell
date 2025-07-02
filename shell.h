#ifndef SHELL_H
#define SHELL_H
#define *GNU*SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>

extern char **environ;

char *read_line(void);
char **split_line(char *line);
int execute(char **args, char *argv, int cmd_count);
char *find_path(char *cmd);
void print_env(void);
void free_args(char **args);
char *_getenv(const char *name);

#endif
