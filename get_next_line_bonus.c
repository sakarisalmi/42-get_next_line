#include "get_next_line_bonus.h"

char	*get_next_line(int fd);
char	*read_next_line(int fd, char *static_line);
int		*get_fd_for_get_next_line(int fd);

char	*get_next_line(int fd)
{
	static char	*static_line[4096];
	char		*single_line;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_line[fd] = read_next_line(fd, static_line[fd]);
	if (!static_line[fd])
		return (NULL);
	single_line = get_single_line(static_line[fd]);
	static_line[fd] = trim_static_line(static_line[fd]);
	return (single_line);
}

char	*read_next_line(int fd, char *static_line)
{
	char	*buffer;
	int		read_bytes;
	int		i;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (read_bytes != 0 && !ft_strchr(static_line, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		if (read_bytes != 0)
			static_line = ft_strjoin(static_line, buffer);
	}
	i = -1;
	while (buffer[++i] != '\0')
		buffer[i] = '\0';
	free(buffer);
	return (static_line);
}
