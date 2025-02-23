#include "minishell.h"
/* 
 * Iterates through tokens and handles each token based on its type.
 * For each token type (input redirection, output redirection, word, or pipe),
 * the appropriate handler function is called.
 * - Handles redirections (input/output), pipes, and arguments.
 */
void	handle_token_type(t_token **cur_token, t_cmd **cur_cmd,
	t_minishell *minishell)
{
	t_token_op	*token_op;

		token_op = get_token_op((*cur_token)->type);
		token_op->handler(cur_token, cur_cmd, minishell);
}
