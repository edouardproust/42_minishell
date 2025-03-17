#include "minishell.h"

/**
 * Checks if the character is a special character (|, <, >).
 * Used to differentiate between operators and words in tokenization.
 *
 * @param c The character to check
 * @return 1 if special char, 0 otherwise.
 */
int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/**
 * Checks if the character is a whitespace (space, tab, newline, etc.).
 *
 * @param c The character to check
 * @return 1 if it is a whitespace, 0 otherwise).
 */
int	is_space_char(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

/**
 * Checks if the character is a quote symbol.
 * Used to determine whether a word token is enclosed in quotes.
 *
 * @param c The character to check
 * @return 1 if quote char, 0 otherwise.
 */
int	is_quote_char(char c)
{
	return (c == '\'' || c == '"');
}

/**
 * Skips all leading whitespace characters in the input string.
 * Advances the `i` index to the next non-whitespace character.
 *
 * @param input The input string
 * @param i Pointer to the current index in the input string.
 * @return void
 */
void	skip_whitespaces(char *input, int *i)
{
	while (input[*i] == ' ' || (input[*i] >= 9 && input[*i] <= 13))
		(*i)++;
}

/**
 * Converts a character to a null-terminated string.
 *
 * @param c The character to convert.
 * @return A pointer to a static string representing the character.
 */
char	*char_to_str(char c)
{
	static char	str[2];

	str[0] = c;
	str[1] = '\0';
	return (str);
}

/**
 * Converts an integer to a string.
 *
 * Frees the result of ft_itoa immediately and returns a static buffer
 * to avoid memory leaks.
 *
 * @param n The integer to convert.
 * @param minishell Pointer to the minishell struct for cleanup on failure.
 * @return A pointer to a static string representing the integer.
 */
char *int_to_str(int n)
{
	static char	buf[12];
	char		*tmp;

	tmp = ft_itoa(n);
	if (!tmp)
		return (NULL);
	ft_strlcpy(buf, tmp, sizeof(buf));
	free(tmp);
	return (buf);
}
