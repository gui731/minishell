#include "../../includes/minishell.h"


volatile sig_atomic_t	g_signo;


void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signo = 130;
}

int	handle_eof(char *input)
{
	if (input == NULL)
	{
		write(1, "exit\n", 5);
		return (1);
	}
	return (0);
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
} 