/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:35:35 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:35:40 by fpapadak         ###   ########.fr       */
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
