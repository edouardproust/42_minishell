#include "minishell.h"

/**
 * Iterates through tokens and handles each token based on its type.
 * 
 * For each token type (input redirection, output redirection, word, or pipe),
 * the appropriate handler function is called.
 * Handles redirections (input/output), pipes, and arguments.
 */
void	handle_token_type(t_token **cur_token, t_cmd **cur_cmd,
	t_minishell *minishell)
{
	if ((*cur_token)->type == TOKEN_REDIR_IN)
		handle_input_redirection(cur_token, cur_cmd, minishell);
	else if ((*cur_token)->type == TOKEN_REDIR_OUT)
		handle_output_redirection(cur_token, cur_cmd, minishell);
	else if ((*cur_token)->type == TOKEN_WORD)
		handle_word(cur_token, cur_cmd, minishell);
	else if ((*cur_token)->type == TOKEN_PIPE)
		handle_pipe(cur_token, cur_cmd, minishell);
}
