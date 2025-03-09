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
 * Processes a single character while removing surrounding quotes.
 *
 * - If inside a quote block, the function either closes the quote
 *   or adds the character to the cleaned string.
 * - If not inside a quote block, it checks if the character is a quote
 *   and marks the start of a new quote block or adds the character.
 *
 * @param c The current character to process.
 * @param in_quote Pointer to track whether currently inside a quote.
 * @param cleaned The output string being built.
 * @param j Pointer to the current position in `cleaned`.
 */
static void	process_quotes(char c, t_expansion *exp)
{
	if (!exp->in_quote && (is_quote_char(c)))
		exp->in_quote = c;
	else if (exp->in_quote == c)
		exp->in_quote = 0;
	exp->input_pos++;
}

/**
 * Removes quotes from a string while preserving its contents.
 *
 * - Allocates memory for a new string without quotes.
 * - Iterates through the input string and removes quote characters while
 *   preserving characters inside quotes.
 * - If memory allocation fails, frees the input string and returns NULL.
 *
 * @param str The string to process.
 * @return A new string with quotes removed, or NULL if memory allocation fails.
 */
char	*remove_quotes_and_expand(char *str, t_minishell *minishell)
{
	t_expansion	exp;

	init_expansion(&exp, str);
	if (!exp.cleaned)
		return(free(str), NULL);
	while (str[exp.input_pos])
	{
		if ((!exp.in_quote || exp.in_quote == '"'))
		{
			if (str[exp.input_pos] == '$')
				expand_var(&exp, str, minishell);
			else if (is_quote_char(str[exp.input_pos]))
				process_quotes(str[exp.input_pos], &exp);
			else
				exp.cleaned[exp.output_pos++] = str[exp.input_pos++];
		}
		else
			exp.cleaned[exp.output_pos++] = str[exp.input_pos++];
	}
	exp.cleaned[exp.output_pos] = '\0';
	free(str);
	return (exp.cleaned);
}
