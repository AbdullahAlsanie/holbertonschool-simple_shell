#include "shell.h"

/**
 * rm_spaces - remove spaces btween the commande
 * @str: string to operate on
 * Return: updated string
 */
char* rm_spaces(char* str)
{
	int i = 0, j = 0;

	while (str[i])
	{
		if (str[i] != ' ')
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}
