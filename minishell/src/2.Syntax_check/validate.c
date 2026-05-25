#include "../../includes/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	check_unclosed_quotes(char *input)
{
	char	*ptr;
	int		double_quotes;
	int		single_quotes;

	ptr = input;
	double_quotes = 0;
	single_quotes = 0;
	while (*ptr)
	{
		if (*ptr == '"' && single_quotes == 0)
			double_quotes = !double_quotes;
		else if (*ptr == '\'' && double_quotes == 0)
			single_quotes = !single_quotes;
		ptr++;
	}
	if (double_quotes || single_quotes)
	{
		ft_putstr_fd("Syntax error: Unclosed quotes\n", 2);
		return (1);
	}
	return (0);
}

static int	is_redir(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == APPEND || type == HEREDOC);
}

int	validate_tokens(t_token *tokens)
{
	t_token	*cur;

	if (!tokens)
		return (0);
	if (tokens->type == PIPE)
		return (syntax_error("|"));
	cur = tokens;
	while (cur->next)
	{
		if (cur->type == PIPE && cur->next->type == PIPE)
			return (syntax_error("|"));
		if (is_redir(cur->type) && cur->next->type != WORD)
			return (syntax_error(cur->next->value));
		cur = cur->next;
	}
	if (cur->type == PIPE)
		return (syntax_error("|"));
	if (is_redir(cur->type))
		return (syntax_error("newline"));
	return (0);
}
