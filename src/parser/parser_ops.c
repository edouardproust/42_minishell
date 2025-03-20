/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:43:49 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:43:51 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * Returns a static list of parsing operators and their corresponding handlers.
 *
 * Used in `handle_token_type()` to determine how to process tokens.
 *
 * Returns: A pointer to a static array of `t_parse_op` structures.
 */
t_parse_op	*get_parse_ops(void)
{
	static t_parse_op	parse_ops[] = {
	{TOKEN_PIPE, handle_pipe},
	{TOKEN_REDIR_IN, handle_redir_in},
	{TOKEN_REDIR_OUT, handle_redir_out},
	{TOKEN_HEREDOC, handle_redir_heredoc},
	{TOKEN_APPEND, handle_redir_append},
	{TOKEN_WORD, handle_word},
	{0, NULL}
	};

	return (parse_ops);
}

/**
 * Processes tokens based on their type using appropriate handler functions
 * - Calls handlers for redirections (`<`, `>`, `<<`, `<<`),
 *   pipes (`|`), and words.
 * - If an unknown token is encountered, exits with an error.
 */
int	handle_token_type(t_token **cur_token, t_cmd **cur_cmd,
	t_minishell *minishell)
{
	t_parse_op	*parse_ops;
	int			type;
	int			i;

	parse_ops = get_parse_ops();
	type = (*cur_token)->type;
	i = 0;
	while (parse_ops[i].handler)
	{
		if (parse_ops[i].type == type)
			return (parse_ops[i].handler(cur_token, cur_cmd, minishell));
		i++;
	}
	exit_minishell(EXIT_FAILURE, minishell, NULL);
	return (EXIT_FAILURE);
}
