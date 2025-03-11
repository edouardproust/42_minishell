#include "minishell.h"
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
		return (extract_name_with_braces(start, chars_consumed));
	}
	return (extract_name_without_braces(start, chars_consumed));
}

/*
 * Expands `$$` to the current process ID (PID).
 * Converts `getpid()` to a string and appends it to the output buffer.
 */
void	handle_pid_expansion(t_expansion *exp)
{
	char	*pid_str;
	int		pid_len;

	pid_str = ft_itoa(getpid());
	if (!pid_str)
		return ;
	pid_len = ft_strlen(pid_str);
	ensure_buffer_space(exp, pid_len);
	ft_strlcpy(exp->cleaned + exp->output_pos, pid_str, pid_len + 1);
	exp->output_pos = exp->output_pos + pid_len;
	free(pid_str);
}

/*
 * Handles `$?` (exit code) and `$$` (PID).
 * Returns `1` if a special case was processed, `0` otherwise.
 */
int	handle_special_cases(t_expansion *exp, char *str, t_minishell *minishell)
{
	if (str[exp->input_pos] == '$' && str[exp->input_pos + 1] == '$')
	{
		handle_pid_expansion(exp);
		exp->input_pos = exp->input_pos + 2;
		return (1);
	}
	else if (str[exp->input_pos] == '?')
	{
		handle_exit_status(exp, minishell);
		exp->input_pos++;
		return (1);
	}
	else if (!str[exp->input_pos + 1]
		|| (str[exp->input_pos + 1] != '{'
			&& !is_valid_varchar(str[exp->input_pos + 1], TRUE)))
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
