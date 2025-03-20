/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:40:26 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:40:29 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * Handles heredoc redirection (`<<`) token by setting the delimiter for the
 * current command.
 * - Ensures that the next token is a valid word token (delimiter).
 * - Stores the delimiter in `heredoc_del` for later processing.
 * If the token sequence is invalid, it exits with a syntax error.
 */
int	handle_redir_heredoc(t_token **cur_token, t_cmd **cur_cmd,
	t_minishell *minishell)
{
	t_token	*token;
	int		ret;

	token = *cur_token;
	if (check_redir_syntax(token, minishell) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (check_ambiguous_redir(token->next, minishell) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ret = add_path_to_redirs(&(*cur_cmd)->infiles, token->next->value);
	if (ret == EXIT_FAILURE)
		exit_minishell(EXIT_FAILURE, minishell, "parse heredoc: malloc");
	ft_free(&(*cur_cmd)->infile);
	ft_free(&(*cur_cmd)->heredoc->delimiter);
	(*cur_cmd)->heredoc->delimiter = ft_strdup(token->next->value);
	if (!(*cur_cmd)->heredoc->delimiter)
		exit_minishell(EXIT_FAILURE, minishell, NULL);
	*cur_token = token->next->next;
	(*cur_cmd)->heredoc->start = minishell->input_line;
	return (EXIT_SUCCESS);
}
