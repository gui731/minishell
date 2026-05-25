#include "../../includes/minishell.h"

char	**find_path(t_shell *data)
{
	int		i;
	char	**paths;

	i = 0;
	if (!data || !data->envp)
		return (NULL);
	while (data->envp[i] && ft_strncmp(data->envp[i], "PATH=", 5) != 0)
		i++;
	if (!data->envp[i])
		return (NULL);
	paths = ft_split(data->envp[i] + 5, ':');
	if (!paths || !paths[0])
	{
		free_2d(paths);
		return (NULL);
	}
	return (paths);
}

char	*join_path_cmd(char *path, char *cmd)
{
	char	*temp;
	char	*path_with_cmd;

	if (!path || !cmd)
		return (NULL);
	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	path_with_cmd = ft_strjoin(temp, cmd);
	free(temp);
	if (!path_with_cmd)
		return (NULL);
	return (path_with_cmd);
}

int	check_access(t_shell *data, t_cmd *cmd, char *path)
{
	(void)data;
	if (!path)
		return (1);
	if (access(path, F_OK) == -1)
		return (free(path), 1);
	if (access(path, X_OK) == -1)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free(path);
		return (CMD_NOT_EXECUTABLE);
	}
	free(cmd->full_path);
	cmd->full_path = ft_strdup(path);
	free(path);
	if (!cmd->full_path)
		return (1);
	return (0);
}
