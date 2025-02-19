#include "minishell.h"

/**
 * Implementation of the pwd builtin, with no option.
 * 
 * @param args (not used) Array of arguments passed to pwd.
 * @param minishell (not used) Struct containing global Minishell data.
 * @return EXIT_SUCCESS on success. EXIT_FAILURE on failure.
 * @note The quotes around args are removed during tokenization.
 * eg. `$"pwd" 'wrong_arg'` -> args: {"pwd","wrong_arg"} // TODO
 */
int	do_pwd(char **args, t_minishell *minishell)
{
	char	*path;

	(void)args;
	(void)minishell;
	path = getcwd(NULL, 0);
	if (!path)
		return (put_error("pwd: getcwd"), EXIT_FAILURE);
	if (ft_printf("%s\n", path) < 0)
	{
		ft_free_ptrs(1, &path);
		return (put_error("pwd: ft_printf"), EXIT_FAILURE);
	}
	ft_free_ptrs(1, &path);
	return (EXIT_SUCCESS);
}
