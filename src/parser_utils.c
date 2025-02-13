#include "minishell.h"

void	handle_token_type(t_cmd *current_cmd, t_token **tokens)
{
	while (*tokens)
	{
		if ((*tokens)->type == TOKEN_REDIR_IN)
			handle_input_redirection(current_cmd, tokens);
		else if ((*tokens)->type == TOKEN_REDIR_OUT)
			handle_output_redirection(current_cmd, tokens);
		else if ((*tokens)->type == TOKEN_WORD)
			handle_word(current_cmd, *tokens);
		else if ((*tokens)->type == TOKEN_PIPE)
		{
			handle_pipe(&current_cmd, tokens);
			continue ;
		}
		*tokens = (*tokens)->next;
	}
}
