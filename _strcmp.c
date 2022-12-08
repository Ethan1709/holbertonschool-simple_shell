#include "simple_shell.h"

/**
 * _strcmp - function
 * @s1: u8 ptr
 * @s2: u8 ptr
 *
 * Return: i32
*/
i32	_strcmp(u8 *s1, u8 *s2)
{
	u64	x;

	if (s1 == 0 || s2 == 0)
		return (-1);
	for (x = 0; s1[x] || s2[x]; x++)
		if (s1[x] != s2[x])
			return (s1[x] - s2[x]);
	return (0);
}
