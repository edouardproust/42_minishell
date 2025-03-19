#include "minishell.h"

int	error_if_options(char **args, char *builtin_name)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '-')
		{
			put_error2("%s: -%s: bad option", builtin_name,
				char_to_str(args[i][1]));
			return (E_CMDWRONGARG);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	error_if_wrong_args(char **args, char *builtin_name,
	int max_args_nb)
{
	int	args_nb;

	args_nb = ft_matrix_size(args);
	if (args_nb > max_args_nb)
	{
		put_error1("%s: too many arguments", builtin_name);
		return (EXIT_FAILURE);
	}
	return (error_if_options(args, builtin_name));
}
