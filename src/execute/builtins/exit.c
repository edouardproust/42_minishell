#include "minishell.h"

int	do_exit(char **args, t_minishell *minishell)
{
	(void)args;
	(void)minishell;
	ft_fprintf(STDERR_FILENO, "[TODO: ft_exit]\n");
	return (EXIT_SUCCESS);
}