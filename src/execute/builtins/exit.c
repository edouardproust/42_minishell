#include "minishell.h"

/**
 *  Implementation of the exit builtin, with no option.
 * 
 * @param args Array of arguments passed to exit.
 * @param minishell Struct containing global Minishell data, including the 
 * 	environment variables list (`envvar_lst`) and the environment array (`envp`).
 * @return EXIT_SUCCESS on success. EXIT_FAILURE on failure.
 * @note The quotes around args are removed during tokenization.
 * eg. `$"exit" '1234' "'"test"'"` -> args: {"exit","1234", "\'test\'"} // TODO
 */
static t_bool	is_number(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

int	do_exit(char **args, t_minishell *minishell)
{
	int		exit_code;

	ft_printf("exit\n");
	if (is_number(args[1]))
		exit_code = ft_atoi(args[1]);
	else
	{
		exit_code = 2;
		put_error("exit: %s: numeric argument required", args[1]);
	}
	exit_minishell(exit_code, &minishell, NULL);
	return (EXIT_SUCCESS);
}
