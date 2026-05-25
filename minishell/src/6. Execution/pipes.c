#include "../../includes/minishell.h"

typedef struct s_pipe_ctx
{
	int		fd[2];
	int		prev_fd;
	pid_t	last_pid;
}	t_pipe_ctx;

static int	fork_one_cmd(t_cmd *cmd, t_shell *data, t_pipe_ctx *ctx)
{
	pid_t	pid;

	if (cmd->next && pipe(ctx->fd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
	{
		if (cmd->next)
		{
			close(ctx->fd[0]);
			close(ctx->fd[1]);
		}
		return (perror("fork"), -1);
	}
	if (pid == 0)
		setup_child(cmd, data, ctx->prev_fd, ctx->fd);
	ctx->last_pid = pid;
	if (ctx->prev_fd != -1)
		close(ctx->prev_fd);
	if (cmd->next)
		(close(ctx->fd[1]), ctx->prev_fd = ctx->fd[0]);
	else
		ctx->prev_fd = -1;
	return (0);
}

static void	wait_pipeline(pid_t last_pid, t_shell *data)
{
	int	status;

	if (last_pid != -1)
	{
		waitpid(last_pid, &status, 0);
		if (WIFEXITED(status))
			data->last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			data->last_exit_status = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
			if (WTERMSIG(status) == SIGQUIT)
				ft_putstr_fd("Quit (core dumped)\n", 2);
		}
	}
	while (wait(NULL) > 0)
		;
}

void	execute_pipe(t_cmd *cmd, t_shell *data)
{
	t_pipe_ctx	ctx;

	ctx.prev_fd = -1;
	ctx.last_pid = -1;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (cmd)
	{
		if (fork_one_cmd(cmd, data, &ctx) == -1)
		{
			if (ctx.prev_fd != -1)
				close(ctx.prev_fd);
			break ;
		}
		cmd = cmd->next;
	}
	wait_pipeline(ctx.last_pid, data);
	setup_signal_handlers();
}
