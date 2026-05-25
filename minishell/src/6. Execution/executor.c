#include "../../includes/minishell.h"

int	prepare_heredocs(t_cmd *cmd, t_shell *data)
{
	while (cmd)
	{
		if (cmd->heredoc_delim)
		{
			cmd->heredoc_fd = handle_heredoc(cmd, data);
			if (cmd->heredoc_fd == -1 || data->stop)
				return (-1);
		}
		cmd = cmd->next;
	}
	return (0);
}

static int	setup_redir(t_cmd *cmd, int *saved_in, int *saved_out)
{
	int	fd;

	*saved_in = -1;
	*saved_out = -1;
	if (cmd->heredoc_delim && cmd->heredoc_fd != -1)
	{
		*saved_in = dup(STDIN_FILENO);
		dup2(cmd->heredoc_fd, STDIN_FILENO);
		close(cmd->heredoc_fd);
		cmd->heredoc_fd = -1;
	}
	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
			return (perror(cmd->infile), 1);
		if (*saved_in == -1)
			*saved_in = dup(STDIN_FILENO);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->outfile)
	{
		if (cmd->append)
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (perror(cmd->outfile), 1);
		*saved_out = dup(STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

static void	restore_redir(int saved_in, int saved_out)
{
	if (saved_in != -1)
	{
		dup2(saved_in, STDIN_FILENO);
		close(saved_in);
	}
	if (saved_out != -1)
	{
		dup2(saved_out, STDOUT_FILENO);
		close(saved_out);
	}
}

void	execute_commands(t_cmd *cmd, t_shell *data)
{
	int	saved_in;
	int	saved_out;

	data->stop = 0;
	if (prepare_heredocs(cmd, data) == -1)
		return ;
	if (cmd->next == NULL && is_builtin(cmd))
	{
		if (setup_redir(cmd, &saved_in, &saved_out))
		{
			data->last_exit_status = 1;
			restore_redir(saved_in, saved_out);
			return ;
		}
		data->last_exit_status = exec_builtin(cmd, data);
		restore_redir(saved_in, saved_out);
	}
	else
		execute_pipe(cmd, data);
}
