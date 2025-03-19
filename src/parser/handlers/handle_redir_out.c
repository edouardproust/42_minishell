#include "minishell.h"
/**
 * Handles output redirection (`>`) token by setting the outfile for the
 * current command.
 * - Ensures that the next token is a valid word token (file name).
 * - Copies the file name to the current command's outfile field.
 * @TODO Check malloc error message (for now on NULL)
 */
int	handle_redir_out(t_token **cur_token, t_cmd **cur_cmd,
	t_minishell *minishell)
{
	t_token	*token;

	token = *cur_token;
	if (check_redir_syntax(token, minishell) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (check_ambiguous_redir(token->next, minishell) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_free(1, &(*cur_cmd)->outfile);
	(*cur_cmd)->outfile = ft_strdup(token->next->value);
	(*cur_cmd)->append = 0;
	if (!(*cur_cmd)->outfile)
		exit_minishell(EXIT_FAILURE, minishell, NULL);
	(*cur_token) = token->next->next;
	return (EXIT_SUCCESS);
}
