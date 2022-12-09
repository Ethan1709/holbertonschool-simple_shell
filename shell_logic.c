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
	u8	**envp;
	u64	x;

	if (s == 0)
		return (0);
	envp = set_consume(set_clone(s->envp));
	if (envp == 0)
		return (shell_free(s));
	pid = fork();
	if (pid == -1)
	{
		for (x = 0; envp[x]; x++)
			free(envp[x]);
		free(envp);
		return (shell_free(s));
	}
	if (pid == 0 && execve((char *) path, (char **) args, (char **) envp) == -1)
	{
		print_string("failed at execve\n");
		for (x = 0; envp[x]; x++)
			free(envp[x]);
		free(envp);
	}
	else
	{
		wait(0);
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
 *
 * Return: shell_t ptr
*/
shell_t	*shell_iter_line(shell_t *s, u8 **args)
{
	set_t	*set;
	u64	x;

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
	{
		for (x = 0; args[x]; x++)
			free(args[x]);
		free(args);
		return (shell_free(s));
	}
	if (set->size < 1)
	{
		print_string((char *) s->name);
		print_string(ERRFILE);
	}
	else
	{
		shell_exec(s, _strdup(set->data[0]), args);
	}
	for (x = 0; args[x]; x++)
		free(args[x]);
	free(args);
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
	u8	*i;
	u64	x;

	i = read_line();
	if (i == 0)
		return (shell_exit(s, 1));
	l = _strsplit(i, (u8 *) ";\n");
	free(i);
	if (l == 0)
		return (shell_exit(s, 1));
	for (x = 0; l[x]; x++)
	{
		if (shell_iter_line(s, _strsplit(l[x], (u8 *) " ")) == 0)
			return (0);
		free(l[x]);
	}
	free(l);
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
