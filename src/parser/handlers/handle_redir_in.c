#include "minishell.h"
/**
 * Handles input redirection (`<`) token by setting the infile for the
 * current command.
 * - Ensures that the next token is a valid word token (file name).
 * - Copies the file name to the current command's infile field.
 * @TODO Check malloc error message (for now on NULL)
 */
void	handle_redir_in(t_token **cur_token, t_cmd **cur_cmd,
	t_minishell *minishell)
{
	t_token	*token;

	token = *cur_token;
	if (!token->next || token->next->type != TOKEN_WORD)
		exit_minishell(EXIT_FAILURE, minishell,
			"syntax error near unexpected token `newline'");
	ft_free_ptrs(1, &(*cur_cmd)->infile);
	(*cur_cmd)->infile = ft_strdup(token->next->value);
	if (!(*cur_cmd)->infile)
		exit_minishell(EXIT_FAILURE, minishell, NULL);
	(*cur_token) = token->next->next;
}
