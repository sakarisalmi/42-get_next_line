#include "get_next_line.h"

size_t	ft_strlen(const char *s);
int		get_newline_index(t_gnl_struct *gnl_struct);
char	*join_read_buffer_to_main_buffer(t_gnl_struct *gnl_struct);
char	*get_single_line(t_gnl_struct *gnl_struct);
char	*trim_main_buffer(t_gnl_struct *gnl_struct);

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

int	get_newline_index(t_gnl_struct *gnl_struct)
{
	int		i;

	if (!gnl_struct->main_buffer)
		return (0);
	i = gnl_struct->last_checked_index;
	while (gnl_struct->main_buffer[i])
	{
		if (gnl_struct->main_buffer[i] == '\n')
		{
			gnl_struct->newline_index = i;
			return(1);
		}
		i++;
	}
	gnl_struct->last_checked_index = i;
	return(0);
}

char	*join_read_buffer_to_main_buffer(t_gnl_struct *gnl_struct)
{
	char 	*new_main_buffer;
	ssize_t i;
	ssize_t j;

	if (!gnl_struct->main_buffer)
	{
		gnl_struct->main_buffer = (char *)malloc(sizeof(char) * 1);
		gnl_struct->main_buffer[0] = '\0';
	}
	if (!gnl_struct->main_buffer || !gnl_struct->read_buffer)
		return(NULL);
	new_main_buffer = (char *)malloc((gnl_struct->main_buffer_length + gnl_struct->read_bytes + 1) * sizeof(char));
	if (!new_main_buffer)
		return (NULL);

	i = 0;
	while(i < gnl_struct->main_buffer_length)
	{
		new_main_buffer[i] = gnl_struct->main_buffer[i];
		++i;
	}
	j = 0;
	while(j < gnl_struct->read_bytes)
		new_main_buffer[i++] = gnl_struct->read_buffer[j++];
	new_main_buffer[i] = '\0';
	free(gnl_struct->main_buffer);
	gnl_struct->main_buffer_length += gnl_struct->read_bytes;
	return(new_main_buffer);
}

char	*get_single_line(t_gnl_struct *gnl_struct)
{
	char	*single_line;
	int		i;

	if (!gnl_struct->main_buffer)
		return(NULL);
	single_line = (char *)malloc(sizeof(char) * (gnl_struct->newline_index + 2));
	if (!single_line)
		return(NULL);
	i = 0;
	while (i <= gnl_struct->newline_index)
	{
		single_line[i] = gnl_struct->main_buffer[i];
		++i;
	}
	single_line[i] = '\0';
	if (single_line[0] == '\0')
	{
		free(single_line);
		return(NULL);
	}
	return(single_line);
}

char	*trim_main_buffer(t_gnl_struct *gnl_struct)
{
	char	*new_main_buffer;
	int 	i;
	int		j;

	// if true, discard whole buffer
	if (gnl_struct->main_buffer_length == gnl_struct->newline_index + 1)
	{
		free(gnl_struct->main_buffer);
		return(NULL);
	}
	new_main_buffer = (char *)malloc(sizeof(char) * (gnl_struct->main_buffer_length - gnl_struct->newline_index));
	if (!new_main_buffer)
		return(NULL);
	i = gnl_struct->newline_index + 1;
	j = 0;
	while (i < gnl_struct->main_buffer_length)
		new_main_buffer[j++] = gnl_struct->main_buffer[i++];
	free(gnl_struct->main_buffer);
	gnl_struct->main_buffer_length -= gnl_struct->newline_index + 1;
	return(new_main_buffer);
}
