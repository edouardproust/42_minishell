#include "minishell.h"

/**
 * Implementation of the pwd builtin.
 * 
 * @param args Array of arguments passed to pwd (not used).
 * @return EXIT_SUCCESS on success.
 */
int	do_pwd(char **args)
{
	char	*path;

	(void)args;
	path = getcwd(NULL, 0);
	if (!path)
		return (print_error("pwd: getcwd"), EXIT_FAILURE);
	if (ft_printf("%s\n", path) < 0)
	{
		ft_free_ptrs(1, &path);
		return (print_error("pwd: write error"), EXIT_FAILURE);
	}
	ft_free_ptrs(1, &path);
	return (EXIT_SUCCESS);
}
