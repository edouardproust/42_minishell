#include "minishell.h"

/**
 * Implementation of the unset builtin, with no options.
 *
 * @param args Array of arguments passed to unset.
 * @param minishell Struct containing global Minishell data, including the
 * 	environment variables list (`envvar_lst`) and the environment array (`envp`).
 * @return EXIT_SUCCESS on success. EXIT_FAILURE on failure.
 * @note The quotes around args are removed during tokenization.
 */
int	do_unset(char **args, t_minishell *minishell)
{
	int			exit_code;
	int			i;
	t_envvar	*found_node;

	exit_code = error_if_options(args, "unset");
	if (exit_code)
		return (exit_code);
	if (ft_matrix_size(args) == 1)
		return (EXIT_SUCCESS);
	i = 1;
	while (args[i])
	{
		found_node = envvar_findbyname(minishell->envvar_lst, args[i]);
		if (found_node)
			envvar_deleteone(&minishell->envvar_lst, found_node);
		i++;
	}
	return (update_envp(minishell));
}
