#include "../includes/minishell.h"

static char	*read_input(void)
{
	if (isatty(STDIN_FILENO))
		return (readline("minishell$ "));
	return (get_next_line(STDIN_FILENO));
}

static int	check_signal_state(t_shell *data)
{
	if (g_signo == 130 || g_signo == 131)
	{
		data->last_exit_status = g_signo;
		g_signo = 0;
	}
	if (!data->input[0])
	{
		free(data->input);
		data->input = NULL;
		return (1);
	}
	add_history(data->input);
	return (0);
}

static int	parse_input(t_shell *data)
{
	if (check_unclosed_quotes(data->input))
		return (data->last_exit_status = 2, 1);
	data->tokens = tokenize(data->input);
	if (!data->tokens)
		return (1);
	if (validate_tokens(data->tokens))
		return (data->last_exit_status = 2, 1);
	if (expander_tokens(data, data->tokens))
		return (1);
	data->cmds = parser(data->tokens);
	free_tokens(data->tokens);
	data->tokens = NULL;
	return (0);
}

static void	process_line(t_shell *data)
{
	if (check_signal_state(data))
		return ;
	if (parse_input(data))
	{
		free_tokens(data->tokens);
		data->tokens = NULL;
		free(data->input);
		data->input = NULL;
		return ;
	}
	if (data->cmds)
	{
		execute_commands(data->cmds, data);
		free_cmds(data->cmds);
		data->cmds = NULL;
	}
	free(data->input);
	data->input = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*data;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_shell));
	if (!data)
		return (1);
	init_shell(data, envp);
	while (1)
	{
		setup_signal_handlers();
		data->input = read_input();
		if (handle_eof(data->input))
			break ;
		process_line(data);
	}
	cleanup_shell(data);
	return (0);
}
