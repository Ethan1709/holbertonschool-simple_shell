#include "simple_shell.h"

/**
 * malloc_try - allocates chunk of 0 filled memory while exiting on failure
 * @size: size_t
 *
 * Return: void ptr
*/
void	*malloc_try(size_t size)
{
	void	*r;
	size_t	x;

	r = malloc(size);
	if (!r)
		exit(1);
	for (x = 0; x < size; x++)
		((u8 *) r)[x] = 0;
	return (r);
}
