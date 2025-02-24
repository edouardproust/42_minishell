#include "minishell.h"

/**
 * Check if the string is a valid number.
 */
static t_bool	is_number(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

/**
 * Implementation of the exit builtin, with no option.
 * 
 * @param args Array of arguments passed to exit.
 * @param minishell Struct containing global Minishell data.
 * @return EXIT_SUCCESS on success. EXIT_FAILURE on failure.
 * @TODO The quotes around args are removed during tokenization.
 * eg. `$"exit" '1234' "'"test"'"` -> args: {"exit","1234", "\'test\'"}
 * @TODO line `minishell->exit_code = minishell->exit_code;`:
 * 	check at school: minishell->exit_code or EXIT_SUCCESS ?
 */
int	do_exit(char **args, t_minishell *minishell)
{
	ft_printf("exit\n");
	if (ft_matrix_size(args) == 1)
		minishell->exit_code = minishell->exit_code;
	else if (is_number(args[1]))
		minishell->exit_code = ft_atoi(args[1]);
	else
	{
		minishell->exit_code = E_CMDWRONGARG;
		put_error("exit: %s: numeric argument required", args[1]);
	}
	exit_minishell(minishell->exit_code, minishell, NULL);
	return (EXIT_SUCCESS);
}
