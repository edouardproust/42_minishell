#include "minishell.h"
/* 
 * Iterates through tokens and handles each token based on its type.
 * For each token type (input redirection, output redirection, word, or pipe),
 * the appropriate handler function is called.
 * - Handles redirections (input/output), pipes, and arguments.
 */
void	handle_token_type(t_minishell **minishell)
{
	while ((*minishell)->current_token)
	{
		if ((*minishell)->current_token->type == TOKEN_REDIR_IN)
			handle_input_redirection(minishell);
		else if ((*minishell)->current_token->type == TOKEN_REDIR_OUT)
			handle_output_redirection(minishell);
		else if ((*minishell)->current_token->type == TOKEN_WORD)
			handle_word(minishell);
		else if ((*minishell)->current_token->type == TOKEN_PIPE)
			handle_pipe(minishell);
		(*minishell)->current_token = (*minishell)->current_token->next;
	}
}
