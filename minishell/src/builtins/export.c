#include "../../includes/minishell.h"

static int	append_env_var(t_shell *data, char *new_entry, int count)
{
	char	**new_env;
	int		j;

	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
	{
		free(new_entry);
		return (1);
	}
	j = 0;
	while (j < count)
	{
		new_env[j] = data->envp[j];
		j++;
	}
	new_env[j] = new_entry;
	new_env[j + 1] = NULL;
	free(data->envp);
	data->envp = new_env;
	return (0);
}

int	set_env_var(t_shell *data, char *name, char *value)
{
	char	*new_entry;
	char	*tmp;
	size_t	name_len;
	int		i;

	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (1);
	new_entry = ft_strjoin(tmp, value ? value : "");
	free(tmp);
	if (!new_entry)
		return (1);
	name_len = ft_strlen(name);
	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], name, name_len)
			&& data->envp[i][name_len] == '=')
		{
			free(data->envp[i]);
			data->envp[i] = new_entry;
			return (0);
		}
		i++;
	}
	return (append_env_var(data, new_entry, i));
}

static void	print_export_list(t_shell *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		write(1, "declare -x ", 11);
		write(1, data->envp[i], ft_strlen(data->envp[i]));
		write(1, "\n", 1);
		i++;
	}
}

static int	export_one(t_shell *data, char *arg)
{
	char	*eq;
	char	*name;
	int		ret;

	eq = ft_strchr(arg, '=');
	if (!eq)
		return (0);
	name = ft_substr(arg, 0, eq - arg);
	if (!name)
		return (1);
	ret = set_env_var(data, name, eq + 1);
	free(name);
	return (ret);
}

int	builtin_export(t_cmd *cmd, t_shell *data)
{
	int	i;
	int	ret;

	if (!cmd->argv[1])
	{
		print_export_list(data);
		return (0);
	}
	ret = 0;
	i = 1;
	while (cmd->argv[i])
	{
		if (export_one(data, cmd->argv[i]))
			ret = 1;
		i++;
	}
	return (ret);
}
