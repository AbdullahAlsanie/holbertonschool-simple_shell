#ifndef SHELL_H
#define SHELL_H

/* All needed headers for the project, determine by the allowed functions mentioned. */
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

/* the Globale varibale to use throughout the project */
extern char **environ;

#endif
