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
	u64	x;

	if (s == 0)
		return (0);
	if (s->path)
	{
		for (x = 0; s->path[x]; x++)
			free(s->path[x]);
		free(s->path);
	}
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
	u64		y;

	if (isatty(STDOUT_FILENO) && isatty(STDIN_FILENO))
		print_string(PROMPT_TEXT);
	commands = commands_read(envp);
	if (commands == 0)
		return (shell_free(shell_exit(s, 1)));
	for (x = 0; commands[x]; x++)
	{
		if (commands[x]->argv[0] == 0)
			continue;
		if (shell_exit_test(s, commands[x]->argv[0]) == 0)
		{
			commands_free(commands, 0, 0);
			return (0);
		}
		for (y = 0; s->path[y]; y++)
		{
			if (commands[x]->path)
				free(commands[x]->path);
			commands[x]->path = path_generate(
				s->path[y], commands[x]->argv[0]);
			if (commands[x]->path == 0)
			{
				perror("failed at allocating executable path");
				return (shell_free(s));
			}
			if (access((char *) commands[x]->path, X_OK) == 0)
			{
				pid = fork();
				if (pid == -1)
				{
					commands_free(commands, 0, 0);
					perror("failed at forking process\n");
					return (shell_free(s));
				}
				else if ((pid == 0) && (_execve(commands[x]) == -1))
				{
					commands_free(commands, 0, 0);
					print_string("failed at executing\n");
					return (shell_free(s));
				}
				else
					wait(&status);
				commands_free(commands, 0, 0);
				return (s);
			}
		}
		print_string(argv[0]);
		print_string(": No such file or directory\n");
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
	if (shell_parse(s, envp) == 0)
		return (0);
	while (1)
		if (shell_iter(s, argv, envp) == 0)
			return (0);
	return (s);
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
