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

static void	init_remove_quotes(char **cleaned, int *buf_size, char *str)
{
	*buf_size = ft_strlen(str) * 2 + 1;
	*cleaned = malloc(*buf_size);
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
static void	process_quotes(char c, char *in_quote, int *i)
{
	if (!*in_quote && (is_quote_char(c)))
		*in_quote = c;
	else if (*in_quote == c)
		*in_quote = 0;
	(*i)++;
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
	t_remove	r;

	init_remove_quotes(&r.cleaned, &r.buf_size, str);
	if (!r.cleaned)
		return(free(str), NULL);
	r.i = 0;
	r.j = 0;
	r.in_quote = 0;
	while (str[r.i])
	{
		if ((!r.in_quote || in_quote == '"') && str[i] == '$')
			handle_expansion(str + r.i, minishell, &r);
		else if (is_quote_char(str[r.i]))
			process_quotes(str[r.i], &r.in_quote, &r.i);
		else
			r.cleaned[r.j++] = str[r.i++];
	}
	cleaned[r.j] = '\0';
	free(str);
	return (r.cleaned);
}
