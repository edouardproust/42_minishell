#include "minishell.h"

/**
 * Implementation of the cd builtin, with only a relative or absolute path.
 * 
 * @param args Array of arguments passed to cd.
 * @param minishell Struct containing global Minishell data, including the 
 * 	environment variables list (`envvar_lst`) and the environment array (`envp`).
 * @return EXIT_SUCCESS on success. EXIT_FAILURE on failure.
 * @note The quotes around args are removed during tokenization phase.
 */
int	do_cd(char **args, t_minishell *minishell)
{
	int			args_nb;
	char		*dir;

	args_nb = ft_matrix_size(args);
	if (args_nb > 2)
		return (put_error("cd: too many arguments"), EXIT_FAILURE);
	if (args_nb == 2)
		dir = args[1];
	else
	{
		dir = get_env_value("HOME", minishell);
		if (!dir)
			return (put_error("cd: HOME not set"), EXIT_FAILURE);
	}
	if (dir[0] == '\0')
		return (EXIT_SUCCESS);
	if (chdir(dir) == -1)
		return (put_error("cd: %s", dir), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
