#include "simple_shell.h"

/**
 * shell_exit - function
 * @s: shell_t ptr
 * @nl: u8
 *
 * Return: shell_t ptr
*/
shell_t	*shell_exit(shell_t *s, u8 nl)
{
	if (s == 0)
		return (0);
	if (isatty(STDOUT_FILENO) && isatty(STDIN_FILENO))
	{
		if (nl)
			print_string("\n");
		print_string("exit\n");
	}
	return (shell_free(s));
}

/**
 * shell_exit_test - function
 * @s: shell_t ptr
 * @command: u8 ptr
 *
 * Return: shell_t ptr
*/
shell_t	*shell_exit_test(shell_t *s, u8 *command)
{
	if (s == 0)
		return (s);
	if (_strlen((u8 *) command) != _strlen((u8 *) "exit"))
		return (s);
	if (_strcmp((u8 *) command, (u8 *) "exit") != 0)
		return (s);
	return (shell_exit(s, 0));
}

/**
 * shell_parse - function
 * @s: shell_t ptr
 * @envp: char ptr ptr
 *
 * Return: shell_t ptr
*/
shell_t *shell_parse(shell_t *s, char **envp)
{
	u64	x;
	u64	y;
	u8	**kv;

	if (s == 0)
		return (0);
	for (x = 0; envp[x]; x++)
	{
		kv = _strsplit((u8 *) envp[x], (u8 *) "=");
		if (kv == 0)
			return (shell_free(s));
		if (_strcmp((u8 *) kv[0], (u8 *) "PATH") == 0 &&
			_strlen(kv[0]) == _strlen((u8 *) "PATH"))
		{
			s->path = _strsplit((u8 *) kv[1], (u8 *) ":");
			if (s->path == 0)
			{
				for (y = 0; kv[y]; y++)
					free(kv[y]);
				free(kv);
				return (shell_free(s));
			}
		}
		for (y = 0; kv[y]; y++)
			free(kv[y]);
		free(kv);
	}
	return (s);
}
