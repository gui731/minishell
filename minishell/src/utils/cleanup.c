#include "../../includes/minishell.h"

void	cleanup_shell(t_shell *data)
{
	if (!data)
		return ;
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->tokens)
	{
		free_tokens(data->tokens);
		data->tokens = NULL;
	}
	if (data->cmds)
	{
		free_cmds(data->cmds);
		data->cmds = NULL;
	}
	if (data->envp)
	{
		free_env(data->envp);
		data->envp = NULL;
	}
	rl_clear_history();
	free(data);
}
