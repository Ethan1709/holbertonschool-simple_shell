#include "simple_shell.h"

/**
 * print_char - function
 * @c: char
*/
void	print_char(char c)
{
	write(1, &c, 1);
}

/**
 * print_string - function
 * @str: char ptr
*/
void	print_string(char *str)
{
	if (!*str)
		return;
	print_char(*str++);
	print_string(str);
}

/**
 * read_line - function
 *
 * Return: []u8
*/
u8	*read_line()
{
	vector_t	*v;
	u8		*b;
	i64		l;

	b = (u8 *) malloc(sizeof(u8) * (BUFFER_SIZE));
	if (b == 0)
		return (0);
	v = vector_new(0);
	if (v == 0)
	{
		free(b);
		return (0);
	}
	while (1)
	{
		l = read(STDIN_FILENO, b, BUFFER_SIZE);
		if (l == -1)
		{
			free(b);
			vector_free(v);
			return (0);
		}
		if (l == 0)
		{
			free(b);
			vector_free(v);
			return (0);
		}
		vector_write(v, b, l - (b[l - 1] == '\n'));
		if (l < BUFFER_SIZE)
			break;
	}
	free(b);
	return (vector_consume(v));
}
