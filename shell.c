#include "simple_shell.h"

/**
 * shell_new - function
 * @s: shell_t ptr
 * @name: u8 ptr
 * @envp: set_t ptr
 * @path: set_t ptr
 *
 * Return: shell_t ptr
 */
shell_t	*shell_new(shell_t *s, u8 *name, set_t *envp, set_t *path)
{
	shell_free(s);
	s = (shell_t *) malloc(sizeof(shell_t));
	if (s == 0)
		return (0);
	s->name = _strdup(name);
	if (s->name == 0)
		return (shell_free(s));
	s->envp = set_clone(envp);
	if (s->envp == 0)
		return (shell_free(s));
	s->path = set_clone(path);
	if (s->path == 0)
		return (shell_free(s));
	return (s);
}

/**
 * shell_init_envp - function
 * @s: shell_t ptr
 * @env: char ptr ptr
 *
 * Return: shell_t ptr
*/
shell_t	*shell_init_envp(shell_t *s, char **env)
{
	if (s == 0)
		return (0);
	(void) env;
	return (s);
}

/**
 * shell_init - function
 * @s: shell_t ptr
 * @name: u8 ptr
 * @env: char ptr ptr
 *
 * Return: shell_t ptr
*/
shell_t	*shell_init(shell_t *s, u8 *name, char **env)
{
	set_t	*envp;
	set_t	*path;
	u8	**v;
	u8	*t;
	u64	x;

	s = shell_free(s);
	if (env == 0)
		return (0);
	envp = set_new(0);
	if (envp == 0)
		return (0);
	path = set_new(0);
	if (path == 0)
	{
		set_free(envp);
		return (0);
	}
	for (x = 0; env[x]; x++)
		envp = set_add(envp, (u8 *) env[x]);
	if (envp == 0)
	{
		set_free(path);
		return (0);
	}
	v = set_consume(set_apply(set_filter(
		set_clone(envp), set_filter_path), set_apply_path));
	if (v == 0)
	{
		set_free(envp);
		set_free(path);
		return (0);
	}
	if (v[0] == 0)
	{
		s = shell_new(s, name, envp, path);
		set_free(envp);
		set_free(path);
		return (s);
	}
	t = _strdup(v[0]);
	for (x = 0; v[x]; x++)
		free(v[x]);
	free(v);
	if (t == 0)
	{
		set_free(envp);
		set_free(path);
		return (0);
	}
	v = _strsplit(t, (u8 *) ":");
	free(t);
	if (v == 0)
	{
		set_free(envp);
		set_free(path);
		return (0);
	}
	for (x = 0; v[x]; x++)
		path = set_add(path, v[x]);
	for (x = 0; v[x]; x++)
		free(v[x]);
	free(v);
	s = shell_new(s, name, envp, path);
	set_free(envp);
	set_free(path);
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
	if (s->name)
		free(s->name);
	if (s->envp)
		set_free(s->envp);
	if (s->path)
		set_free(s->path);
	free(s);
	return (0);
}
