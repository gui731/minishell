#include "../../includes/minishell.h"
// exemplo comnina isto tudo numa depois de expandir -> "hello $USER world"
char	*build_result(char *before, char *env, char *after)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(before, env);
	free(before);
	free(env);
	if (!tmp)
	{
		free(after);
		return (NULL);
	}
	res = ft_strjoin(tmp, after);
	free(tmp);
	free(after);
	return (res);
}

char	*extract_env_name(char *s)
{
	int	i;

	if (!s || s[0] != '$')
		return (NULL);

	i = 1;

	if (s[i] == '?')
		return (ft_strdup("?"));
	if (s[i] == '0')
		return (ft_strdup("0"));
	if (s[i] == '!')
		return (ft_strdup("!"));

	if (!ft_isalpha(s[i]) && s[i] != '_')
		return (NULL);

	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;

	return (ft_substr(s, 1, i - 1));
}

char	*get_env_value(t_shell *data, char *var_name)
{
	int		i;
	char	*eq_pos;
	size_t	name_len;

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(data->last_exit_status));
	if (ft_strcmp(var_name, "0") == 0)
		return (ft_strdup("minishell"));
	if (ft_strcmp(var_name, "!") == 0 || ft_isdigit(var_name[0]))
		return (ft_strdup(""));
	name_len = ft_strlen(var_name);
	i = 0;
	while (data->envp[i])
	{
		eq_pos = ft_strchr(data->envp[i], '=');
		if (eq_pos && (size_t)(eq_pos - data->envp[i]) == name_len
			&& !ft_strncmp(data->envp[i], var_name, name_len))
			return (ft_strdup(eq_pos + 1));
		i++;
	}
	return (ft_strdup(""));
}

char	*separate_parts(char *content, int i, char **after)
{
	char	*var_name;
	size_t	len;

	var_name = extract_env_name(content + i);
	if (!var_name)
		return (NULL);
	len = ft_strlen(var_name);
	*after = ft_strdup(content + i + len + 1);
	if (!*after)
	{
		free(var_name);
		return (NULL);
	}
	return (var_name);
}