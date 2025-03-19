/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:36:03 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:36:06 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
int	process_quotes(char c, t_expansion *exp)
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
