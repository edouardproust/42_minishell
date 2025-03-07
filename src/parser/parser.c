#include "minishell.h"
/**
 * Cleans up token and command lists if parsing fails.
 * 
 * @param minishell Shell instance containing token/cmd lists.
 * @param status Indicates failure (EXIT_FAILURE) or success.
 * @return The input `status` unchanged.
 * @note Frees resources only on failure (EXIT_FAILURE).
 */
static int	parse_cleanup(t_minishell *minishell, int status)
{
	if (status == EXIT_FAILURE)
	{
		free_token_lst(&minishell->token_lst);
		free_cmd_lst(&minishell->cmd_lst);
	}
	return (status);
}

/* 
 * Parses a list of tokens and builds a linked list of commands.
 *
 * - Initializes the command list (`cmd_lst`).
 * - Delegates token processing to `handle_token_type`.
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

	minishell->cmd_lst = cmd_new(NULL);
	if (!minishell->cmd_lst)
		return (parse_cleanup(minishell, EXIT_FAILURE));
	cur_token = minishell->token_lst;
	cur_cmd = minishell->cmd_lst;
	while (cur_token)
	{
		prev_token = cur_token;
		if (handle_token_type(&cur_token, &cur_cmd, minishell)
			== EXIT_FAILURE)
			return (parse_cleanup(minishell, EXIT_FAILURE));
	}
	return (EXIT_SUCCESS);
}
