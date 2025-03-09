#include "minishell.h"

static char	*extract_name_with_braces(char *start, t_expansion *exp)
{
	char	*name;
	int		i;
	int		brace_depth;

	i = 0;
	exp->input_pos++;
	brace_depth = 1;
	i++;
	while (start[exp->input_pos] && brace_depth > 0)
	{
		if (start[exp->input_pos] == '{')
			brace_depth++;
		else if (start[exp->input_pos] == '}')
			brace_depth--;
		exp->input_pos++;
	}
	name = ft_substr(start, 1, i - 2);
	exp->input_pos = exp->input_pos + i;
	return (name);
}

static char	*extract_name_without_braces(char *start, t_expansion *exp)
{
	char	*name;
	int		start_pos;

	start_pos = exp->input_pos;
	while (ft_isalnum(start[exp->input_pos])
			|| start[exp->input_pos] == '_')
		exp->input_pos++;
	name = ft_substr(start, start_pos, exp->input_pos - start_pos);
	return (name);
}

/**
 * Extracts the variable name after `$`.
 * 
 * @param start Position after `$` (e.g., `USER` in `$USER`).
 * @return Allocated string containing the variable name.
 */
static char	*extract_var_name(char *start, t_expansion *exp)
{

	if (start[exp->input_pos] == '{')
		return (extract_name_with_braces(start, exp));
	else
		return (extract_name_without_braces(start, exp));
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

	exp->input_pos++;
	var_name = extract_var_name(str + exp->input_pos, exp);
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
	ft_free(1, &var_name);
}

