#include "minishell.h"

static char	*extract_name_with_braces(char *start, int *i)
{
	char	*name;

	(*i)++;
	while (start[*i] && start[*i] != '}')
		(*i)++;
	name = ft_substr(start, 1, *i - 1);
	if (start[*i] == '}')
		(*i)++;
	return (name);
}

static char	*extract_name_without_braces(char *start, int *i)
{
	char	*name;

	while (ft_isalnum(start[*i]) || start[*i] == '_')
		(*i)++;
	name = ft_substr(start, 0, *i);
	return (name);
}

/**
 * Extracts the variable name after `$`.
 * 
 * @param start Position after `$` (e.g., `USER` in `$USER`).
 * @return Allocated string containing the variable name.
 */
static char	*extract_var_name(char *start)
{
	int		i;

	i = 0;
	if (start[i] == '}')
		return (extract_name_with_braces(start, &i));
	else
		return (extract_name_without_braces(start, &i));
}

/**
 * Expands a variable starting at `i` and updates the cleaned buffer.
 * 
 * @param str Input string.
 * @param i Pointer to current index (updated after expansion).
 * @param cleaned Buffer to append the variable's value.
 * @param minishell Shell instance for environment lookup.
 * @return Length of the appended value.
 */

int	expand_var(char *str, int *i, char *cleaned, t_minishell *minishell)
{
	char	*var_name;
	char	*var_value;
	int		len;

	(*i)++;
	var_name = extract_var_name(str + *i);
	var_value = get_env_value(var_name, minishell);
	if (!var_value)
		var_value = "";
	len = ft_strlcpy(cleaned, var_value, ft_strlen(var_value) + 1);
	*i = *i + ft_strlen(var_name);
	ft_free(1, &var_name);
	return (len - 1);
}

