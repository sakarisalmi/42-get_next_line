#include "get_next_line.h"

static int	resize_buffer(t_cache *cache, ssize_t new_cap){
	void	*new_buffer;

	if (new_cap <= cache->cap)
		return(1);
	new_buffer = malloc(new_cap);
	if (!new_buffer)
		return(0);
	if (!cache->buf)
		cache->buf = new_buffer;
	else {
		ft_memcpy(new_buffer, cache->buf, cache->size);
		free(cache->buf);
		cache->buf = new_buffer;
	}
	cache->cap = new_cap;
	return(1);
}

static int init_cache(t_cache *cache, int fd) {
	if (fd != cache->fd) {
		cache->fd = fd;
		cache->cap = 0;
		if (!resize_buffer(cache, BUFFER_SIZE))
			return(0);
		cache->size = 0;
	}
	return(1);
}

static char *get_line_from_buf(t_cache *cache) {
	char *src;
	char *newline;
	char *line;
	size_t line_size, remaining_size;

	if (!cache->buf)
		return(NULL);
	src = (char *)cache->buf;
	newline = ft_strchr(src, '\n');
	if (newline) {
		line_size = newline - src + 1;
		line = malloc(line_size + 1);
		if (!line)
			return(NULL);
		line = ft_memcpy(line, src, line_size);
		line[line_size] = '\0';
		remaining_size = cache->size - line_size;
		src = ft_memcpy(src, src + line_size, remaining_size);
		src[remaining_size] = '\0';
		cache->size = remaining_size;
		return(line);
	}
	return(NULL);
}

char	*get_next_line(int fd)
{
	static t_cache	cache[4096];
	int				read_bytes;
	char			*line;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!init_cache(&cache[fd], fd))
		return(NULL);
	read_bytes = 1;
	while (read_bytes > 0){
		line = get_line_from_buf(&cache[fd]);
		if (line){
			return(line);
		}
		if (cache[fd].cap < cache[fd].size + BUFFER_SIZE){
			if (!resize_buffer(&cache[fd], 2 * cache[fd].cap))
				return(NULL);
		}
		read_bytes = read(fd, cache[fd].buf + cache[fd].size, BUFFER_SIZE);
		cache[fd].size += read_bytes;
	}
	return (line);
}