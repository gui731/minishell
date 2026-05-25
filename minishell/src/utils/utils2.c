#include "../../includes/minishell.h"

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'));
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;

	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);

	i = 0;
	while (i < n - 1
		&& s1[i]
		&& s2[i]
		&& s1[i] == s2[i])
		i++;

	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}

	if ((char)c == '\0')
		return ((char *)s);

	return (NULL);
}

char	*ft_strremove(char *str, const char *remove)
{
	char	*result;
	char	*ptr;
	int		i;
	int		j;

	if (!str || !remove)
		return (NULL);
	result = (char *)malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	ptr = str;
	i = 0;
	j = 0;
	while (ptr[i])
	{
		if (ptr[i] != remove[0])
			result[j++] = ptr[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}