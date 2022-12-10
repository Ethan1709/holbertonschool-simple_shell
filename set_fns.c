#include "simple_shell.h"

/**
 * set_filter_path - function
 * @set: set_t ptr
 * @str: u8 ptr
 *
 * Return: u8
*/
u8	set_filter_path(set_t *set, u8 *str)
{
	u64	x;
	u8	f;
	u8	**l;

	if (set == 0)
		return (0);
	if (str == 0)
		return (0);
	f = 0;
	for (x = 0; str[x]; x++)
		if (str[x] == '=')
			f = 1;
	if (f == 0)
		return (0);
	l = _strsplit(str, (u8 *) "=");
	if (l == 0)
		return (0);
	if (l[1] == 0)
	{
		for (x = 0; l[x]; x++)
			free(l[x]);
		free(l);
		return (0);
	}
	f = _strlen(l[0]) == _strlen((u8 *) "PATH")
		&& _strcmp(l[0], (u8 *) "PATH") == 0;
	for (x = 0; l[x]; x++)
		free(l[x]);
	free(l);
	return (f);
}

/**
 * set_apply_path - function
 * @set: set_t ptr
 * @v: vector_t ptr
 *
 * Return: vector_t ptr
*/
vector_t	*set_apply_path(set_t *set, vector_t *v)
{
	u8	**l;
	u8	*s;
	u64	x;

	if (set == 0)
		return (0);
	if (v == 0)
		return (0);
	s = vector_consume(v);
	l = _strsplit(s, (u8 *) "=");
	free(s);
	if (l == 0)
		return (0);
	if (l[0] == 0 || l[1] == 0)
	{
		for (x = 0; l[x]; x++)
			free(l[x]);
		free(l);
		return (0);
	}
	v = vector_write(vector_new(0), l[1], _strlen(l[1]));
	for (x = 0; l[x]; x++)
		free(l[x]);
	free(l);
	return (v);
}

/**
 * set_filter_path_exec - function
 * @set: set_t ptr
 * @str: u8 ptr
 *
 * Return: u8
*/
u8	set_filter_path_exec(set_t *set, u8 *str)
{
	if (set == 0)
		return (0);
	if (str == 0)
		return (0);
	if (str[0] != '/' && str[0] != '.')
		return (0);
	return (access((char *) str, X_OK) == 0);
}

/**
 * set_apply_path_exec - function
 * @set: set_t ptr
 * @v: vector_t ptr
 *
 * Return: vector_t ptr
*/
vector_t	*set_apply_path_exec(set_t *set, vector_t *v)
{
	vector_t	*r;
	u8		*s;

	if (set == 0)
		return (0);
	if (v == 0)
		return (0);
	r = vector_new(0);
	if (r == 0)
		return (0);
	s = vector_consume(v);
	if (s == 0)
		return (vector_free(r));
	if (vector_write(r, s, _strlen(s)) == 0)
	{
		free(s);
		return (vector_free(r));
	}
	free(s);
	if (vector_write(r, "/", 1) == 0)
		return (vector_free(r));
	if (vector_write(r, set->extra, _strlen(set->extra)) == 0)
		return (vector_free(r));
	return (r);
}
