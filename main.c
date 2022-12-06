#include "simple_shell.h"

/**
 * main - function
 * @argc: int
 * @argv: char ptr ptr
 * @envp: char ptr ptr
 *
 * Return: int
*/
int	main(int argc, char **argv, char **envp)
{
	shell_t	*s;
	char	**_envp;
	u64	x;

	for (x = 0; envp[x]; x++)
		;
	_envp = (char **) malloc(sizeof(char *) * (x + 1));
	for (x = 0; envp[x]; x++)
		_envp[x] = _strdup(envp[x]);
	_envp[x] = 0;

	s = shell_new(0);
	if (s == 0)
	{
		perror("failed at allocating shell");
		exit(0);
	}
	shell_free(shell_runtime(s, argv, _envp));

	for (x = 0; envp[x]; x++)
		free(_envp[x]);
	free(_envp);
	(void) argv;
	(void) argc;
	return (0);
}
