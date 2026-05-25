#include "../../includes/minishell.h"

int	builtin_env(t_shell *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		write(1, data->envp[i], ft_strlen(data->envp[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
