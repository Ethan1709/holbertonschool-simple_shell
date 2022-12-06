#include "simple_shell.h"

/**
 * _execve - function
 * @c: command_t ptr
 *
 * Return: int
*/
int	_execve(command_t *c)
{
	char	*tp;
	char	**ta;
	char	**te;

	if (c == 0)
		return (-1);

	tp = (char *) c->argv[0];
	ta = (char **) c->argv;
	te = (char **) c->envp;

	return (execve(tp, ta, te));
}
