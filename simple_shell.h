#ifndef SIMPLE_SHELL_H
# define SIMPLE_SHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

# define i8  int8_t
# define u8  uint8_t
# define i32 int32_t
# define u32 uint32_t
# define i64 int64_t
# define u64 uint64_t

/**
 * struct vector_s - struct
 * @data: []u8
 * @size: u64
 * @curr: u64
*/
typedef struct vector_s
{
	u8	*data;
	u64	size;
	u64	curr;
}	vector_t;

/**
 * struct command_s - struct
 * @path: u8 ptr
 * @argv: u8 ptr ptr
 * @envp: u8 ptr ptr
 */
typedef struct command_s
{
	u8	*path;
	u8	**argv;
	u8	**envp;
}	command_t;

/**
 * struct shell_s - struct
 * @path: u8 ptr ptr
 */
typedef struct shell_s
{
	u8	**path;
}	shell_t;

void		*malloc_try(size_t size);
char		*_strdup(char *);
u8		*_strchr(u8 *, u8);
u64		_strlen(u8 *);
i32		_strcmp(u8 *, u8 *);
u8		*_strcat(u8 *dst, u8 *src);
void		print_string(char *str);
u8		**_strsplit(u8 *str, u8 *lim);
u8		*read_line();
int		_execve(command_t *c);
vector_t	*vector_new(vector_t *v);
vector_t	*vector_free(vector_t *v);
vector_t	*vector_write(vector_t *v, void *src, u64 len);
vector_t	*vector_read(vector_t *v, void *dst, u64 size);
u8		*vector_consume(vector_t *v);
command_t	*command_new(command_t *c);
command_t	*command_free(command_t *c);
command_t	*command_argv(command_t *c, char **argv);
command_t	*command_envp(command_t *c, char **envp);
command_t	**commands_read(char **envp);
void		commands_free(command_t **commands, u64 index, u8 indexed);
u8		*path_generate(u8 *dir, u8 *file);
shell_t		*shell_new(shell_t *s);
shell_t		*shell_free(shell_t *s);
shell_t		*shell_iter(shell_t *s, char **argv, command_t **commands);
shell_t		*shell_iter_init(shell_t *s, char **argv, char **envp);
shell_t		*shell_runtime(shell_t *s, char **argv, char **envp);
shell_t		*shell_parse(shell_t *s, char **envp);
shell_t		*shell_exit(shell_t *s, u8 nl);
shell_t		*shell_exit_test(shell_t *s, u8 *command);

# define BUFFER_SIZE (1024)
# define PROMPT_TEXT "#cisfun$ "
# define ERRFILE     ": No such file or directory\n"

#endif
