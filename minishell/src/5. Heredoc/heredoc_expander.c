#include "../../includes/minishell.h"

char	*expand_heredoc_content(char *content, t_shell *data)
{
	char	*result;
	char	*tmp;
	int		i;

	if (!content)
		return (NULL);
	result = ft_strdup(content);
	if (!result)
		return (NULL);
	i = 0;
	while (result[i])
	{
		if (result[i] == '$' && result[i + 1])
		{
			tmp = replace_env_var(data, result, i);
			if (!tmp)
			{
				free(result);
				return (NULL);
			}
            free(result);
			result = tmp;
			while (result[i] && result[i] != '$')
				i++;
		}
		else
			i++;
	}
	return (result);
}
