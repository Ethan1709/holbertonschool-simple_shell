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
	int	exit;
	shell_t	*shell;

	exit = 0;
	shell = shell_init(0, (u8 *) argv[0], envp);
	if (shell == 0)
		return (0);
	shell->exit = &exit;
	shell_free(shell_runtime(shell));
	(void) argc;
	return (exit);
}
