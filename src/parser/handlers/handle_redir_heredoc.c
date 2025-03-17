#include "minishell.h"
/**
 * Handles heredoc redirection (`<<`) token by setting the delimiter for the
 * current command.
 * - Ensures that the next token is a valid word token (delimiter).
 * - Stores the delimiter in `heredoc_del` for later processing.
 * If the token sequence is invalid, it exits with a syntax error.
 */
int	handle_redir_heredoc(t_token **cur_token, t_cmd **cur_cmd,
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
	ft_free(&(*cur_cmd)->infile);
	ft_free(&(*cur_cmd)->heredoc->delimiter);
	(*cur_cmd)->heredoc->delimiter = ft_strdup(token->next->value);
	if (!(*cur_cmd)->heredoc->delimiter)
		exit_minishell(EXIT_FAILURE, minishell, NULL);
	*cur_token = token->next->next;
	(*cur_cmd)->heredoc->start = minishell->input_line;
	return (EXIT_SUCCESS);
}
