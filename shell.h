#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>

extern char **environ;

void display_prompt(void);
char *read_input(void);
int execute_command(char *line);
char *find_in_path(const char *command);

#endif /* SHELL_H */

