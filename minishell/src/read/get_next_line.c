#include "../../includes/minishell.h"

# define BUFFER_SIZE 1024

int has_new_line(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int len_until_newline(char *s)
{
	int i = 0;

	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

char *extract_line(char *stash)
{
	char	*line;
	int		len;
	int		i;

	if (!stash || !stash[0])
		return (NULL);
	len = len_until_newline(stash);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char *update_stash(char *stash)
{
	char	*new_stash;
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	start = i + 1;
	new_stash = malloc(ft_strlen(stash + start) + 1);
	if (!new_stash)
	{
		free(stash);
		return (NULL);
	}
	while (stash[start])
		new_stash[j++] = stash[start++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

char *get_next_line(int fd)
{
	static char	*stash;
	char		buffer[BUFFER_SIZE + 1];
	char		*tmp;
	char		*line;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes = 1;
	while (!has_new_line(stash) && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(stash), stash = NULL, NULL);
		buffer[bytes] = '\0';
		if (!stash)
			tmp = ft_strdup(buffer);
		else
			tmp = ft_strjoin(stash, buffer);
		free(stash);
		stash = NULL;
		if (!tmp)
			return (NULL);
		stash = tmp;
	}
	if (!stash || !stash[0])
		return (free(stash), stash = NULL, NULL);
	line = extract_line(stash);
	stash = update_stash(stash);
	return (line);
}
