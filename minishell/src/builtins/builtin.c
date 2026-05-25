#include "../../includes/minishell.h"

int is_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	return (
		ft_strcmp(cmd->argv[0], "echo") == 0 ||
		ft_strcmp(cmd->argv[0], "cd") == 0 ||
		ft_strcmp(cmd->argv[0], "pwd") == 0 ||
		ft_strcmp(cmd->argv[0], "env") == 0 ||
		ft_strcmp(cmd->argv[0], "export") == 0 ||
		ft_strcmp(cmd->argv[0], "unset") == 0 ||
		ft_strcmp(cmd->argv[0], "exit") == 0
	);
}

int exec_builtin(t_cmd *cmd, t_shell *data)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (builtin_echo(cmd));
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (builtin_cd(cmd, data));
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (builtin_env(data));
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (builtin_export(cmd, data));
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (builtin_unset(cmd, data));
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (builtin_exit(cmd, data));
	return (1);
}
