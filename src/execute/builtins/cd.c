#include "minishell.h"

int	do_cd(char **args)
{
	char	*dir;

	if (args[2])
		return (put_error("cd: too many arguments"), EXIT_FAILURE);
	if (args[1])
		dir = args[1];
	else
	{
		dir = getenv("HOME");
		if (dir == NULL)
			return (put_error("cd: HOME not set"), EXIT_FAILURE);
	}
	if (chdir(dir) == -1)
		return (put_error("cd: %s", dir), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
