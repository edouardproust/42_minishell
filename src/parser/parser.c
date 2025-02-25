#include "minishell.h"
/* 
 * Parses a list of tokens and builds a linked list of commands.
 *
 * - Initializes the command list (`cmd_lst`).
 * - Iterates through tokens, processing each one using `handle_token_type()`.
 * - Exits if an error occurs.
 * 
 * Returns: EXIT_SUCCESS on success, or EXIT_FAILURE on failure.
 */
//TODO (A) Implement append and heredoc logic types.
int	parse_tokens(t_minishell *minishell)
{
	t_token	*cur_token;
	t_cmd	*cur_cmd;
	t_token	*prev_token;

	if (!minishell->token_lst)
		return (EXIT_FAILURE);
	minishell->cmd_lst = cmd_new(NULL);
	if (!minishell->cmd_lst)
		exit_minishell(EXIT_FAILURE, minishell, NULL);
	cur_token = minishell->token_lst;
	cur_cmd = minishell->cmd_lst;
	while (cur_token)
	{
		prev_token = cur_token;
		handle_token_type(&cur_token, &cur_cmd, minishell);
		if (cur_token == prev_token)
		{
			exit_minishell(EXIT_FAILURE, minishell, NULL);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
