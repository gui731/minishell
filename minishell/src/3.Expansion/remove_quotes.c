#include "../../includes/minishell.h"


char	*remove_quotes_from_str(char *s)
{
	char	*new;
	int		i;
	int		j;
	int		in_single;
	int		in_double;

	i = 0;
	j = 0;
	in_single = 0;
	in_double = 0;

	new = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new)
		return (NULL);

	while (s[i])
	{
		if (s[i] == '\'' && !in_double)
		{
			in_single = !in_single;
			i++;
			continue ;
		}
		if (s[i] == '"' && !in_single)
		{
			in_double = !in_double;
			i++;
			continue ;
		}
		new[j++] = s[i++];
	}
	new[j] = '\0';

	return (new);
}

void remove_quotes_from_tokens(t_token *token)
{
    t_token *cur = token;
    char *tmp;

    while (cur)
    {
        if (cur->value)
        {
            tmp = remove_quotes_from_str(cur->value);
            free(cur->value);
            cur->value = tmp;
        }
        cur = cur->next;
    }
}