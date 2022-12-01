#include "simple_shell.h"

/**
 * execute - function
 * @path: char ptr
 * @argv: char ptr ptr
 * @envp: char ptr ptr
 * @name: char ptr
 *
 * Return: int
*/
int	execute(char *path, char **argv, char **envp, char *name)
{
	pid_t	p;
	int	s;

	p = fork();
	if (p == -1)
	{
		perror("failed at creating fork");
		return (-1);
	}
	if (p == 0)
	{
		if (execve(path, argv, envp) == -1)
		{
			print_string(name);
			print_string(": No such file or directory\n");
			return (0);
		}
	}
	else
	{
		wait(&s);
	}
}

/**
 * execute_args - function
 * @name: char ptr
 *
 * Return: char ptr ptr
*/
char	**execute_args(char *name)
{
	char	**r;

	r = (char **) malloc(sizeof(char *) * 2);
	if (r == 0)
		return (0);
	r[0] = _strdup(name);
	r[1] = 0;
	return (r);
}

/**
 * execute_args_free - function
 * @args: char ptr ptr
*/
void execute_args_free(char **args)
{
	u64	x;

	if (args == 0)
		return;
	for (x = 0; args[x]; x++)
		free(args[x]);
	free(args);
}

/**
 * runtime - function
 * @argv: char ptr ptr
 * @envp: char ptr ptr
*/
void	runtime(char **argv, char **envp)
{
	char	**t;
	char	**args;
	char	*l;
	pid_t	p;
	u64	x;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			print_string(PROMPT_TEXT);
		l = read_line();
		if (l == 0)
			exit(0);
		t = tokens(l);
		free(l);
		if (t == 0)
			exit(0);
		for (x = 0; t[x]; x++)
		{
			args = execute_args(t[x]);
			if (args)
				execute(t[x], args, envp, argv[0]);
			execute_args_free(args);
			free(t[x]);
		}
		free(t);
	}
}

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
	(void) argc;
	runtime(argv, envp);
	return (0);
}
