#include "../../includes/minishell.h"

void	heredoc_sigint(int sig)
{
	(void)sig;
	g_signo = SIGINT;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	setup_heredoc_signals(void)
{
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}

