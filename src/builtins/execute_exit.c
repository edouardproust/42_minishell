#include "minishell.h"

int	execute_exit(char **args)
{
	(void)args;
	ft_fprintf(STDERR_FILENO, "[TODO: ft_exit]\n");
	return (EXIT_SUCCESS);
}
