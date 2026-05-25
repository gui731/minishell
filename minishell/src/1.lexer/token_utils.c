#include "../../includes/minishell.h"

char	*extract_word(char *s, int start, int end)
{
	int		len;
	char	*word;
	int		i;

	len = end - start;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

void	handle_quotes(char *s, int *i)
{
	char	quote;

	quote = s[*i];
	(*i)++;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	if (s[*i] == quote)
		(*i)++;
}

void	skip_spaces(char *s, int *i)
{
	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
