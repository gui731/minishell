#include "../../includes/minishell.h"

static int	parse_digits(const char *s, int i, unsigned long long *n)
{
	unsigned long long	d;

	*n = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		d = s[i] - '0';
		if (*n > (18446744073709551615ULL - d) / 10ULL)
			return (0);
		*n = *n * 10ULL + d;
		i++;
	}
	return (1);
}

static int	parse_exit_arg(const char *s, long long *out)
{
	int					i;
	int					sign;
	unsigned long long	n;

	i = 0;
	sign = 1;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	if (!s[i])
		return (0);
	if (!parse_digits(s, i, &n))
		return (0);
	if (sign == 1 && n > 9223372036854775807ULL)
		return (0);
	if (sign == -1 && n > 9223372036854775808ULL)
		return (0);
	if (sign == -1 && n == 9223372036854775808ULL)
		*out = (-9223372036854775807LL - 1);
	else
		*out = (long long)n * sign;
	return (1);
}

static int	exit_error(t_cmd *cmd)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd->argv[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (2);
}

int	builtin_exit(t_cmd *cmd, t_shell *data)
{
	long long	num;
	int			status;

	ft_putstr_fd("exit\n", 2);
	if (!cmd->argv[1])
	{
		status = data->last_exit_status;
		cleanup_shell(data);
		exit(status);
	}
	if (!parse_exit_arg(cmd->argv[1], &num))
	{
		status = exit_error(cmd);
		cleanup_shell(data);
		exit(status);
	}
	if (cmd->argv[2])
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), 1);
	status = (int)(num & 0xff);
	cleanup_shell(data);
	exit(status);
}
