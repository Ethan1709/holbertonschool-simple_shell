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
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
	{
		if (nl)
			print_string("\n");
		print_string(EXIT_TEXT);
		print_string("\n");
	}
	return (shell_free(s));
}

/**
 * shell_exit_cmd - function
 * @s: shell_t ptr
 * @args: u8 ptr ptr
 *
 * Return: shell_t ptr
*/
shell_t	*shell_exit_cmd(shell_t *s, u8 **args)
{
	if (s == 0)
		return (0);
	if (_strlen(args[0]) != _strlen((u8 *) "exit"))
		return (s);
	if (_strcmp(args[0], (u8 *) "exit") != 0)
		return (s);
	return (shell_exit(s, 0));
}
