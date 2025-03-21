/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_out.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:40:42 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:40:44 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Handles output redirection (`>`) token by setting the outfile for the
 * current command.
 * - Ensures that the next token is a valid word token (file name).
 * - Copies the file name to the current command's outfile field.
 */
int	handle_redir_out(t_token **cur_token, t_cmd **cur_cmd,
	t_minishell *minishell)
{
	t_token		*token;
	t_outfile	*new_outfile;

	token = *cur_token;
	if (check_redir_syntax(token, minishell) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (check_ambiguous_redir(token->next, minishell) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	new_outfile = create_outfile(token->next->value, FALSE);
	if (!new_outfile)
		exit_minishell(EXIT_FAILURE, minishell, "parse outfile"); //TODO exit minishell OR print error + new prompt?
	if (add_outfile_to_cmd(*cur_cmd, new_outfile) == EXIT_FAILURE)
		exit_minishell(EXIT_FAILURE, minishell, "parse outfile"); //TODO exit minishell OR print error + new prompt?
	*cur_token = token->next->next;
	return (EXIT_SUCCESS);
}
