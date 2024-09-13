#include "get_next_line.h"

static int	resize_buffer(t_buffer_data *bdata, ssize_t new_cap){
	void	*new_buffer;

	if (new_cap <= bdata->cap)
		return(1);
	new_buffer = malloc(new_cap);
	if (!new_buffer)
		return(0);
	if (!bdata->buf)
		bdata->buf = new_buffer;
	else {
		ft_memcpy(new_buffer, bdata->buf, bdata->size * bdata->type_size);
		free(bdata->buf);
		bdata->buf = new_buffer;
	}
	bdata->cap = new_cap;
	return(1);
}

static int init_buffer_data(t_cache *cache, t_buffer_data *bdata, int fd) {
	if (fd == cache->fd) {
		ft_memcpy(bdata, &cache->bdata, sizeof(t_buffer_data));
		cache->bdata.buf = NULL;
		cache->bdata.cap = 0;
		cache->bdata.size = 0;
		cache->bdata.type_size = 0;
	} else {
		cache->fd = fd;
		bdata->cap = 0;
		if (!resize_buffer(bdata, BUFFER_SIZE))
			return(0);
		bdata->size = 0;
		bdata->type_size = sizeof(char);
	}
	return(1);
}

static char *get_line_from_buf(t_buffer_data *bdata) {
	char *src;
	char *newline;
	char *line;
	size_t line_size, remaining_size;

	if (!bdata->buf)
		return(NULL);
	src = (char *)bdata->buf;
	newline = ft_strchr(src, '\n');
	if (newline) {
		line_size = newline - src + 1;
		line = malloc(line_size + 1);
		if (!line)
			return(NULL);
		line = ft_memcpy(line, src, line_size);
		line[line_size] = '\0';
		remaining_size = bdata->size - line_size;
		src = ft_memcpy(src, src + line_size, remaining_size);
		src[remaining_size] = '\0';
		bdata->size = remaining_size;
		return(line);
	}
	return(NULL);
}

char	*get_next_line(int fd)
{
	static t_cache	cache;
	t_buffer_data	bdata;
	int				read_bytes;
	char			*line;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!init_buffer_data(&cache, &bdata, fd))
		return(NULL);
	read_bytes = 1;
	while (read_bytes > 0){
		line = get_line_from_buf(&bdata);
		if (line){
			copy_buffer_data_to_cache(&cache, &bdata);
			return(line);
		}
		if (bdata.cap < bdata.size + BUFFER_SIZE){
			if (!resize_buffer(&bdata, 2 * bdata.cap))
				return(NULL);
		}
		read_bytes = read(fd, bdata.buf + bdata.size, BUFFER_SIZE);
		bdata.size += read_bytes;
	}
	return (line);
}