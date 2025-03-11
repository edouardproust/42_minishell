#include "minishell.h"

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

char	*extract_name_with_braces(char *start, int *chars_consumed)
{
	int		i;
	int		j;
	char	*name;

	i = 1;
	*chars_consumed = 0;
	while (start[i] && start[i] != '}')
		i++;
	if (start[i] != '}' || i == 1 || !is_valid_varchar(start[1], TRUE))
		return (NULL);
	name = ft_substr(start, 1, i - 1);
	if (!name)
		return (NULL);
	j = 0;
	while (name[j])
	{
		if (!is_valid_varchar(name[j], (j == 0)))
			return (free(name), NULL);
		j++;
	}
	*chars_consumed = i + 1;
	return (name);
}

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

void	handle_bad_substitution(t_expansion *exp, char *str)
{
	char	*sub;
	int		end;

	end = exp->input_pos;
	while (str[end] && !ft_isspace(str[end]) 
		&& str[end] != '$' && str[end] != '}' 
		&& !is_quote_char(str[end]))
		end++;
	if (str[end] == '}')
		end++;
	sub = ft_substr(str, exp->input_pos - 1, end - (exp->input_pos - 1) + 1);
	if (!sub)
		return ;
	set_errno(0);
	put_error("%s: bad substitution", sub);
	free(sub);
	exp->input_pos = end + 1;
}

/*
 * Extracts the variable name after `$`.
 * 
 * @param start Position after `$` (e.g., `USER` in `$USER`).
 * @return Allocated string containing the variable name.
 */
char	*extract_var_name(char *start, int *chars_consumed)
{
	if (start[0] == '}')
		return (*chars_consumed = 0, NULL);
	if (start[0] == '{')
	{
		if (start[1] == '}')
			return (*chars_consumed = 3, NULL);
		return (extract_name_with_braces(start, chars_consumed));
	}
	return (extract_name_without_braces(start, chars_consumed));
}

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

int	handle_special_cases(t_expansion *exp, char *str, t_minishell *minishell)
{
	if (str[exp->input_pos] == '$' && str[exp->input_pos + 1] == '$')
	{
		handle_pid_expansion(exp);
		exp->input_pos += 2;
		return (1);
	}
	else if (str[exp->input_pos] == '?')
    {
		handle_exit_status(exp, minishell);
		exp->input_pos++;
		return (1);
    }
	else if (!str[exp->input_pos] || !is_valid_varchar(str[exp->input_pos], TRUE))
	{
		ensure_buffer_space(exp, 1);
		exp->cleaned[exp->output_pos++] = '$';
		exp->input_pos++;
		return (1);
	}
	return (0);
}

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
