#include "simple_shell.h"

/**
 * _strdup - function
 * @str: char ptr
 *
 * Return: char ptr
*/
char	*_strdup(char *str)
{
	char	*r;
	u64	x;

	if (str == 0)
		return (0);
	for (x = 0; str[x]; x++)
		;
	r = (char *) malloc(sizeof(char) * (x + 1));
	if (r == 0)
		return (0);
	for (x = 0; str[x]; x++)
		r[x] = str[x];
	r[x] = 0;
	return (r);
}
