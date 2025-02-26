#include "minishell.h"
/**
 * Handles append redirection (`>>`) token by setting the outfile for the
 * current command.
 * - Ensures that the next token is a valid wrod token (file name).
 * - Stores the file name in `outfile` and marks the append flag as `1`.
 * If the token sequence is invalid, it exits with a syntax error.
 * @TODO Check malloc error message (for now on NULL)
 */
void	handle_redir_append(t_token **cur_token, t_cmd **cur_cmd,
	t_minishell *minishell)
{
	t_token	*token;

	token = *cur_token;
	if (!token->next || token->next->type != TOKEN_WORD)
		exit_minishell(EXIT_FAILURE, minishell,
			"syntax error near unexpected token `newline'");
	ft_free_ptrs(1, &(*cur_cmd)->outfile);
	(*cur_cmd)->outfile = ft_strdup(token->next->value);
	(*cur_cmd)->append = 1;
	if (!(*cur_cmd)->outfile)
		exit_minishell(EXIT_FAILURE, minishell, NULL);
	*cur_token = token->next->next;
}
