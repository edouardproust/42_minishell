#include "minishell.h"

/**
 * Defines if the option -n is active for this command or not.
 *
 * @param args Array of args (strings) of the current t_cmd
 * @param i Pointer to the args index
 * @return boolean TRUE if option -n is activated. FALSE if not.
 */
t_bool	handle_option_n(char **args, int *i)
{
	t_bool	option_n;

	option_n = FALSE;
	if (args[*i] && ft_strncmp(args[*i], "-n", 3) == 0)
	{
		option_n = TRUE;
		(*i)++;
		while (args[*i] && ft_strncmp(args[*i], "-n", 3) == 0)
			(*i)++;
	}
	return (option_n);
}

/**
 * Implementation of the echo builtin, with option -n.
 *
 * @param args Array of arguments passed to echo.
 * @param minishell (not used) Struct containing global Minishell data.
 * @return EXIT_SUCCESS on success. EXIT_FAILURE on failure.
 * @note The quotes around args are removed during tokenization.
 */
int	do_echo(char **args, t_minishell *minishell)
{
	t_bool	option_n;
	int		i;
	char	*err_msg;

	(void)minishell;
	err_msg = "echo: printf";
	i = 1;
	option_n = handle_option_n(args, &i);
	while (args[i])
	{
		if (printf("%s", args[i]) < 0)
			return (put_error(err_msg), EXIT_FAILURE);
		if (args[i + 1])
		{
			if (printf(" ") < 0)
				return (put_error(err_msg), EXIT_FAILURE);
		}
		i++;
	}
	if (option_n == FALSE)
		if (printf("\n") < 0)
			return (put_error(err_msg), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
