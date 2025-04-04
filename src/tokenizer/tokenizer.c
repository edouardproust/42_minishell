/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:36:32 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:36:34 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * Tokenizes the input string into individual tokens.
 *
 * - Calls skip_whitespace in order to skip over spaces in the input string.
 * - Iterates through the input, processing each character.
 * - Calls `handle_token_creation()` to create appropriate tokens.
 * - Adds the tokens to `minishell->token_lst` using `token_addback()`.
 * - If an unmatched quote is detected,
 *   an error is handled in `handle_token_error()`.
 * - If memory allocation fails, the token list is freed and the function
 *   returns NULL.
 *
 * @param minishell Pointer to the minishell data structure.
 * @return The head of the token list (`t_token *`), or NULL if an error
 *  occurs during tokenization.
 */
t_token	*tokenizer(t_minishell *minishell)
{
	char	*input;
	t_token	*new_token;
	char	unmatched_quote;
	int		i;

	input = minishell->input;
	i = 0;
	unmatched_quote = 0;
	while (input[i])
	{
		skip_whitespaces(input, &i);
		if (!input[i])
			break ;
		new_token = handle_token_creation
			(input, &i, &unmatched_quote, minishell);
		if (!new_token)
			return (handle_token_error(&minishell->token_lst,
					unmatched_quote, minishell), NULL);
		token_addback(&minishell->token_lst, new_token);
	}
	return (minishell->token_lst);
}
