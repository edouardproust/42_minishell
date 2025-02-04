#include "minishell.h"

static char	**split_env_path(void)
{
	char	*path_env;

	path_env = getenv("PATH");
	if (path_env == NULL)
	{
		errno = ENOENT;
		return (NULL);
	}
	return (ft_split(path_env, ':'));
}

static char	*join_abspath(char *dir, char *progname, char **dirnames)
{
	char	*dir_tmp;
	char	*path;

	dir_tmp = ft_strjoin(dir, "/");
	if (dir_tmp == NULL)
	{
		ft_free_split(&dirnames);
		return (NULL);
	}
	path = ft_strjoin(dir_tmp, progname);
	if (path == NULL)
	{
		ft_free_ptrs(1, &dir_tmp);
		ft_free_split(&dirnames);
		return (NULL);
	}
	ft_free_ptrs(1, &dir_tmp);
	return (path);
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
		abspath_tmp = join_abspath(dirnames[i], progname, dirnames);
		if (abspath_tmp == NULL)
		{
			errno = ENOENT; // TODO adapt to errcode in bash
			return (NULL);
		}
		if (access(abspath_tmp, X_OK) == 0)
			return (abspath_tmp);
		ft_free_ptrs(1, &abspath_tmp);
		i++;
	}
	errno = ENOENT;
	return (NULL);
}

char	*get_exec_path(char *progname, t_cmd **cmd_lst)
{
	char	*abspath;
	char	**dirnames;

	if (progname[0] == '/')
	{
		abspath = check_duplicate_abspath(progname);
		if (abspath == NULL)
			exit_exec(cmd_lst, progname);
	}
	else
	{
		dirnames = split_env_path();
		if (dirnames == NULL)
			exit_exec(cmd_lst, progname);
		abspath = find_abspath(dirnames, progname);
		ft_free_split(&dirnames);
		if (abspath == NULL)
			exit_exec(cmd_lst, progname);
	}
	return (abspath);
}
