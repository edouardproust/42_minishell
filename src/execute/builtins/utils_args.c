#include "minishell.h"

t_bool	error_if_options(char **args, char *builtin_name)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '-')
		{
			put_error("%s: %s: invalid option", builtin_name, args[i]);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

t_bool	error_if_wrong_args(char **args, char *builtin_name,
	int max_args_nb)
{
	int	args_nb;

	args_nb = ft_matrix_size(args);
	if (args_nb > max_args_nb)
	{
		put_error("%s: too many arguments", builtin_name);
		return (TRUE);
	}
	return (error_if_options(args, builtin_name));
}