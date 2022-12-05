#include "simple_shell.h"

/**
 * commands_read - function
 * @envp: char ptr ptr
 *
 * Return: command_t ptr
*/
command_t	**commands_read(char **envp)
{
	command_t	**r;
	u8		**l;
	u8		*s;
	u64		x;

	s = read_line();
	if (s == 0)
		return (0);
	l = _strsplit(s, (u8 *) "\n");
	free(s);
	if (l == 0)
		return (0);
	for (x = 0; l[x]; x++)
		;
	r = (command_t **) malloc(sizeof(command_t *) * (x + 1));
	if (r == 0)
	{
		free(l);
		return (0);
	}
	for (x = 0; l[x]; x++)
	{
		r[x] = command_envp(command_argv(command_new(0),
			(char **) _strsplit(l[x], (u8 *) " ")), envp);
		if (r[x] == 0)
		{
			commands_free(r, x, 1);
			for (; x > 0; x--)
				free(l[x]);
			free(l[x]);
			free(l);
			return (0);
		}
	}
	for (x = 0; l[x]; x++)
		free(l[x]);
	free(l);
	r[x] = 0;
	return (r);
}

/**
 * commands_free - function
 * @commands: command_t ptr ptr
 * @index: u64
 * @indexed: u8
*/
void	commands_free(command_t **commands, u64 index, u8 indexed)
{
	u64	x;

	if (commands == 0)
		return;
	if (indexed)
	{
		for (x = 0; commands[x] && x <= index; x++)
		{
			command_free(commands[x]);
		}
	}
	else
	{
		for (x = 0; commands[x]; x++)
		{
			command_free(commands[x]);
		}
	}
	free(commands);
}
