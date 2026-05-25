#include "../../includes/minishell.h"

int	syntax_error(char *msg)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

char    *ft_strjoin(char *s1, char *s2)
{
    char    *new;
    int     i;
    int     j;

    if (!s1 || !s2)
        return (NULL);

    new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!new)
        return (NULL);

    i = 0;
    j = 0;

    while (s1[i])
    {
        new[j] = s1[i];
        i++;
        j++;
    }

    i = 0;
    while (s2[i])
    {
        new[j] = s2[i];
        i++;
        j++;
    }

    new[j] = '\0';
    return (new);
}

int ft_strlen(char *s)
{
    int i;

    if (!s)
        return (0);
    i = 0;
    while (s[i])
        i++;
    return i;
}

void	free_2d(char **str)
{
	int	i;

	if (!str)
		return;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
