/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:41:26 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:42:26 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * Handles unquoted word tokens by splitting them into individual arguments.
 * - Creates temporary tokens from split values
 * - Adds each split part as a separate command argument
 * - Ensures proper memory cleanup on allocation failure
 *
 * @param cur_cmd Current command being built
 * @param split_tokens Temporary tokens created from splitting
 * @param minishell Shell context for error handling
 */
static void	handle_unquoted_word(t_cmd *cur_cmd, t_token *split_tokens,
				t_minishell *minishell)
{
	t_token	*tmp;
	char	*arg_copy;

	tmp = split_tokens;
	while (tmp)
	{
		arg_copy = ft_strdup(tmp->value);
		if (!arg_copy)
		{
			free_token_lst(&split_tokens);
			exit_minishell(EXIT_FAILURE, minishell, NULL);
		}
		add_arg_to_cmd(cur_cmd, arg_copy);
		tmp = tmp->next;
	}
	free_token_lst(&split_tokens);
}

/**
 * Handles a word token by copying its value and adding it to the current
 * command's arguments.
 * - Duplicates the word and adds it to the args list of the current command.
 */
int	handle_word(t_token **cur_token, t_cmd **cur_cmd,
	t_minishell *minishell)
{
	t_token	*token;
	char	*arg_copy;

	token = *cur_token;
	if (token->was_quoted)
	{
		arg_copy = ft_strdup(token->value);
		if (!arg_copy)
			exit_minishell(EXIT_FAILURE, minishell, "parse word: strdup");
		add_arg_to_cmd(*cur_cmd, arg_copy);
	}
	else
		handle_unquoted_word(*cur_cmd,
			split_unquoted(token, token->value), minishell);
	*cur_token = token->next;
	return (EXIT_SUCCESS);
}
