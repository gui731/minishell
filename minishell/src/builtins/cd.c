#include "../../includes/minishell.h"

static void	update_pwd(t_shell *data, char *old_pwd)
{
	char	*new_pwd;

	if (old_pwd)
	{
		set_env_var(data, "OLDPWD", old_pwd);
		free(old_pwd);
	}
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		set_env_var(data, "PWD", new_pwd);
		free(new_pwd);
	}
}

static char	*resolve_target(t_cmd *cmd, t_shell *data, int *print_target)
{
	char	*target;
	char	*key;

	if (!cmd->argv[1] || ft_strcmp(cmd->argv[1], "-") == 0)
	{
		if (cmd->argv[1])
			key = "OLDPWD";
		else
			key = "HOME";
		target = get_env_value(data, key);
		if (!target || target[0] == '\0')
		{
			free(target);
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(key, 2);
			ft_putstr_fd(" not set\n", 2);
			return (NULL);
		}
		if (cmd->argv[1])
			*print_target = 1;
		return (target);
	}
	return (ft_strdup(cmd->argv[1]));
}

int	builtin_cd(t_cmd *cmd, t_shell *data)
{
	char	*target;
	char	*old_pwd;
	int		print_target;

	print_target = 0;
	target = resolve_target(cmd, data, &print_target);
	if (!target)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (chdir(target) != 0)
	{
		perror("cd");
		free(target);
		free(old_pwd);
		return (1);
	}
	if (print_target)
	{
		ft_putstr_fd(target, 1);
		ft_putstr_fd("\n", 1);
	}
	free(target);
	update_pwd(data, old_pwd);
	return (0);
}
