#include "simple_shell.h"

/**
 * vector_new - function
 * @v: vector_t ptr
 *
 * Return: vector_t ptr
*/
vector_t	*vector_new(vector_t *v)
{
	vector_t	*r;
	u8		*data;

	if (v)
		vector_free(v);
	data = (u8 *) malloc(sizeof(u8) * 1024);
	if (data == 0)
		return (0);
	r = (vector_t *) malloc(sizeof(vector_t));
	if (r == 0)
	{
		free(data);
		return (0);
	}
	r->data = data;
	r->size = 1024;
	r->curr = 0;
	return (r);
}

/**
 * vector_free - function
 * @v: vector_t ptr
 *
 * Return: vector_t ptr
*/
vector_t	*vector_free(vector_t *v)
{
	if (v == 0)
		return (0);
	if (v->data)
		free(v->data);
	free(v);
	return (0);
}

/**
 * vector_write - function
 * @v: vector_t ptr
 * @src: void ptr
 * @len: u64
 *
 * Return: vector_t ptr
*/
vector_t	*vector_write(vector_t *v, void *src, u64 len)
{
	u8	*data;
	u64	x;

	if (v == 0)
		return (0);
	if ((v->curr + len) > v->size)
	{
		data = (u8 *) malloc(sizeof(u8) * (v->size * 2));
		if (data == 0)
		{
			free(data);
			return (vector_free(v));
		}
		for (x = 0; x < v->curr; x++)
			data[x] = v->data[x];
		free(v->data);
		v->data = data;
		v->size = v->size * 2;
	}
	for (x = 0; x < len; x++)
		v->data[v->curr + x] = ((u8 *) src)[x];
	v->curr = v->curr + len;
	return (v);
}

/**
 * vector_read - function
 * @v: vector_t ptr
 * @dst: void ptr
 * @size: u64
 *
 * Return: vector_t ptr
*/
vector_t	*vector_read(vector_t *v, void *dst, u64 size)
{
	u64	x;

	if (v == 0)
		return (0);
	for (x = 0; dst && x < size && x < v->curr; x++)
		((u8 *) dst)[x] = v->data[x];
	return (v);
}

/**
 * vector_consume - function
 * @v: vector_t ptr
 *
 * Return: []u8
*/
u8	*vector_consume(vector_t *v)
{
	u8	*r;

	if (v == 0)
		return (0);
	r = (u8 *) malloc(sizeof(u8) * (v->curr + 1));
	if (r == 0)
	{
		vector_free(v);
		return (0);
	}
	r[v->curr] = '\0';
	vector_read(v, r, v->curr);
	vector_free(v);
	return (r);
}
