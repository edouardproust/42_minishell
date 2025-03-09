#include "minishell.h"
/**
 * Determines the error message for invalid pipe syntax.
 * 
 * @param token Current token being processed.
 * @return "|" if the next token is missing or another pipe, otherwise returns
 *         the unexpected token's value.
 * @note Static helper for `handle_pipe`.
 */
static char	*pipe_error(t_token *token)
{
	if (!token->next)
		return ("|");
	if (token->next->type == TOKEN_PIPE)
		return ("|");
	return (token->next->value);
}

/**
 * Handles the pipe (`|`) token by creating a new command.
 * - Checks for syntax errors like consecutive pipes.
 * - Creates a new command for the next part of the pipeline.
 */
int	handle_pipe(t_token **cur_token, t_cmd **cur_cmd,
	t_minishell *minishell)
{
	t_token	*token;

	token = *cur_token;
	if (!(token)->next || token->next->type == TOKEN_PIPE)
	{
		put_error("syntax error near unexpected token `%s'",
			pipe_error(token));
		minishell->exit_code = E_CRITICAL;
		return (EXIT_FAILURE);
	}
	(*cur_cmd)->next = cmd_new((*cur_cmd));
	if (!(*cur_cmd)->next)
		exit_minishell(EXIT_FAILURE, minishell, "cmd: malloc");
	(*cur_cmd) = (*cur_cmd)->next;
	*cur_token = token->next;
	return (EXIT_SUCCESS);
}
