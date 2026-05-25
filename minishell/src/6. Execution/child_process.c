#include "../../includes/minishell.h"

static void	setup_child_input(t_cmd *cmd, int prev_fd)
{
	int	in_fd;

	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->heredoc_delim && cmd->heredoc_fd != -1)
	{
		dup2(cmd->heredoc_fd, STDIN_FILENO);
		close(cmd->heredoc_fd);
	}
	if (cmd->infile)
	{
		in_fd = open(cmd->infile, O_RDONLY);
		if (in_fd < 0)
		{
			perror(cmd->infile);
			exit(1);
		}
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
}

void	setup_child(t_cmd *cmd, t_shell *data, int prev_fd, int fd[2])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_child_input(cmd, prev_fd);
	if (cmd->next)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (cmd->outfile)
		handle_output_redir(cmd);
	if (is_builtin(cmd))
		exit(exec_builtin(cmd, data));
	exec_external(cmd, data);
}

void	handle_output_redir(t_cmd *cmd)
{
	int	fd;

	if (cmd->append)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(cmd->outfile);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	print_exec_error(t_cmd *cmd, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->argv[0], 2);
	if (ret == CMD_NOT_EXECUTABLE)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (is_abs_path(cmd->argv[0]))
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
}

void	exec_external(t_cmd *cmd, t_shell *data)
{
	int	ret;

	ret = get_cmd_path(cmd, data);
	if (ret == CMD_NOT_EXECUTABLE)
	{
		print_exec_error(cmd, ret);
		exit(126);
	}
	if (ret != 0)
	{
		print_exec_error(cmd, ret);
		exit(127);
	}
	execve(cmd->full_path, cmd->argv, data->envp);
	perror("execve");
	exit(1);
}
