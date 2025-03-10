#include "minishell.h"

char	*get_destdir(char **args, int args_nb, t_minishell *ms)
{
	char	*dest_dir;

	if (args_nb == 2)
		dest_dir = args[1];
	else
	{
		dest_dir = get_env_value("HOME", ms);
		if (!dest_dir)
			return (put_error("cd: HOME not set"), NULL);
	}
	return (dest_dir);
}

char	*get_current_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (put_error("cd: getcwd"), NULL);
	return (pwd);
}

int	change_directory(char *dest_dir, char **pwd)
{
	if (chdir(dest_dir) == -1)
	{
		ft_free(1, pwd);
		return (put_error("cd: %s", dest_dir), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
