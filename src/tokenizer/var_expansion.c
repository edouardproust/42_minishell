#include "minishell.h"

static char	*extract_name_with_braces(char *start, int *chars_consumed)
{
	int		i;
	int		brace_depth;

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
	{
		*chars_consumed = 0;
		return (ft_strdup("${"));
	}
	*chars_consumed = i;
	return (ft_substr(start, 1, i - 2));
}

static char	*extract_name_without_braces(char *start, int *chars_consumed)
{
	int		i;

	i = 0;
	while (ft_isalnum(start[i]) || start[i] == '_')
		i++;
	*chars_consumed = i;
	return (ft_substr(start, 0, i));
}

/**
 * Extracts the variable name after `$`.
 * 
 * @param start Position after `$` (e.g., `USER` in `$USER`).
 * @return Allocated string containing the variable name.
 */
static char	*extract_var_name(char *start, int *chars_consumed)
{
	if (start[0] == '{' && start[1] == '}')
	{
		*chars_consumed = 2;
		return (ft_strdup(""));
	}
	if (start[0] == '{')
		return (extract_name_with_braces(start, chars_consumed));
	else
		return (extract_name_without_braces(start, chars_consumed));
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

void	expand_var(t_expansion *exp, char *str, t_minishell *minishell)
{
	char	*var_name;
	char	*var_value;
	int		var_len;
	int		chars_consumed;

	chars_consumed = 0;
	exp->input_pos++;
	var_name = extract_var_name(str + exp->input_pos, &chars_consumed);
	if (!var_name)
		return ;
	var_value = get_env_value(var_name, minishell);
	if (!var_value)
		var_value = "";
	var_len = ft_strlen(var_value);
	if (exp->output_pos + var_len >= exp->buf_size)
		ensure_buffer_space(exp, var_len);
	ft_strlcpy(exp->cleaned + exp->output_pos, var_value, var_len + 1);
	exp->output_pos = exp->output_pos + var_len;
	exp->input_pos += chars_consumed;
	ft_free(1, &var_name);
}
