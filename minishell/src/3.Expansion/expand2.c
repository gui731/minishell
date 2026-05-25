#include "../../includes/minishell.h"

void	handle_expansion_quotes(char c, int *in_single, int *in_double)
{
	if (c == '\'' && !(*in_double))
		*in_single = !*in_single;
	else if (c == '"' && !(*in_single))
		*in_double = !*in_double;
}


char	*replace_env_var(t_shell *data, char *content, int i)
{
	char	*var;
	char	*env;
	char	*before_var;
	char	*after_var;

	var = separate_parts(content, i, &after_var);
	if (!var)
		return (NULL);
	env = get_env_value(data, var);
	free(var);
	if (!env)
		return (free(after_var), NULL);
	before_var = ft_substr(content, 0, i);
	if (!before_var)
		return (free(env), free(after_var), NULL);
	return (build_result(before_var, env, after_var));
}

int	process_env_var(t_token *current, int *i,  t_shell *data)
{
	char	*new_content;

	new_content = replace_env_var(data, current->value, *i);
	if (!new_content)
		return (1);
	free(current->value); 
	current->value = new_content;
	return (0);
}

int	process_env_if_needed(t_token *current, int *i, t_shell *data)
{

	if (current->value[*i + 1] == '?' || ft_isalnum(current->value[*i + 1])
		|| current->value[*i + 1] == '_')
	{
		if (process_env_var(current, i, data))
			return (1);
	}
	else if (current->value[*i + 1] == '!'
		|| current->value[*i + 1] == '#')
	{
		ft_putstr_fd("minishell: invalid input\n", 2);
		return (1);
	}
	return (0);
}