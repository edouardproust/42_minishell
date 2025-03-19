#include "minishell.h"
/**
 * Processes a string through three stages:
 * 1. Quote removal (handling nested/non-nested quotes)
 * 2. Variable expansion (`$VAR` substitution)
 * 3. Clean string construction
 *
 * @param str Input string with potential quotes/variables
 * @return Newly allocated processed string, or NULL on:
 *         - Memory allocation failure
 *         - Unclosed quotes
 */
char	*remove_quotes_and_expand(char *str, t_minishell *minishell,
	t_bool remove_quotes)
{
	t_expansion	exp;
	int			error;
	char		*result;

	error = 0;
	init_expansion(&exp, str);
	if (!exp.cleaned)
		return (NULL);
	exp.cleaned[0] = '\0';
	while (str[exp.input_pos] && !error)
	{
		if (remove_quotes && is_quote_char(str[exp.input_pos]))
			error = process_quotes(str[exp.input_pos], &exp);
		else if ((!exp.in_quote || exp.in_quote == '"')
			&& str[exp.input_pos] == '$')
			error = expand_var(&exp, str, minishell);
		else
			exp.cleaned[exp.output_pos++] = str[exp.input_pos++];
	}
	if (error)
		return (free(exp.cleaned), free(str), NULL);
	exp.cleaned[exp.output_pos] = '\0';
	result = ft_strdup(exp.cleaned);
	free(exp.cleaned);
	return (result);
}
