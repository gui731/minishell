#include "../../includes/minishell.h"

int	create_pipe_and_fork(int pipe_fd[2], pid_t *pid)
{
	if (pipe(pipe_fd) == -1)
		return (-1);
	*pid = fork();
	if (*pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	return (0);
}

void	write_to_pipe(t_cmd *cmd, int *pipe_fd, t_shell *data)
{
	char	*expanded;

	if (cmd->heredoc_expand)
	{
		expanded = expand_heredoc_content(cmd->heredoc_input, data);
		if (expanded)
		{
			write(pipe_fd[1], expanded, ft_strlen(expanded));
			write(pipe_fd[1], "\n", 1);
			free(expanded);
		}
	}
	else
	{
		write(pipe_fd[1], cmd->heredoc_input, ft_strlen(cmd->heredoc_input));
		write(pipe_fd[1], "\n", 1);
	}
}

int	handle_heredoc_input(t_cmd *cmd, int pipe_fd[2], t_shell *data)
{
	while (1)
	{
		cmd->heredoc_input = readline("> ");
		if (!cmd->heredoc_input)
			return (1);
		if (ft_strcmp(cmd->heredoc_input, cmd->heredoc_delim) == 0)
		{
			free(cmd->heredoc_input);
			cmd->heredoc_input = NULL;
			break ;
		}
		write_to_pipe(cmd, pipe_fd, data);
		free(cmd->heredoc_input);
		cmd->heredoc_input = NULL;
	}
	return (0);
}

int	handle_parent_process(int pipe_fd[2], t_shell *data, int *status)
{
	signal(SIGINT, SIG_IGN);
	wait(status);
	signal(SIGINT, SIG_DFL);
	close(pipe_fd[1]);
	if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGINT)
	{
		data->last_exit_status = 130;
		data->stop = 1;
		close(pipe_fd[0]);
		return (-1);
	}
	if (WIFEXITED(*status))
	{
		data->last_exit_status = WEXITSTATUS(*status);
		if (data->last_exit_status == 130)
		{
			data->stop = 1;
			close(pipe_fd[0]);
			return (-1);
		}
		return (pipe_fd[0]);
	}
	close(pipe_fd[0]);
	return (-1);
}

int	handle_heredoc(t_cmd *cmd, t_shell *data)
{
	int		pipe_fd[2];
	int		status;
	pid_t	pid;

	if (create_pipe_and_fork(pipe_fd, &pid) == -1)
		return (-1);
	if (pid == 0)
	{
		setup_heredoc_signals();
		close(pipe_fd[0]);
		if (handle_heredoc_input(cmd, pipe_fd, data))
		{
			close(pipe_fd[1]);
			if (g_signo == SIGINT)
				exit(128 + SIGINT);
			else
				exit(0);
		}
		close(pipe_fd[1]);
		exit(0);
	}
	else
		return (handle_parent_process(pipe_fd, data, &status));
}
