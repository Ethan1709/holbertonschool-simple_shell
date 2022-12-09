#include "simple_shell.h"

/**
 * shell_prompt - function
 * @s: shell_t ptr
 *
 * Return: shell_t ptr
*/
shell_t *shell_prompt(shell_t *s)
{
	if (s == 0)
		return (0);
	if (isatty(STDOUT_FILENO) && isatty(STDIN_FILENO))
		print_string(PROMPT_TEXT);
	return (s);
}

/**
 * shell_exec - function
 * @s: shell_t ptr
 * @path: u8 ptr
 * @args: u8 ptr ptr
 *
 * Return: shell_t ptr
*/
shell_t	*shell_exec(shell_t *s, u8 *path, u8 **args)
{
	pid_t	pid;
	int	status;
	u8	**envp;
	u64	x;

	if (s == 0)
		return (0);
	envp = set_consume(set_clone(s->envp));
	if (envp == 0)
		return (0);
	pid = fork();
	if (pid == -1)
	{
		for (x = 0; envp[x]; x++)
			free(envp[x]);
		free(envp);
		return (0);
	}
	if (pid == 0 && execve((char *) path, (char **) args, (char **) envp) == -1)
	{
		for (x = 0; envp[x]; x++)
			free(envp[x]);
		free(envp);
		return (0);
	}
	else
	{
		wait(&status);
		if (status != 0)
			*(s->exit) = 2;
	}
	for (x = 0; envp[x]; x++)
		free(envp[x]);
	free(envp);
	return (s);
}

/**
 * shell_iter_line - function
 * @s: shell_t ptr
 * @args: u8 ptr ptr
 * @line: u64
 *
 * Return: shell_t ptr
*/
shell_t	*shell_iter_line(shell_t *s, u8 **args, u64 line)
{
	set_t	*set;
	u8	*str;

	if (s == 0)
		return (0);
	if (args == 0)
		return (shell_free(s));
	if (args[0] == 0)
		return (s);
	if (shell_exit_cmd(s, args) == 0)
		return (0);
	s->path->extra = args[0];
	set = set_filter(set_add(set_apply(set_clone(s->path),
		set_apply_path_exec), args[0]), set_filter_path_exec);
	s->path->extra = 0;
	if (set == 0)
		return (shell_free(s));
	if (set->size < 1)
	{
		print_not_found(s->name, line + 1, args[0]);
		*(s->exit) = 127;
	}
	else
	{
		str = _strdup(set->data[0]);
		if (str == 0)
			return (shell_free(s));
		if (shell_exec(s, str, args) == 0)
		{
			print_not_found(s->name, line + 1, args[0]);
			*(s->exit) = 127;
		}
		free(str);
	}
	set_free(set);
	return (s);
}

/**
 * shell_iter - function
 * @s: shell_t ptr
 *
 * Return: shell_t ptr
*/
shell_t	*shell_iter(shell_t *s)
{
	u8	**l;
	u8	**a;
	u8	*i;
	u64	x;
	u64	y;
	u8	f;

	i = read_line();
	if (i == 0)
		return (shell_exit(s, 1));
	l = _strsplit(i, (u8 *) ";\n");
	free(i);
	if (l == 0)
		return (shell_exit(s, 1));
	f = 0;
	for (x = 0; l[x]; x++)
	{
		a = _strsplit(l[x], (u8 *) " ");
		if (a == 0)
			continue;
		f = shell_iter_line(s, a, x) == 0;
		for (y = 0; a[y]; y++)
			free(a[y]);
		free(a);
		if (f)
			break;
	}
	for (x = 0; l[x]; x++)
		free(l[x]);
	free(l);
	if (f)
		return (0);
	return (s);
}

/**
 * shell_runtime - function
 * @s: shell_t ptr
 *
 * Return: shell_t ptr
*/
shell_t	*shell_runtime(shell_t *s)
{
	if (s == 0)
		return (0);
	while (1)
		if (shell_iter(shell_prompt(s)) == 0)
			return (0);
	return (shell_free(s));
}
