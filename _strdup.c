#include "simple_shell.h"

/**
 * _strdup - function
 * @str: u8 ptr
 *
 * Return: u8 ptr
*/
u8	*_strdup(u8 *str)
{
	u8	*r;
	u64	x;

	if (str == 0)
		return (0);
	for (x = 0; str[x]; x++)
		;
	r = (u8 *) malloc(sizeof(u8) * (x + 1));
	if (r == 0)
		return (0);
	for (x = 0; str[x]; x++)
		r[x] = str[x];
	r[x] = 0;
	return (r);
}
