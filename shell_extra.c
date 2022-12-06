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
	if (nl)
		print_string("\n");
	print_string("exit\n");
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
