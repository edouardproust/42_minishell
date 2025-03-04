#include "minishell.h"
/**
 * Handles output redirection (`>`) token by setting the outfile for the
 * current command.
 * - Ensures that the next token is a valid word token (file name).
 * - Copies the file name to the current command's outfile field.
 * @TODO Check malloc error message (for now on NULL)
 */
void	handle_redir_out(t_token **cur_token, t_cmd **cur_cmd,
	t_minishell *minishell)
{
	t_token	*token;

	token = *cur_token;
	if (!token->next || token->next->type != TOKEN_WORD)
		exit_minishell(EXIT_FAILURE, minishell,
			"syntax error near unexpected token `newline'");
	ft_free(1, &(*cur_cmd)->outfile);
	(*cur_cmd)->outfile = ft_strdup(token->next->value);
	(*cur_cmd)->append = 0;
	if (!(*cur_cmd)->outfile)
		exit_minishell(EXIT_FAILURE, minishell, NULL);
	(*cur_token) = token->next->next;
}
