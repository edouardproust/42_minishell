#include "minishell.h"
/**
 * Handles output redirection (`>`) token by setting the outfile for the
 * current command.
 * - Ensures that the next token is a valid word token (file name).
 * - Copies the file name to the current command's outfile field.
 */
int	handle_redir_out(t_token **cur_token, t_cmd **cur_cmd,
	t_minishell *minishell)
{
	t_token	*token;

	token = *cur_token;
	if (!token->next || token->next->type != TOKEN_WORD)
	{
		put_error1("syntax error near unexpected token `%s'",
			redir_error(token));
		minishell->exit_code = E_CRITICAL;
		return (EXIT_FAILURE);
	}
	if (check_ambiguous_redirect(token->next, minishell) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_free(&(*cur_cmd)->outfile);
	(*cur_cmd)->outfile = ft_strdup(token->next->value);
	(*cur_cmd)->append = FALSE;
	if (!(*cur_cmd)->outfile)
		exit_minishell(EXIT_FAILURE, minishell, "parse redirection: malloc");
	(*cur_token) = token->next->next;
	return (EXIT_SUCCESS);
}
