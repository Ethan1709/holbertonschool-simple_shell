#include "simple_shell.h"

/**
 * _strcat - function
 * @dst: u8 ptr
 * @src: u8 ptr
 *
 * Return: u8 ptr
*/
u8	*_strcat(u8 *dst, u8 *src)
{
	u64	x;
	u64	y;

	if (dst == 0)
		return (0);
	if (src == 0)
		return (0);
	for (x = 0; dst[x]; x++)
		;
	for (y = 0; src[y]; y++)
		dst[x++] = src[y];
	dst[x] = 0;
	return (dst);
}
