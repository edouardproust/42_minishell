#include "minishell.h"

/**
 * Duplicate and return the identifier part of a envp variable string
 * "identifier=value".
 * 
 * If the string is not a valid envp var string, the whole string is
 * duplicated.
 * 
 * @param var The envp variable string. Must not be NULL.
 * @return A newly allocated string containing the identifier part (if valid)
 * or the whole string. Returns NULL if allocation fails.
 * @note The caller is responsible for freeing the returned string.
 */
char	*get_envp_var_identifier(char *var)
{
	int		eq_index;
	char	*identifier;

	eq_index = ft_strchri(var, '=');
	if (eq_index > 0 && is_valid_envp_var(var))
		identifier = ft_substr(var, 0, eq_index);
	else
		identifier = ft_strdup(var);
	return (identifier);
}

/**
 * Get the value part of an envp variable string "identifier=value".
 * 
 * If the string is not a valid envp var string, allocate and return an
 * empty string.
 * 
 * @param var The envp variable string. Must not be NULL.
 * @return A newly allocated string containing the value part (if valid)
 * or an empty string. Returns NULL if allocation fails.
 * @note The caller is responsible for freeing the returned string.
 */
char	*get_envp_var_value(char *var)
{
	int		eq_index;
	char	*value;

	eq_index = ft_strchri(var, '=');
	if (eq_index > 0 && is_valid_envp_var(var))
		value = ft_substr(var, eq_index + 1, ft_strlen(var));
	else
		value = ft_strdup("");
	return (value);
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
