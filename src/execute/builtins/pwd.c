#include "minishell.h"

/**
 * Implementation of the pwd builtin, with no option.
 *
 * @param args (not used) Array of arguments passed to pwd.
 * @param minishell (not used) Struct containing global Minishell data.
 * @return EXIT_SUCCESS on success. EXIT_FAILURE on failure.
 * @note The quotes around args are removed during tokenization.
 */
int	do_pwd(char **args, t_minishell *minishell)
{
	int		exit_code;
	char	*path;

	(void)minishell;
	exit_code = error_if_options(args, "pwd");
	if (exit_code)
		return (exit_code);
	path = getcwd(NULL, 0);
	if (!path)
		return (put_error("pwd: getcwd"), EXIT_FAILURE);
	if (printf("%s\n", path) < 0)
	{
		ft_free(&path);
		return (put_error("pwd: printf"), EXIT_FAILURE);
	}
	ft_free(&path);
	return (EXIT_SUCCESS);
}
