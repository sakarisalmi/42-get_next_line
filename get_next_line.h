#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 30
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_buffer_data {
	void	*buf;
	ssize_t size;
	ssize_t	type_size;
	ssize_t	cap;
}	t_buffer_data;

typedef struct s_cache {
	int fd;
	t_buffer_data bdata;
}	t_cache;


char	*get_next_line(int fd);

void 	*ft_memcpy(void *dst, const void *src, size_t n);
void 	*ft_strchr(const void *str, unsigned char c);
void	copy_buffer_data_to_cache(t_cache *cache, t_buffer_data *bdata);

#endif