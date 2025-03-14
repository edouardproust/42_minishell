#include "minishell.h"
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
 * Handles invalid variable syntax (e.g. `${}`).
 * - Prints "bad substitution" error for the invalid substring.
 * - Advances `exp->input_pos` to skip the invalid portion.
 */
void	handle_bad_substitution(t_expansion *exp, char *str)
{
	int		end;
	char	*sub;

	end = exp->input_pos - 1;
	while (str[end] && !ft_isspace(str[end]) && !is_quote_char(str[end]))
		end++;
	sub = ft_substr(str, exp->input_pos - 1, end - (exp->input_pos - 1));
	if (sub)
	{
		put_error("%s: bad substitution", sub);
		free(sub);
	}
	exp->input_pos = end;
}

/**
 * Handles special variable expansion cases:
 * - `$$` (PID expansion)
 * - `$?` (exit code expansion)
 * - Lone `$` or `$` followed by invalid characters
 * 
 * @param exp Expansion context (buffer state)
 * @param str Input string being processed
 * @param minishell Shell context for environment/exit code
 * @return 1 if special case handled, 0 if normal expansion needed
 * @note Advances input position when handling special cases
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
	else if (str[exp->input_pos] == '$' && str[exp->input_pos + 1] == '?')
	{
		handle_exit_status(exp, minishell);
		exp->input_pos = exp->input_pos + 2;
		return (1);
	}
	else if (str[exp->input_pos] == '$'
		&& (str[exp->input_pos + 1] == '\0'
			|| (str[exp->input_pos + 1] != '{'
				&& !is_valid_varchar(str[exp->input_pos + 1], TRUE))))
	{
		ensure_buffer_space(exp, 1);
		exp->cleaned[exp->output_pos++] = '$';
		exp->input_pos++;
		return (1);
	}
	return (0);
}
