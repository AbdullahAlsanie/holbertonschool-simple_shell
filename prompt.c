#include "shell.h"

/**
 * display_prompt - Checks if the stdin is a terminal and displays a message
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "#cisfun$ ", 9);
}

