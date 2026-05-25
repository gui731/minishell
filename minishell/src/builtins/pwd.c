#include "../../includes/minishell.h"

int	builtin_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
	}
	return (0);
}
