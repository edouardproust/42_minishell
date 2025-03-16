#include "minishell.h"
/*
 * Retrieves a variable’s value from the env and adds it to the output.
 * - Unset variables are treated as empty strings.
 * - Uses `get_env_value` (assumed to search `minishell`’s env).
 */
static void	process_valid_var(t_expansion *exp, char *var_name,
	t_minishell *minishell)
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
}

/*
 * Expands a variable starting at `exp->input_pos`.
 * - Handles special cases (`$?` etc).
 * - Extracts and validates the variable name.
 * - Appends the variable’s value (or empty string if unset).
 * Returns `0` on failure.
 */
int	expand_var(t_expansion *exp, char *str, t_minishell *minishell)
{
	char	*var_name;
	int		chars_consumed;

	chars_consumed = 0;
	if (handle_special_cases(exp, str, minishell))
		return (0);
	exp->input_pos++;
	var_name = extract_var_name(str + exp->input_pos, &chars_consumed);
	if (!var_name)
		return (0);
	process_valid_var(exp, var_name, minishell);
	exp->input_pos = exp->input_pos + chars_consumed;
	ft_free(1, &var_name);
	return (0);
}
