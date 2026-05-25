#include "../../includes/minishell.h"
static int var_match(char *env, char *key)
{
    int i = 0;

    while (key[i] && env[i] && key[i] == env[i])
        i++;

    return (key[i] == '\0' && env[i] == '=');
}
static void	unset_one(char **envp, char *key)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		if (var_match(envp[i], key))
		{
			free(envp[i]);
			j = i;
			while (envp[j])
			{
				envp[j] = envp[j + 1];
				j++;
			}
			return ;
		}
		i++;
	}
}

int	builtin_unset(t_cmd *cmd, t_shell *data)
{
	int	i;

	if (!cmd->argv[1])
		return (0);
	i = 1;
	while (cmd->argv[i])
	{
		unset_one(data->envp, cmd->argv[i]);
		i++;
	}
	return (0);
}