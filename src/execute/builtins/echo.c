#include "minishell.h"

/**
 * Implementation of the echo builtin.
 * 
 * @param args Array of arguments passed to echo.
 * @return EXIT_SUCCESS on success.
 */
int	do_echo(char **args)
{
	int		n_flag;
	int		i;
	char	*err_msg;

	err_msg = "echo: write error";
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
		if (ft_printf("%s", args[i]) < 0)
			return (builtin_error(err_msg));
		if (args[i + 1])
			if (ft_printf(" ") < 0)
				return (builtin_error(err_msg));
		i++;
	}
	if (!n_flag)
		if (ft_printf("\n") < 0)
			return (builtin_error(err_msg));
	return (EXIT_SUCCESS);
}
