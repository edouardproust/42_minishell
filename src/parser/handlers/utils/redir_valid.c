/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:41:32 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:43:14 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Determines the error message for invalid redirection syntax.
 *
 * @param token Current token (e.g., `<`, `>`, `<<`, `>>`).
 * @return "newline" if no token follows, "|" for unexpected pipes.
 */
char	*redir_error(t_token *token)
{
	if (!token->next)
		return ("newline");
	if (token->next->type == TOKEN_PIPE)
		return ("|");
	return (token->next->value);
}

int	check_redir_syntax(t_token *token, t_minishell *minishell)
{
	if (!token->next || token->next->type != TOKEN_WORD)
	{
		put_error1("syntax error near unexpected token `%s'",
			redir_error(token));
		minishell->exit_code = E_CRITICAL;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * Validates redirection targets to prevent ambiguous filenames.
 *
 * @param file_token Token containing filename (after expansion)
 * @param minishell Shell context for error reporting
 * @return EXIT_SUCCESS if valid, EXIT_FAILURE if:
 *         - Value is empty/unset
 *         - Contains spaces in unquoted token
 * @note Uses original token value for error messages
 */
int	check_ambiguous_redir(t_token *file_token, t_minishell *minishell)
{
	char	*expanded_val;

	expanded_val = file_token->value;
	if (!expanded_val || expanded_val[0] == '\0')
	{
		put_error1("%s: ambiguous redirect", file_token->original_value);
		minishell->exit_code = E_CRITICAL;
		return (EXIT_FAILURE);
	}
	if (ft_strchr(expanded_val, ' ') && !file_token->was_quoted)
	{
		put_error1("%s: ambiguous redirect", file_token->original_value);
		minishell->exit_code = E_CRITICAL;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
