#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *static_line, char *buffer);
char	*get_single_line(char *str);
char	*trim_static_line(char *old_str);

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

char	*ft_strchr(char *s, int c)
{
	int		i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *static_line, char *buffer)
{
	unsigned int		len;
	unsigned int		j;
	char				*str;

	len = 0;
	j = 0;
	if (!static_line)
	{
		static_line = (char *)malloc(sizeof(char) * 1);
		static_line[0] = '\0';
	}
	if (!static_line || !buffer)
		return (NULL);
	str = (char *)malloc((ft_strlen(static_line) + ft_strlen(buffer)
				+ 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (static_line[j])
		str[len++] = static_line[j++];
	j = 0;
	while (buffer[j])
		str[len++] = buffer[j++];
	str[len] = '\0';
	free(static_line);
	return (str);
}

char	*get_single_line(char *static_line)
{
	char	*single_line;
	int		len;
	int		i;

	len = 0;
	i = -1;
	if (!static_line)
		return (NULL);
	while (static_line[len] && static_line[len] != '\n')
		len++;
	if (static_line[len] == '\n')
		len++;
	single_line = (char *)malloc(sizeof(char) * (len + 1));
	if (!single_line)
		return (NULL);
	while (++i < len)
		single_line[i] = static_line[i];
	single_line[i] = '\0';
	if (single_line[0] != '\0')
		return (single_line);
	else
	{
		free(single_line);
		return (NULL);
	}
}

char	*trim_static_line(char *old_str)
{
	unsigned int		i;
	unsigned int		j;
	char				*new_str;

	i = 0;
	while (old_str[i] && old_str[i] != '\n')
		i++;
	if (!old_str[i])
	{
		free(old_str);
		return (NULL);
	}
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(old_str) - i + 1));
	if (!new_str)
		return (NULL);
	i++;
	j = 0;
	while (old_str[i])
			new_str[j++] = old_str[i++];
	new_str[j] = '\0';
	free(old_str);
	if (new_str[0] != '\0')
		return (new_str);
	free(new_str);
	return (NULL);
}
