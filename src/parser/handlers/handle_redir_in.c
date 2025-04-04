/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:41:01 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:41:04 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Handles input redirection (`<`) token by setting the infile for the
 * current command.
 * - Ensures that the next token is a valid word token (file name).
 * - Copies the file name to the current command's infile field.
 */
int	handle_redir_in(t_token **cur_token, t_cmd **cur_cmd,
	t_minishell *minishell)
{
	t_token		*token;
	t_infile	*new_infile;

	token = *cur_token;
	if (check_redir_syntax(token, minishell) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (check_ambiguous_redir(token->next, minishell) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	new_infile = create_infile_from_path(token->next->value);
	if (!new_infile)
		exit_minishell(EXIT_FAILURE, minishell, "parse infile");
	if (add_infile_to_cmd(*cur_cmd, new_infile) == EXIT_FAILURE)
		exit_minishell(EXIT_FAILURE, minishell, "parse infile");
	*cur_token = token->next->next;
	return (EXIT_SUCCESS);
}
