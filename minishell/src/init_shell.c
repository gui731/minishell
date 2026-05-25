#include "../includes/minishell.h"


void	init_data(t_shell *data)
{
	
	data->last_exit_status = 0;
	data->envp = NULL;
	data->stop = 0;
	data->cmds = NULL;
	data->tokens = NULL;
	data->input = NULL;
}

void	free_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

static int	copy_env(t_shell *data, char **envp, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		data->envp[i] = ft_strdup(envp[i]);
		if (!data->envp[i])
		{
			while (--i >= 0)
				free(data->envp[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

void	get_env(t_shell *data, char **envp)
{
	int		size;

	size = 0;
	while (envp[size])
		size++;
	data->envp = malloc(sizeof(char *) * (size + 1));
	if (!data->envp)
		return ;
	if (!copy_env(data, envp, size))
	{
		free(data->envp);
		data->envp = NULL;
		return ;
	}
	data->envp[size] = NULL;
}

void	init_shell(t_shell *data, char **envp)
{
	init_data(data);
	get_env(data, envp);
}