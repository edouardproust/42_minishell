#include "minishell.h"
/* 
 * Checks if the character is a special character (|, <, >).
 * Returns: 1 if special char, 0 otherwise.
 */
int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/* 
 * Checks if the character is a space.
 * Returns: 1 if it is a space, 0 otherwise).
 */
int	is_space_char(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

/*
 * Checks if the character is a quote symbol.
 * Returns: 1 if quote char, 0 otherwise.
 */
int	is_quote_char(char c)
{
	return (c == '\'' || c == '"');
}

void	skip_whitespaces(char *input, int *i)
{
	while (input[*i] == ' ' || (input[*i] >= 9 && input[*i] <= 13))
		(*i)++;
}
