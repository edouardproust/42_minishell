#include "minishell.h"

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
