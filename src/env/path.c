#include "minishell.h"

static char	**split_env_path(void)
{
	char	*path_env;

	path_env = getenv("PATH");
	if (path_env == NULL)
		return (set_errno(ENOENT), NULL);
	return (ft_split(path_env, ':'));
}

static char	*check_duplicate_abspath(char *progpath)
{
	if (access(progpath, X_OK) == -1)
		return (NULL);
	return (ft_strdup(progpath));
}

static char	*find_abspath(char **dirnames, char *progname)
{
	char	*abspath_tmp;
	int		i;

	i = 0;
	while (dirnames[i] != NULL)
	{
		abspath_tmp = ft_strglue(dirnames[i], "/", progname);
		if (abspath_tmp == NULL)
		{
			ft_free_ptrs(1, &abspath_tmp);
			return (set_errno(ENOENT), NULL);
		}
		if (access(abspath_tmp, X_OK) == 0)
			return (abspath_tmp);
		ft_free_ptrs(1, &abspath_tmp);
		i++;
	}
	errno = ENOENT;
	return (NULL);
}

char	*get_exec_path(char *progname, t_minishell **minishell)
{
	char	*abspath;
	char	**dirnames;

	if (progname[0] == '/')
	{
		abspath = check_duplicate_abspath(progname);
		if (abspath == NULL)
			exit_minishell(E_CMDNOTEXEC, minishell, progname);
	}
	else
	{
		dirnames = split_env_path();
		if (dirnames == NULL)
			exit_minishell(E_CMDNOTFOUND, minishell, progname);
		abspath = find_abspath(dirnames, progname);
		ft_free_split(&dirnames);
		if (abspath == NULL)
			exit_minishell(E_CMDNOTFOUND, minishell, progname);
	}
	return (abspath);
}
