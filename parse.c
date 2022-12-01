#include "simple_shell.h"

/**
 * token_delim - function
 * @c: char
 *
 * Return: int
*/
int	token_delim(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\n')
		return (1);
	return (0);
}

/**
 * tokens_count - function
 * @str: char ptr
 *
 * Return: u64
*/
u64	tokens_count(char *str)
{
	u64	r;
	u64	m;
	u64	x;

	r = 0;
	m = 0;
	for (x = 0; str && str[x]; x++)
	{
		if (token_delim(str[x]))
		{
			if (m > 0)
				r++;
			m = 0;
		}
		else
			m++;
	}
	r += m > 0;
	return (r);
}

/**
 * tokens - function
 * @str: char ptr
 *
 * Return: char ptr ptr
*/
char	**tokens(char *str)
{
	char		**r;
	vector_t	*v;
	u64		s;
	u64		m;
	u64		x;

	if (str == 0)
		return (0);
	r = (char **) malloc(sizeof(char *) * (tokens_count(str) + 1));
	if (r == 0)
		return (0);
	s = 0;
	m = 0;
	v = vector_new(0);
	for (x = 0; str[x]; x++)
	{
		if (token_delim(str[x]))
		{
			if (m > 0)
			{
				r[s++] = (char *) vector_consume(v);
				v = vector_new(0);
			}
			else
				v = vector_new(v);
			m = 0;
		}
		else
		{
			vector_write(v, &str[x], 1);
			m++;
		}
	}
	if (m > 0)
		r[s++] = (char *) vector_consume(v);
	else
		vector_free(v);
	r[s] = 0;
	return (r);
}
