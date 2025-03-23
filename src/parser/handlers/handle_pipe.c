/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:40:16 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:40:18 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Determines the error message for invalid pipe syntax by analyzing context.
 * - Checks for empty commands (leading pipes)
 * - Checks for consecutive/trailing pipes
 *
 * @param token Current pipe token being processed
 * @param cur_cmd Current command structure to validate context
 * @return Error token string to display ("|" or next token's value)
 */
static char	*pipe_error(t_token *token, t_cmd *cur_cmd)
{
	if (!cur_cmd->args && !cmd_has_redirections(cur_cmd))
		return ("|");
	if (!token->next)
		return ("|");
	if (token->next->type == TOKEN_PIPE)
		return ("|");
	return (token->next->value);
}

/**
 * Handles pipe operator (`|`) syntax and pipeline creation
 * - Validates proper pipe usage context
 * - Creates new command structure for RHS of pipeline
 * - Sets proper error codes for syntax violations
 *
 * @param cur_token Pointer to current pipe token
 * @param cur_cmd Double pointer to current command
 * @param minishell Shell context for error handling
 * @return EXIT_SUCCESS on valid pipe, EXIT_FAILURE on syntax error
 */
int	handle_pipe(t_token **cur_token, t_cmd **cur_cmd,
	t_minishell *minishell)
{
	t_token	*token;

	token = *cur_token;
	if ((!(*cur_cmd)->args && !cmd_has_redirections(*cur_cmd))
		|| !token->next || token->next->type == TOKEN_PIPE)
	{
		put_error1("syntax error near unexpected token `%s'",
			pipe_error(token, *cur_cmd));
		minishell->exit_code = E_CRITICAL;
		return (EXIT_FAILURE);
	}
	(*cur_cmd)->next = cmd_new((*cur_cmd));
	if (!(*cur_cmd)->next)
		exit_minishell(EXIT_FAILURE, minishell, "cmd: malloc");
	(*cur_cmd) = (*cur_cmd)->next;
	*cur_token = token->next;
	return (EXIT_SUCCESS);
}
