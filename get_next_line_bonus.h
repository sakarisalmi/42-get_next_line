#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 30
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_cache {
	int 	fd;
	void	*buf;
	ssize_t size;
	ssize_t	cap;
}	t_cache;


char	*get_next_line(int fd);

void 	*ft_memcpy(void *dst, const void *src, size_t n);
void 	*ft_strchr(const void *str, const unsigned char c);

#endif