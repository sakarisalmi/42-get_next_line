#include "get_next_line.h"

#include <stdio.h>

char		*get_next_line(int fd);
static void	read_next_line(int fd, t_gnl_struct *gnl_struct);
static void	clean_gnl_struct(t_gnl_struct *gnl_struct);


char	*get_next_line(int fd)
{
	static t_gnl_struct	gnl_struct;
	char				*single_line;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_next_line(fd, &gnl_struct);
	if (gnl_struct.main_buffer == NULL)
	{
		clean_gnl_struct(&gnl_struct);
		return(NULL);
	}
	single_line = get_single_line(&gnl_struct);
	gnl_struct.main_buffer = trim_main_buffer(&gnl_struct);
	// printf("main buffer length: %zd\tnewline index: %zd\tread buffer length: %zd\tlast checked index: %zd\n", gnl_struct.main_buffer_length, gnl_struct.newline_index, gnl_struct.read_bytes, gnl_struct.last_checked_index);
	return (single_line);
}

static void	read_next_line(int fd, t_gnl_struct *gnl_struct)
{
	gnl_struct->read_buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!gnl_struct->read_buffer)
		return;
	gnl_struct->read_bytes = 1;
	gnl_struct->last_checked_index = 0;
	while (gnl_struct->read_bytes != 0 && !get_newline_index(gnl_struct))
	{
		gnl_struct->read_bytes = read(fd, gnl_struct->read_buffer, BUFFER_SIZE);
		if (gnl_struct->read_bytes < 0)
			return;
		gnl_struct->read_buffer[gnl_struct->read_bytes] = '\0';
		if (gnl_struct->read_bytes != 0)
			gnl_struct->main_buffer = join_read_buffer_to_main_buffer(gnl_struct);
		else
			gnl_struct->newline_index = gnl_struct->main_buffer_length - 1;
	}
	free(gnl_struct->read_buffer);
	gnl_struct->read_buffer = NULL;
}

static void	clean_gnl_struct(t_gnl_struct *gnl_struct)
{
	if (gnl_struct->main_buffer)
	{
		free(gnl_struct->main_buffer);
		gnl_struct->main_buffer = NULL;
	}
	if (gnl_struct->read_buffer)
	{
		free(gnl_struct->read_buffer);
		gnl_struct->read_buffer = NULL;
	}
	gnl_struct->main_buffer_length = -1;
	gnl_struct->newline_index = -1;
	gnl_struct->read_bytes = 0;
}
