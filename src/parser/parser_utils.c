#include "minishell.h"
/* 
 * Iterates through tokens and handles each token based on its type.
 * For each token type (input redirection, output redirection, word, or pipe),
 * the appropriate handler function is called.
 * - Handles redirections (input/output), pipes, and arguments.
 */
void	handle_token_type(t_parse *parse)
{
	t_token_op	*token_op;

	while (parse->current_token)
	{
		token_op = get_token_op(parse->current_token->type);
		token_op->handler(parse);
	}
}
