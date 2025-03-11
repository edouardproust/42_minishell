#include "minishell.h"
/*
 * Handles `$?` and invalid `$` cases (e.g., `$` at end or followed by invalid char).
 * Returns `1` if a special/invalid case was handled, `0` otherwise.
 */
int	handle_special_cases(t_expansion *exp, char *str, t_minishell *minishell)
{
	if (str[exp->input_pos] == '$' && str[exp->input_pos + 1] == '?')
	{
		handle_exit_status(exp, minishell);
		exp->input_pos = exp->input_pos + 2;
		return (1);
	}
	else if (!str[exp->input_pos + 1] && (!str[exp->input_pos + 1]
		|| !is_valid_varchar(str[exp->input_pos + 1], TRUE)))
	{
		ensure_buffer_space(exp, 1);
		exp->cleaned[exp->output_pos++] = '$';
		exp->input_pos++;
		return (1);
	}
	return (0);
}

/*
 * Expands `$?` to the last exit code stored in `minishell->exit_code`.
 * Converts the integer to a string and appends it to the output buffer.
 */
void	handle_exit_status(t_expansion *exp, t_minishell *minishell)
{
	char	*exit_str;
	int		len;

	exit_str = ft_itoa(minishell->exit_code);
	if (!exit_str)
		return ;
	len = ft_strlen(exit_str);
	ensure_buffer_space(exp, len);
	ft_strlcpy(exp->cleaned + exp->output_pos, exit_str, len + 1);
	exp->output_pos = exp->output_pos + len;
	free(exit_str);
}
