#include "minishell.h"

/*
 * Implementation of the env builtin, with no option or argument.
 * 
 * @param args Array of arguments passed to env.
 * @param minishell Struct containing global Minishell data, including the 
 * 	environment variables list (`envvar_lst`) and the environment array (`envp`).
 * @return EXIT_SUCCESS on success. EXIT_FAILURE on failure.
 * @note The quotes around args are removed during tokenization.
 * eg. `$"exit" '1234' "'"test"'"` -> args: {"exit","1234", "\'test\'"} // TODO
 */
int	do_env(char **args, t_minishell *minishell)
{
	t_envvar	*current;

	(void)args;
	current = minishell->envvar_lst;
	while (current)
	{
		if (ft_printf("%s=%s\n", current->name, current->value) < 0)
			return (put_error("env: ft_printf"), EXIT_FAILURE);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
