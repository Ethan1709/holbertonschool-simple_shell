#include "simple_shell.h"

/**
 * command_new - function
 * @c: command_t ptr
 *
 * Return: command_t ptr
*/
command_t	*command_new(command_t *c)
{
	command_t	*r;

	if (c)
		command_free(c);
	r = (command_t *) malloc(sizeof(command_t));
	if (r == 0)
		return (0);
	r->path = 0;
	r->argv = 0;
	r->envp = 0;
	return (r);
}

/**
 * command_free - function
 * @c: command_t ptr
 *
 * Return: command_t ptr
*/
command_t	*command_free(command_t *c)
{
	u64	x;

	if (c == 0)
		return (0);
	if (c->argv)
	{
		for (x = 0; c->argv[x]; x++)
			free(c->argv[x]);
		free(c->argv);
	}
	if (c->path)
		free(c->path);
	if (c)
		free(c);
	return (0);
}

/**
 * command_argv - function
 * @c: command_t ptr
 * @argv: char ptr ptr
 *
 * Return: command_t ptr
*/
command_t	*command_argv(command_t *c, char **argv)
{
	if (c == 0)
		return (0);
	if (argv == 0)
		return (command_free(c));
	if (argv)
		c->argv = (u8 **) argv;
	else
		c->argv = 0;
	return (c);
}

/**
 * command_envp - function
 * @c: command_t ptr
 * @envp: char ptr ptr
 *
 * Return: command_t ptr
*/
command_t	*command_envp(command_t *c, char **envp)
{
	if (c == 0)
		return (0);
	if (envp == 0)
		return (command_free(c));
	if (envp)
		c->envp = (u8 **) envp;
	else
		c->envp = 0;
	return (c);
}
