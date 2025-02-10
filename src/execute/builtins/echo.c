#include "minishell.h"

/**
 * Implementation of the echo builtin.
 * 
 * @param args Array of arguments passed to echo.
 * @return EXIT_SUCCESS on success.
 */
int	do_echo(char **args)
{
	int	n_flag;
	int	i;

	n_flag = 0;
	i = 1;
	if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
	{
		n_flag = 1;
		i = 2;
	}
	while (args[i] && ft_strncmp(args[i], "-n", 3) == 0)
		i++;
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!n_flag)
		ft_fprintf(STDOUT_FILENO, "\n");
	return (EXIT_SUCCESS);
}
