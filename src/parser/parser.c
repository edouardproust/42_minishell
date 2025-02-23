#include "minishell.h"
/* 
 * Parses a list of tokens and converts them into a linked list of commands.
 *
 * - Initializes the parsing process by setting up the necessary variables.
 * - Creates a new command structure to hold the parsed tokens.
 * - Iterates over the tokens, processing them according to their type.
 * - Links the new commands to the command list.
 * 
 * Returns: A linked list of parsed t_cmd structures, or NULL if parsing fails.
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
