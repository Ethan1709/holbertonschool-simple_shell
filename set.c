#include "simple_shell.h"

/**
 * set_new - function
 * @set: set_t ptr
 *
 * Return: set_t ptr
*/
set_t	*set_new(set_t *set)
{
	u8	**data;

	if (set != 0)
		set_free(set);
	data = (u8 **) malloc(sizeof(u8 *));
	if (data == 0)
		return (0);
	set = (set_t *) malloc(sizeof(set_t));
	if (set == 0)
	{
		free(data);
		return (0);
	}
	set->data = data;
	set->size = 0;
	return (set);
}

/**
 * set_free - function
 * @set: set_t ptr
 *
 * Return: set_t ptr
*/
set_t	*set_free(set_t *set)
{
	u64	x;

	if (set == 0)
		return (0);
	if (set->data)
	{
		for (x = 0; x < set->size; x++)
			free(set->data[x]);
		free(set->data);
	}
	free(set);
	return (0);
}

/**
 * set_consume - function
 * @set: set_t ptr
 *
 * Return: u8 ptr
*/
u8	**set_consume(set_t *set)
{
	u8	**r;
	u64	x;

	r = 0;
	if (set == 0)
		return (0);
	r = (u8 **) malloc(sizeof(u8 *) * (set->size + 1));
	if (r == 0)
	{
		set_free(set);
		return (0);
	}
	for (x = 0; x <= set->size; x++)
		r[x] = 0;
	for (x = 0; x < set->size; x++)
	{
		r[x] = _strdup(set->data[x]);
		if (r[x] == 0)
		{
			for (x = 0; x <= set->size; x++)
				free(r[x]);
			free(r);
			set_free(set);
			return (0);
		}
	}
	r[x] = 0;
	set_free(set);
	return (r);
}

/**
 * set_add - function
 * @set: set_t ptr
 * @str: u8 ptr
 *
 * Return: set_t ptr
*/
set_t	*set_add(set_t *set, u8 *str)
{
	u8	**data;
	u8	*s;
	u64	x;

	if (set == 0)
		return (0);
	if (str == 0)
		return (0);
	s = _strdup(str);
	if (s == 0)
		return (set_free(set));
	data = (u8 **) malloc(sizeof(u8 *) * (set->size + 1));
	if (data == 0)
	{
		free(s);
		return (set_free(set));
	}
	for (x = 0; x < set->size; x++)
	{
		data[x] = _strdup(set->data[x]);
		free(set->data[x]);
	}
	data[x] = s;
	free(set->data);
	set->data = data;
	set->size = set->size + 1;
	return (set);
}

/**
 * set_clone - function
 * @set: set_t ptr
 *
 * Return: set_t ptr
*/
set_t	*set_clone(set_t *set)
{
	set_t	*r;
	u64	x;

	if (set == 0)
		return (0);
	r = set_new(0);
	r->extra = set->extra;
	if (r == 0)
		return (set_free(set));
	for (x = 0; x < set->size; x++)
		if (set_add(r, set->data[x]) == 0)
			return (set_free(r));
	return (r);
}
