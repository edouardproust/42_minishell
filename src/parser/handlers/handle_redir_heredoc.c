#include "minishell.h"
/**
 * Handles heredoc redirection (`<<`) token by setting the delimiter for the
 * current command.
 * - Ensures that the next token is a valid word token (delimiter).
 * - Stores the delimiter in `heredoc_del` for later processing.
 * If the token sequence is invalid, it exits with a syntax error.
 * @TODO Check malloc error message (for now on NULL)
 */
void	handle_redir_heredoc(t_token **cur_token, t_cmd **cur_cmd,
	t_minishell *minishell)
{
	t_token	*token;

	token = *cur_token;
	if (!token->next || token->next->type != TOKEN_WORD)
		exit_minishell(EXIT_FAILURE, minishell,
			"syntax error near unexpected token `newline'");
	ft_free_ptrs(1, &(*cur_cmd)->infile);
	ft_free_ptrs(1, &(*cur_cmd)->heredoc_del);
	(*cur_cmd)->heredoc_del = ft_strdup(token->next->value);
	if (!(*cur_cmd)->heredoc_del)
		exit_minishell(EXIT_FAILURE, minishell, NULL);
	*cur_token = token->next->next;
}
