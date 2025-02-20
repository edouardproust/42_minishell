#include "minishell.h"

/**
 * Get the list of directories containing executables.
 * 
 * @param minishell Struct containing global Minishell data, including the 
 * 	environment variables list (`envvar_lst`) to search into.
 * @return An array of directories (strings)
 * @note The list is null-terminated.
 */
static char	**split_env_path(t_minishell *minishell)
{
	char	*path_val;

	path_val = get_env_value("PATH", minishell);
	if (path_val == NULL)
		return (set_errno(ENOENT), NULL);
	return (ft_split(path_val, ':'));
}

/**
 * Duplicate the executable absolute path if it is accessible.
 * 
 * @param progpath The executable absolute path
 * @return A copy of the absolute path if accessible, NULL otherwise.
 */
static char	*check_duplicate_abspath(char *progpath)
{
	if (access(progpath, X_OK) == -1)
		return (NULL);
	return (ft_strdup(progpath));
}

/**
 * Find the absolute path for the given executable name, in the list of
 * directories containing executables.
 * 
 * @param dirnames Array of directories (strings) containing executables
 * @param progname Name of the executable
 * @return The asbolute path of the executable. NULL in case of
 *  string join or path access failure, or not found executable.
 * @note Set errno to ENOENT in case of failure
 */
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

/**
 * Get the absolute execution path for the given executable name.
 * 
 * @param progname Name of the executable
 * @param minishell Struct containing global Minishell data, including the 
 * 	environment variables list (`envvar_lst`). This list contains the PATH var. 
 * @return The absolute path of the executable. NULL in case it is not found
 *  or an error occured during the search.
 */
char	*get_exec_path(char *progname, t_minishell *minishell)
{
	char	*abspath;
	char	**dirnames;

	if (progname[0] == '/')
	{
		abspath = check_duplicate_abspath(progname);
		if (abspath == NULL)
			exit_minishell(E_CMDNOTEXEC, &minishell, progname);
	}
	else
	{
		dirnames = split_env_path(minishell);
		if (dirnames == NULL)
			exit_minishell(E_CMDNOTFOUND, &minishell, progname);
		abspath = find_abspath(dirnames, progname);
		ft_free_split(&dirnames);
		if (abspath == NULL)
			exit_minishell(E_CMDNOTFOUND, &minishell, progname);
	}
	return (abspath);
}
