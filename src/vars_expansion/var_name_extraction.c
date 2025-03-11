#include "minishell.h"
/*
 * Checks if `c` is a valid variable name character.
 *
 * Returns `TRUE` if valid, `FALSE` otherwise.
 */
t_bool	is_valid_varchar(char c, t_bool first_char)
{
	if (first_char)
	{
		if (ft_isalpha(c) || c == '_')
			return (TRUE);
	}
	else
	{
		if (ft_isalnum(c) || c == '_')
			return (TRUE);
	}
	return (FALSE);
}

char	*extract_var_name(char *start, int *chars_consumed)
{
	int	i;
	i = 0;
	if (!is_valid_varchar(start[i], TRUE))
		return (*chars_consumed = 0, NULL);
	while (is_valid_varchar(start[i], (i == 0)))
		i++;
	*chars_consumed = i;
	return (ft_substr(start, 0, i));
}
