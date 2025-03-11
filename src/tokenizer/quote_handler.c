#include "minishell.h"
/** 
 * Skips over quoted sections of the input string.
 *
 * - If a quote character is encountered, it starts skipping
 *   until the matching quote is found.
 * - If the string ends before finding a matching quote, it sets
 *   `unmatched_quote` and returns 0.
 * - Otherwise, it increments the index past the closing quote and returns 1.
 *
 * @param input The input string to process.
 * @param index Pointer to the current position in the input string.
 * @param unmatched_quote Pointer to store an unmatched quote if found.
 * @return 1 if quotes are properly matched, 0 if an unmatched quote is found.
 */
int	skip_quotes(char *input, int *index, char *unmatched_quote)
{
	char	quote;

	quote = input[*index];
	(*index)++;
	while (input[*index] && input[*index] != quote)
		(*index)++;
	if (!input[*index])
	{
		*unmatched_quote = quote;
		return (0);
	}
	(*index)++;
	return (1);
}

/*
 * Toggles quote state and skips quote characters in the output.
 * - If `c` matches the current `exp->in_quote`, closes the quote block.
 * - If not in a quote, opens a new quote block (single/double).
 * - Characters inside quotes are preserved; quote marks are omitted.
 * Returns `0` on success.
 */
static int	process_quotes(char c, t_expansion *exp)
{
	if (exp->in_quote == 0)
	{
		exp->in_quote = c;
		exp->input_pos++;
	}
	else if (exp->in_quote == c)
	{
		exp->in_quote = 0;
		exp->input_pos++;
	}
	else
	{
		exp->cleaned[exp->output_pos++] = c;
		exp->input_pos++;
	}
	return (0);
}

/*
 * Main entry point for quote removal and variable expansion.
 * - Allocates a buffer for the cleaned string (via `init_expansion`).
 * - Processes each character:
 *   - Skips quotes (handled by `process_quotes`).
 *   - Expands `$VAR` (via `expand_var`).
 * - Returns the cleaned string, or `NULL` on allocation error.
 * Frees the original `str` after processing.
 */
char	*remove_quotes_and_expand(char *str, t_minishell *minishell)
{
	t_expansion	exp;
	int			error;

	error = 0;
	init_expansion(&exp, str);
	if (!exp.cleaned)
		return (free(str), NULL);
	exp.cleaned[0] = '\0';
	while (str[exp.input_pos] && !error)
	{
		if (is_quote_char(str[exp.input_pos]))
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
	free(str);
	return (exp.cleaned);
}
