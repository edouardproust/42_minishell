#include "minishell.h"

static void	process_valid_var(t_expansion *exp, char *var_name,
	t_minishell *minishell, int chars_consumed)
{
	char	*var_value;
	int		var_len;

	var_value = get_env_value(var_name, minishell);
	if (!var_value)
		var_value = "";
	var_len = ft_strlen(var_value);
	if (exp->output_pos + var_len >= exp->buf_size)
		ensure_buffer_space(exp, var_len);
	ft_strlcpy(exp->cleaned + exp->output_pos, var_value, var_len + 1);
	exp->output_pos = exp->output_pos + var_len;
	exp->input_pos = exp->input_pos + chars_consumed;
}

/*
 * Expands a variable starting at `i` and updates the cleaned buffer.
 * 
 * @param str Input string.
 * @param i Pointer to current index (updated after expansion).
 * @param cleaned Buffer to append the variable's value.
 * @param minishell Shell instance for environment lookup.
 * @return Length of the appended value.
 */
int	expand_var(t_expansion *exp, char *str, t_minishell *minishell)
{
	char	*var_name;
	int		chars_consumed;
	int		error;

	error = 0;
	chars_consumed = 0;
	exp->input_pos++;
	var_name = extract_var_name(str + exp->input_pos, &chars_consumed);
	if (!var_name)
	{
		handle_bad_substitution(exp, str, chars_consumed);
		error = 1;
	}
	process_valid_var(exp, var_name, minishell, chars_consumed);
	ft_free(1, &var_name);
	return (error);
}
