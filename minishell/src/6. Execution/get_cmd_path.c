#include "../../includes/minishell.h"

int	is_abs_path(char *cmd)
{
	if (!cmd)
		return (0);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
		return (1);
	return (0);
}

static int	handle_abs_lookup(t_cmd *cmd)
{
	if (access(cmd->argv[0], F_OK) == -1)
		return (1);
	if (access(cmd->argv[0], X_OK) == -1)
		return (CMD_NOT_EXECUTABLE);
	free(cmd->full_path);
	cmd->full_path = ft_strdup(cmd->argv[0]);
	if (!cmd->full_path)
		return (1);
	return (0);
}

static int	search_paths(t_cmd *cmd, t_shell *data, char **paths)
{
	int		i;
	int		ret;
	char	*path;

	i = -1;
	while (paths[++i])
	{
		path = join_path_cmd(paths[i], cmd->argv[0]);
		ret = check_access(data, cmd, path);
		if (ret == 0)
			return (free_2d(paths), 0);
		if (ret == CMD_NOT_EXECUTABLE)
			return (free_2d(paths), CMD_NOT_EXECUTABLE);
	}
	free_2d(paths);
	return (1);
}

int	get_cmd_path(t_cmd *cmd, t_shell *data)
{
	char	**paths;

	if (is_abs_path(cmd->argv[0]))
		return (handle_abs_lookup(cmd));
	paths = find_path(data);
	if (!paths)
		return (2);
	return (search_paths(cmd, data, paths));
}
