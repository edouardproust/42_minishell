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
 * Checks if the character is part of a word (not space, |, <, >).
 * Returns: 1 if word char, 0 otherwise.
 */
//int	is_word_char(char c)
//{
//	return (c != ' ' && !is_special_char(c));
//}
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
	while (input[*i] == ' ')
		(*i)++;
}
