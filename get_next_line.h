#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 30
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_gnl_struct {
	char		*main_buffer;
	ssize_t 	main_buffer_length;
	ssize_t		last_checked_index;
	ssize_t 	newline_index;

	char 		*read_buffer;
	ssize_t		read_bytes;
}	t_gnl_struct;

char	*get_next_line(int fd);

int		get_newline_index(t_gnl_struct *gnl_struct);
char	*join_read_buffer_to_main_buffer(t_gnl_struct *gnl_struct);
char	*get_single_line(t_gnl_struct *gnl_struct);
char	*trim_main_buffer(t_gnl_struct *gnl_struct);
size_t	ft_strlen(const char *s);

#endif