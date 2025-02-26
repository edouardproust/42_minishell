#include "minishell.h"

/**
 * Checks if a string represents a relative or absolute path.
 * 
 * The strings represents a path:
 * - if it start by: /, ./ or ../
 * - or if it contains a / anywhere
 * 
 * @param s The string to check. If `NULL` or empty, returns `FALSE`.
 * @return t_bool `TRUE` if the string represents an path..
 */
t_bool	is_path(char *s)
{
	if (!s || s[0] == '\0')
		return (FALSE);
	if ((s[0] == '.' && s[1] == '/')
		|| (s[0] == '.' && s[1] == '.' && s[2] == '/'))
		return (TRUE);
	if (s[0] == '/')
		return (TRUE);
	if (ft_strchr(s, '/') != NULL)
		return (TRUE);
	return (FALSE);
}

/**
 * Checks if a path matches with an existing directory.
 * 
 * @param s The path to check. If `NULL` or empty, returns `FALSE`.
 * @return t_bool `TRUE` if the path is a valid directory.
 */
t_bool	is_directory(char *path)
{
	struct stat	path_stat;
	int			res;

	if (!path || path[0] == '\0')
		return (FALSE);
	res = stat(path, &path_stat);
	if (res == 0 && S_ISDIR(path_stat.st_mode))
		return (TRUE);
	return (FALSE);
}

/**
 * Get the value of an environment variable from its name.
 * 
 * This function is searching through the member
 * t_envvar_lst of t_minishell.
 * 
 * @param var_name Name of the searched environment variable
 * @param minishell Struct containing global Minishell data, including the 
 * 	environment variables list (`envvar_lst`).
 * @return The value if node t_envvar node found. NULL otherwise.
 */
char	*get_env_value(char *var_name, t_minishell *minishell)
{
	t_envvar	*var;

	var = envvar_findbyname(minishell->envvar_lst, var_name);
	if (!var)
		return (NULL);
	return (var->value);
}

/**
 * Count the number of nodes in a t_envvar list.
 * 
 * @param head Head node of the list
 * @return Count of nodes in the list.
 */
static int	envvar_lstsize(t_envvar *head)
{
	int			count;
	t_envvar	*current;

	if (!head)
		return (0);
	current = head;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/**
 * Parse back minishell->envvar_lst into an array of strings (null-terminated)
 * and store it in minishell->envp.
 * 
 * @param minishell Struct containing global Minishell data, including the 
 * 	environment variables list (`envvar_lst`) and the environment array (`envp`).
 * @return EXIT_SUCCESS on success. EXIT_FAILURE otherwise.
 */
int	update_envp(t_minishell *minishell)
{
	t_envvar	*current;
	char		**envp;
	int			i;

	ft_free_split(&minishell->envp);
	current = minishell->envvar_lst;
	envp = malloc(sizeof(char *) * (envvar_lstsize(current) + 1));
	if (!envp)
		return (EXIT_FAILURE);
	i = 0;
	while (current)
	{
		envp[i] = ft_strglue(current->name, "=", current->value);
		if (!envp[i])
			return (ft_free_splitn(&envp, i), EXIT_FAILURE);
		current = current->next;
		i++;
	}
	envp[i] = NULL;
	minishell->envp = envp;
	return (EXIT_SUCCESS);
}
