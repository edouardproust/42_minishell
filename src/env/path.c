#include "minishell.h"

/**
 * Duplicates executable path if accessible.
 * 
 * @param progpath Executable path to validate.
 * @return Copy of path if accessible, NULL otherwise.
 * @note	- If is a directory: returns NULL, and set errno to EISDIR
 * 			- On access failure: returns NULL, errno set by access().
 *			- On malloc failure: exits process.
 */
static char	*dup_valid_path(char *progpath, t_minishell *minishell)
{
	char	*path;

	if (is_directory(progpath))
		return (set_errno(EISDIR), NULL);
	if (access(progpath, X_OK) == -1)
		return (NULL);
	path = ft_strdup(progpath);
	if (!path)
		exit_minishell(EXIT_FAILURE, minishell, progpath);
	return (path);
}

/**
 * Constructs and validates a relative path (./progname).
 *
 * @param progname Executable name.
 * @return "./progname" if executable, NULL otherwise.
 * @note	- On access failure: returns NULL, errno set by access().
 *			- On malloc failure: exits process.
 */
static char	*get_valid_relpath(char *progname, t_minishell *minishell)
{
	char	*relpath;

	relpath = ft_strjoin("./", progname);
	if (!relpath)
		exit_minishell(EXIT_FAILURE, minishell, progname);
	if (access(relpath, X_OK) == -1)
	{
		ft_free(&relpath);
		return (NULL);
	}
	return (relpath);
}

/**
 * Searches directories for an executable (dir/progname).
 *
 * @param dirnames Directories to search (from PATH).
 * @param progname Executable name.
 * @return Valid path if found and executable, NULL otherwise.
 * @note - On access failure (EACCES): returns NULL, errno preserved.
 *       - If no valid path found: returns NULL, errno set to 0.
 *       - On malloc failure: exits process.
 */
static char	*find_abspath(char **dirnames, char *progname,
	t_minishell *minishell)
{
	char	*abspath_tmp;
	int		i;

	i = 0;
	while (progname[0] != '\0' && dirnames[i] != NULL)
	{
		abspath_tmp = ft_strglue(dirnames[i], "/", progname);
		if (!abspath_tmp)
			exit_minishell(EXIT_FAILURE, minishell, progname);
		if (access(abspath_tmp, X_OK) == 0)
			return (abspath_tmp);
		ft_free(&abspath_tmp);
		if (errno == EACCES)
			return (NULL);
		i++;
	}
	set_errno(0);
	return (NULL);
}

/**
 * Searches PATH directories for an executable.
 *
 * @param envpath_value Colon-separated PATH string.
 * @return Valid path if found, NULL otherwise.
 * @note - On malloc failure (split): exits process.
 *       - Calls find_abspath() for actual search.
 */
char	*find_abspath_in_envvars(char *progname, char *envpath_value,
	t_minishell *minishell)
{
	char	**dirnames;
	char	*path;

	dirnames = ft_split(envpath_value, ':');
	if (!dirnames)
		exit_minishell(EXIT_FAILURE, minishell, progname);
	path = find_abspath(dirnames, progname, minishell);
	ft_free_split(&dirnames);
	return (path);
}

/**
 * Resolves executable path (absolute, relative, or PATH search).
 *
 * @param progname Executable name/path.
 * @return Malloc'd path string (caller must free).
 * @note - On critical errors (malloc): exits process.
 *       - On access/not found errors: exits with E_CMDNOTEXEC/E_CMDNOTFOUND.
 */
char	*get_exec_path(char *progname, t_minishell *minishell)
{
	char	*path;
	char	*envpath_value;

	path = NULL;
	if (is_path (progname))
		path = dup_valid_path(progname, minishell);
	else
	{
		envpath_value = get_env_value("PATH", minishell);
		if (!envpath_value || *envpath_value == '\0')
			path = get_valid_relpath(progname, minishell);
		else
			path = find_abspath_in_envvars(progname, envpath_value, minishell);
	}
	if (!path)
	{
		if (errno == ENOENT)
			exit_minishell(E_CMDNOTFOUND, minishell, progname);
		else if (errno == 0)
			exit_minishell1(E_CMDNOTFOUND, minishell, "%s: command not found",
				progname);
		else
			exit_minishell(E_CMDNOTEXEC, minishell, progname);
	}
	return (path);
}
