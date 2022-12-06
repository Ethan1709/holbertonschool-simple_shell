#include "simple_shell.h"

/**
 * path_generate - function
 * @dir: u8 ptr
 * @file: u8 ptr
 *
 * Return: u8 ptr
*/
u8	*path_generate(u8 *dir, u8 *file)
{
	u8	*r;
	u64	x;
	u64	y;

	if (dir == 0 || file == 0)
		return (0);
	r = (u8 *) malloc(sizeof(u8) * (2 + _strlen(dir) + _strlen(file)));
	if (r == 0)
		return (0);
	x = 0;
	for (y = 0; dir[y]; y++)
		r[x++] = dir[y];
	r[x++] = '/';
	for (y = 0; file[y]; y++)
		r[x++] = file[y];
	r[x] = 0;
	return (r);
}
