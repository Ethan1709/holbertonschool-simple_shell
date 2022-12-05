#include "simple_shell.h"

/**
 * _strchr - function
 * @s: u8 ptr
 * @v: u8
 *
 * Return: u8 ptr
*/
u8	*_strchr(u8 *s, u8 v)
{
	u64	x;

	if (s == 0)
		return (0);
	for (x = 0; s[x]; x++)
		if (s[x] == v)
			return (&s[x]);
	return (0);
}
