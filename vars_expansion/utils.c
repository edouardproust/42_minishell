#include "minishell.h"

char	*extract_name_with_braces(char *start, int *chars_consumed)
{
	int		i;
	int		brace_depth;
	char	*name;

	i = 1;
	brace_depth = 1;
	while (start[i] && brace_depth > 0)
	{
		if (start[i] == '{')
			brace_depth++;
		else if (start[i] == '}')
			brace_depth--;
		i++;
	}
	if (brace_depth != 0)
		return (*chars_consumed = 0, NULL);
	*chars_consumed = i;
	name = ft_substr(start, 1, i - 2);
	if (name[0] == '\0')
		return (free(name), *chars_consumed = 0, NULL);
	return (name);
}

char	*extract_name_without_braces(char *start, int *chars_consumed)
{
	int		i;

	i = 0;
	while (ft_isalnum(start[i]) || start[i] == '_')
		i++;
	*chars_consumed = i;
	return (ft_substr(start, 0, i));
}

void	handle_bad_substitution(t_expansion *exp, char *str, int chars_consumed)
{
	if (chars_consumed != 0)
		return ;
	if (exp->output_pos + 1 >= exp->buf_size)
		ensure_buffer_space(exp, 1);
	exp->cleaned[exp->output_pos++] = '$';
	if (str[exp->input_pos + 1] == '{')
		put_error("${}: bad substitution");
}

/*
 * Extracts the variable name after `$`.
 * 
 * @param start Position after `$` (e.g., `USER` in `$USER`).
 * @return Allocated string containing the variable name.
 */
char	*extract_var_name(char *start, int *chars_consumed)
{
	char	*var_name;

	if (start[0] == '{')
		var_name = extract_name_with_braces(start, chars_consumed);
	else
		var_name = extract_name_without_braces(start, chars_consumed);
	if (!var_name && *chars_consumed == 0 && start[0] == '{')
			put_error("${}: bad substitution");
	return (var_name);
}
