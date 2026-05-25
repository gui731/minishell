#include "../../includes/minishell.h"

static void	handle_redir_in(char *input, int *i, t_token **tokens)
{
	if (input[*i + 1] == '<')
	{
		add_token(tokens, new_token(ft_strdup("<<"), HEREDOC));
		(*i) += 2;
	}
	else
	{
		add_token(tokens, new_token(ft_strdup("<"), REDIR_IN));
		(*i)++;
	}
}

static void	handle_redir_out(char *input, int *i, t_token **tokens)
{
	if (input[*i + 1] == '>')
	{
		add_token(tokens, new_token(ft_strdup(">>"), APPEND));
		(*i) += 2;
	}
	else
	{
		add_token(tokens, new_token(ft_strdup(">"), REDIR_OUT));
		(*i)++;
	}
}

void	handle_operator(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '<')
		handle_redir_in(input, i, tokens);
	else if (input[*i] == '>')
		handle_redir_out(input, i, tokens);
	else if (input[*i] == '|')
	{
		add_token(tokens, new_token(ft_strdup("|"), PIPE));
		(*i)++;
	}
}

void	handle_word(char *input, int *i, t_token **tokens)
{
	int		start;
	char	*word;

	start = *i;
	while (input[*i] && !is_operator(input[*i])
		&& input[*i] != ' ' && input[*i] != '\t')
	{
		if (input[*i] == '\'' || input[*i] == '"')
			handle_quotes(input, i);
		else
			(*i)++;
	}
	word = extract_word(input, start, *i);
	add_token(tokens, new_token(word, WORD));
}

t_token	*tokenize(char *input)
{
	int		i;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	while (input[i])
	{
		skip_spaces(input, &i);
		if (!input[i])
			break ;
		if (is_operator(input[i]))
			handle_operator(input, &i, &tokens);
		else
			handle_word(input, &i, &tokens);
	}
	return (tokens);
}
