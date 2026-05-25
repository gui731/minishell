
#include "../../includes/minishell.h"

static void	reset_expansion_state(int *i, int *in_single, int *in_double)
{
	*i = 0;
	*in_single = 0;
	*in_double = 0;
}

int	process_node(t_token *current, t_shell *data)
{
	int	i;
	int	in_single;
	int	in_double;

	if (!current->value)
		return (1);
	i = 0;
	in_single = 0;
	in_double = 0;
	while (i < (int)ft_strlen(current->value))
	{
		handle_expansion_quotes(current->value[i], &in_single, &in_double);
		if (!in_single && current->value[i] == '$')
		{
			if (!current->value[i + 1])
				break ;
			if (process_env_if_needed(current, &i, data))
				reset_expansion_state(&i, &in_single, &in_double);
		}
		i++;
	}
	return (0);
}

int	expand_each_token(t_shell *data, t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (!current->value)
			return (1);
		if (process_node(current, data))
			return (1);
		current = current->next;
	}
	return (0);
}

int	expander_tokens(t_shell *data, t_token *token)
{
	if (expand_each_token(data, token))
		return (1);
	
	remove_quotes_from_tokens(token);
	return (0);
} 