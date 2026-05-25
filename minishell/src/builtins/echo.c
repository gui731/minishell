#include "../../includes/minishell.h"

static int	is_n_flag(char *s)
{
	int	j;

	if (s[0] != '-' || !s[1])
		return (0);
	j = 1;
	while (s[j] == 'n')
		j++;
	if (s[j] != '\0')
		return (0);
	return (1);
}

int	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (cmd->argv[i] && is_n_flag(cmd->argv[i]))
	{
		newline = 0;
		i++;
	}
	while (cmd->argv[i])
	{
		write(1, cmd->argv[i], ft_strlen(cmd->argv[i]));
		if (cmd->argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
