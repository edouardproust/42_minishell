#include "minishell.h"

int	do_cd(char **args)
{
	char	*dir;

	if (args[2])
		return (builtin_error("cd: too many arguments"));
	if (args[1])
		dir = args[1];
	else
	{
		dir = getenv("HOME");
		if (dir == NULL)
			return (builtin_error("cd: HOME not set"));
	}
	if (chdir(dir) == -1)
		return (builtin_error("cd: %s", dir));
	return (EXIT_SUCCESS);
}
