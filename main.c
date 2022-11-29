#include "simple_shell.h"

/**
 * runtime - function
 * @argv: char ptr ptr
 * @envp: char ptr ptr
*/
void	runtime(char **argv, char **envp)
{
	char		*args[2];
	pid_t		pid;
	int		status;
	char		*line;

	while (1)
	{
		print_string("#cisfun$ ");
		line = (char *) read_line();
		if (line == 0)
			exit(errno);
		args[0] = line;
		args[1] = NULL;
		pid = fork();
		if (pid == -1)
		{
			print_string("error\n");
			exit(1);
		}
		if (pid == 0)
		{
			if (execve(line, args, envp) == -1)
			{
				print_string(argv[0]);
				print_string(": No such file or directory\n");
			}
		}
		else
		{
			wait(&status);
		}
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
