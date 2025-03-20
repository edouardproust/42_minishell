/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_append.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:40:52 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:40:54 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * Handles append redirection (`>>`) token by setting the outfile for the
 * current command.
 * - Ensures that the next token is a valid wrod token (file name).
 * - Stores the file name in `outfile` and marks the append flag as `1`.
 * If the token sequence is invalid, it exits with a syntax error.
 */
int	handle_redir_append(t_token **cur_token, t_cmd **cur_cmd,
	t_minishell *minishell)
{
	t_token	*token;
	int		ret;

	token = *cur_token;
	if (check_redir_syntax(token, minishell) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (check_ambiguous_redir(token->next, minishell) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ret = add_path_to_redirs(&(*cur_cmd)->outfiles, token->next->value);
	if (ret == EXIT_FAILURE)
		exit_minishell(EXIT_FAILURE, minishell, "parse redirection");
	(*cur_cmd)->append = TRUE;
	*cur_token = token->next->next;
	return (EXIT_SUCCESS);
}
