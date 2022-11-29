#ifndef SIMPLE_SHELL_H
# define SIMPLE_SHELL_H

# include <unistd.h>
# include <stdlib.h>
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

void		print_string(char *str);
u8		*read_line();
void		*malloc_try(size_t size);
vector_t	*vector_new(vector_t *v);
vector_t	*vector_free(vector_t *v);
vector_t	*vector_write(vector_t *v, void *src, u64 len);
vector_t	*vector_read(vector_t *v, void *dst, u64 size);
u8		*vector_consume(vector_t *v);

# define BUFFER_SIZE (1024)

#endif
