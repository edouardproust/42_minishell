#include "minishell.h"
/**
 * Handles a word token by copying its value and adding it to the current
 * command's arguments.
 * - Duplicates the word and adds it to the args list of the current command.
 * @TODO Check malloc error message (for now on NULL)
 */
int	handle_word(t_token **cur_token, t_cmd **cur_cmd,
	t_minishell *minishell)
{
	t_token	*token;
	char	*arg_copy;

	token = *cur_token;
	arg_copy = ft_strdup(token->value);
	if (!arg_copy)
		exit_minishell(EXIT_FAILURE, minishell, "parse word: strdup");
	add_arg_to_cmd(*cur_cmd, arg_copy);
	*cur_token = token->next;
	return (EXIT_SUCCESS);
}
