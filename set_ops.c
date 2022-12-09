#include "simple_shell.h"

/**
 * set_filter - function
 * @set: set_t ptr
 * @fn: function(set_t ptr, u8 ptr): u8
 *
 * Return: set_t ptr
*/
set_t	*set_filter(set_t *set, u8 (*fn)(set_t *, u8 *))
{
	set_t	*r;
	u64	x;

	if (set == 0)
		return (0);
	if (fn == 0)
		return (0);
	r = set_new(0);
	if (r == 0)
		return (set_free(set));
	for (x = 0; x < set->size; x++)
		if (fn(set, set->data[x]) == 1)
			set_add(r, set->data[x]);
	set_free(set);
	return (r);
}

/**
 * set_apply - function
 * @set: set_t ptr
 * @fn: function(set_t ptr, vector_t ptr): vector_t ptr
 *
 * Return: set_t ptr
*/
set_t	*set_apply(set_t *set, vector_t *(*fn)(set_t *, vector_t *))
{
	u8		**data;
	u64		x;

	if (set == 0)
		return (0);
	if (fn == 0)
		return (0);
	data = (u8 **) malloc(sizeof(u8 *) * (set->size));
	if (data == 0)
		return (set_free(set));
	for (x = 0; x < set->size; x++)
		data[x] = 0;
	for (x = 0; x < set->size; x++)
	{
		data[x] = vector_consume(fn(set, vector_write(
			vector_new(0), set->data[x], _strlen(set->data[x]))));
		if (data[x] == 0)
		{
			for (x = 0; x < set->size; x++)
				free(data[x]);
			free(data);
			return (set_free(set));
		}
	}
	if (set->data)
	{
		for (x = 0; x < set->size; x++)
			free(set->data[x]);
		free(set->data);
	}
	set->data = data;
	return (set);
}
