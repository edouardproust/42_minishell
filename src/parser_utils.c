#include "minishell.h"

void handle_token_type(t_cmd **cmd_list_head, t_cmd **current_cmd, t_token **tokens_head, t_token **current_token)
{
	while (*current_token)
	{
		if ((*current_token)->type == TOKEN_REDIR_IN)
			handle_input_redirection(cmd_list_head, tokens_head, *current_cmd, current_token);
		else if ((*current_token)->type == TOKEN_REDIR_OUT)
			handle_output_redirection(cmd_list_head, tokens_head, *current_cmd, current_token);
		else if ((*current_token)->type == TOKEN_WORD)
			handle_word(cmd_list_head, tokens_head, *current_cmd, *current_token);
		else if ((*current_token)->type == TOKEN_PIPE)
		{
			handle_pipe(cmd_list_head, current_cmd, tokens_head, current_token);
			continue ;
		}
		*current_token = (*current_token)->next;
	}
}
