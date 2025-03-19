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
	t_token	*token;
	int		fd;

	token = *cur_token;
	if (check_redir_syntax(token, minishell) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (check_ambiguous_redir(token->next, minishell) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if ((*cur_cmd)->outfile != NULL)
	{
		fd = open((*cur_cmd)->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			put_error1("%s: failed to create file", (*cur_cmd)->outfile);
		ft_close(&fd);
		ft_free(&(*cur_cmd)->outfile);
	}
	(*cur_cmd)->outfile = ft_strdup(token->next->value);
	(*cur_cmd)->append = FALSE;
	if (!(*cur_cmd)->outfile)
		exit_minishell(EXIT_FAILURE, minishell, "parse redirection: malloc");
	(*cur_token) = token->next->next;
	return (EXIT_SUCCESS);
}
