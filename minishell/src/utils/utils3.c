#include "../../includes/minishell.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;

	i = 0;
	while (s[i])
		i++;

	dup = malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);

	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';

	return (dup);
}


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);

	s_len = 0;
	while (s[s_len])
		s_len++;

	if (start >= s_len)
		return (ft_strdup(""));

	if (len > s_len - start)
		len = s_len - start;

	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);

	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';

	return (sub);
}


static int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;

	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*str;
	long			nb;
	int				len;

	nb = n;
	len = count_digits(n);

	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);

	str[len] = '\0';

	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}

	if (nb == 0)
		str[0] = '0';

	while (nb > 0)
	{
		str[--len] = (nb % 10) + '0';
		nb /= 10;
	}

	return (str);
}