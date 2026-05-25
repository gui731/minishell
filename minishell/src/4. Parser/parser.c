#include "../../includes/minishell.h"

static int	handle_redir(t_token **tokens, t_cmd *cur, t_token_type type)
{
	*tokens = (*tokens)->next;
	if (!*tokens)
		return (1);
	if (type == REDIR_IN)
	{
		free(cur->infile);
		cur->infile = ft_strdup((*tokens)->value);
	}
	else if (type == REDIR_OUT || type == APPEND)
	{
		free(cur->outfile);
		cur->outfile = ft_strdup((*tokens)->value);
		cur->append = (type == APPEND);
	}
	else if (type == HEREDOC)
	{
		free(cur->heredoc_delim);
		cur->heredoc_delim = ft_strdup((*tokens)->value);
	}
	return (0);
}

static t_cmd	*process_token(t_token **tokens, t_cmd **cmd_list, t_cmd *cur)
{
	if (!cur)
	{
		cur = new_cmd();
		add_cmd(cmd_list, cur);
	}
	if ((*tokens)->type == WORD)
		add_arg(cur, (*tokens)->value);
	else if ((*tokens)->type == PIPE)
	{
		cur = new_cmd();
		add_cmd(cmd_list, cur);
	}
	else if (handle_redir(tokens, cur, (*tokens)->type))
		return (NULL);
	return (cur);
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*current;

	cmd_list = NULL;
	current = NULL;
	while (tokens)
	{
		current = process_token(&tokens, &cmd_list, current);
		if (!current)
			return (free_cmds(cmd_list), NULL);
		tokens = tokens->next;
	}
	return (cmd_list);
}
