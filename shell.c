#include "simple_shell.h"

/**
 * shell_new - function
 * @s: shell_t ptr
 *
 * Return: shell_t ptr
*/
shell_t	*shell_new(shell_t *s)
{
	if (s)
		s = shell_free(s);
	s = (shell_t *) malloc(sizeof(shell_t));
	if (s == 0)
		return (0);
	return (s);
}

/**
 * shell_free - function
 * @s: shell_t ptr
 *
 * Return: shell_t ptr
*/
shell_t	*shell_free(shell_t *s)
{
	if (s == 0)
		return (0);
	free(s);
	return (0);
}

/**
 * shell_iter - function
 * @s: shell_t ptr
 * @argv: char ptr ptr
 * @envp: char ptr ptr
 *
 * Return: shell_t ptr
*/
shell_t	*shell_iter(shell_t *s, char **argv, char **envp)
{
	pid_t		pid;
	command_t	**commands;
	int		status;
	u64		x;

	if (isatty(STDOUT_FILENO) && isatty(STDIN_FILENO))
		print_string(PROMPT_TEXT);
	commands = commands_read(envp);
	if (commands == 0)
		return (shell_free(s));
	for (x = 0; commands[x]; x++)
	{
		if (commands[x]->argv[0] == 0)
			continue;
		pid = fork();
		if (pid == -1)
		{
			commands_free(commands, 0, 0);
			perror("failed at forking process");
			return (shell_free(s));
		}
		else if ((pid == 0) && (_execve(commands[x]) == -1))
		{
			commands_free(commands, 0, 0);
			print_string(argv[0]);
			print_string(": No such file or directory\n");
			return (shell_free(s));
		}
		else
		{
			wait(&status);
		}
	}
	commands_free(commands, 0, 0);
	return (s);
}

/**
 * shell_runtime - function
 * @s: shell_t ptr
 * @argv: char ptr ptr
 * @envp: char ptr ptr
 *
 * Return: shell_t ptr
*/
shell_t	*shell_runtime(shell_t *s, char **argv, char **envp)
{
	if (s == 0)
		return (0);
	while (1)
		if (shell_iter(s, argv, envp) == 0)
			return (0);
	return (s);
}
