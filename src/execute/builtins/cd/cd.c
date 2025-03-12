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
int	do_cd(char **args, t_minishell *ms)
{
	int			exit_code;
	int			args_nb;
	char		*dest_dir;
	char		*pwd;
	char		*new_pwd;

	exit_code = error_if_wrong_args(args, "cd", 2);
	if (exit_code)
		return (exit_code);
	args_nb = ft_matrix_size(args);
	dest_dir = get_destdir(args, args_nb, ms);
	if (!dest_dir)
		return (EXIT_FAILURE);
	if (dest_dir[0] == '\0')
		return (EXIT_SUCCESS);
	pwd = get_current_pwd();
	if (!pwd)
		return (EXIT_FAILURE);
	if (change_directory(dest_dir, &pwd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	new_pwd = get_current_pwd();
	if (!new_pwd)
		return (EXIT_FAILURE);
	if (update_envvars(&pwd, &new_pwd, ms) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (update_envp(ms));
}
