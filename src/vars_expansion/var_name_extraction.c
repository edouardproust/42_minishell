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

/*
 * Extracts `${VAR}`-style variable names.
 * - Validates syntax (e.g., `${VALID}` or `${INVALID!}`).
 * - Returns the extracted name (without braces) or `NULL` on error.
 * Updates `chars_consumed` to indicate how many input characters were processed.
 */
char	*extract_name_with_braces(char *start, int *chars_consumed)
{
	int		i;
	char	*name;

	i = 1;
	*chars_consumed = 0;
	if (!start[1] || !is_valid_varchar(start[1], TRUE))
		return (NULL);
	while (start[i] && start[i] != '}')
	{
		if (!is_valid_varchar(start[i], (i == 1)))
			return (NULL);
		i++;
	}
	if (start[i] != '}' || i == 1)
		return (NULL);
	name = ft_substr(start, 1, i - 1);
	if (!name)
		return (NULL);
	*chars_consumed = i + 1;
	return (name);
}

/*
 * Extracts `$VAR`-style variable names (no braces).
 * - Stops at the first invalid character (e.g., `$USER$VAR` → `USER`).
 * Returns the extracted name or `NULL` on error.
 */
char	*extract_name_without_braces(char *start, int *chars_consumed)
{
	int		i;

	i = 0;
	if (!is_valid_varchar(start[0], TRUE))
		return (*chars_consumed = 0, NULL);
	while (is_valid_varchar(start[i], (i == 0)))
		i++;
	*chars_consumed = i;
	return (ft_substr(start, 0, i));
}

/*
 * Extracts a variable name after `$`.
 * - Delegates to `extract_name_with_braces` or `extract_name_without_braces`.
 * Returns the variable name or `NULL` if invalid.
 * Updates `chars_consumed` to reflect parsed characters (e.g., `${VAR}` -> 5).
 */
char	*extract_var_name(char *start, int *chars_consumed)
{
	if (start[0] == '{')
	{
		if (start[1] == '}' || !is_valid_varchar(start[1], TRUE))
		{
			if (start[1] == '}')
				*chars_consumed = 2;
			else
				*chars_consumed = 1;
			return (NULL);
		}
		if (!extract_name_with_braces(start, chars_consumed))
			*chars_consumed = 0;
		return (extract_name_with_braces(start, chars_consumed));
	}
	return (extract_name_without_braces(start, chars_consumed));
}
