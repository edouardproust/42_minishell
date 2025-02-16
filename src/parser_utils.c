#include "minishell.h"
/* 
 * Iterates through tokens and handles each token based on its type.
 * For each token type (input redirection, output redirection, word, or pipe),
 * the appropriate handler function is called.
 * - Handles redirections (input/output), pipes, and arguments.
 */
void	handle_token_type(t_parse *parse)
{
	while (parse->current_token)
	{
		if (parse->current_token->type == TOKEN_REDIR_IN)
			handle_input_redirection(parse);
		else if (parse->current_token->type == TOKEN_REDIR_OUT)
			handle_output_redirection(parse);
		else if (parse->current_token->type == TOKEN_WORD)
			handle_word(parse);
		else if (parse->current_token->type == TOKEN_PIPE)
		{
			handle_pipe(parse);
			continue ;
		}
		parse->current_token = parse->current_token->next;
	}
}
