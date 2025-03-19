/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:32:42 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:33:54 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
