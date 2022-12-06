#include "simple_shell.h"

/**
 * _strlen - function
 * @s: u8 ptr
 *
 * Return: u64
*/
u64	_strlen(u8 *s)
{
	u64	x;

	for (x = 0; s && s[x]; x++)
		;
	return (x);
}
