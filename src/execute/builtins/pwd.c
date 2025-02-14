#include "minishell.h"

/**
 * Implementation of the pwd builtin.
 * 
 * @param args Array of arguments passed to pwd (not used).
 * @return EXIT_SUCCESS on success.
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
		return (put_error("pwd: write error"), EXIT_FAILURE);
	}
	ft_free_ptrs(1, &path);
	return (EXIT_SUCCESS);
}
