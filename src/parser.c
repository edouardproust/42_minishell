#include "minishell.h"

/** 
 * Creates a new command structure with default values.
 * Returns: A new t_cmd structure or NULL if malloc fails.
 */
t_cmd	*cmd_new(t_cmd *prev_cmd)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->pipe = malloc(sizeof(int) * 2);
	if (!cmd->pipe)
		return (free(cmd), NULL);
	cmd->pipe[0] = -1;
	cmd->pipe[1] = -1;
	cmd->fdin = STDIN_FILENO;
	cmd->fdout = STDOUT_FILENO;
	cmd->pid = -1;
	cmd->prev = prev_cmd;
	cmd->next = NULL;
	if (cmd->prev)
		cmd->prev->next = cmd;
	return (cmd);
}

/** 
 * Adds an argument to the command's arguments list.
 */
void	add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	int		i;
	int		count;
	char	**new_args;

	count = 0;
	while (cmd->args && cmd->args[count])
		count++;
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return ;
	i = -1;
	while (++i < count)
		new_args[i] = cmd->args[i];
	new_args[count] = arg;
	new_args[count + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}

/**
 * Parses a list of tokens and converts them into a linked list of commands.
 *
 * - Initializes the parsing process by setting up the necessary variables.
 * - Creates a new command structure to hold the parsed tokens.
 * - Iterates over the tokens, processing them according to their type.
 * - Links the new commands to the command list.
 * 
 * @return A linked list of parsed t_cmd structures, or NULL if parsing fails.
 */
//TODO (A) Implement append and heredoc logic types.
//TODO Check error message for malloc exit
int	parse_tokens(t_minishell *minishell)
{
	t_token	*cur_token;
	t_cmd	*cur_cmd;

	if (!minishell->token_lst)
		return (EXIT_FAILURE);
	minishell->cmd_lst = cmd_new(NULL);
	if (!minishell->cmd_lst)
		exit_minishell(EXIT_FAILURE, minishell, NULL);
	cur_token = minishell->token_lst;
	cur_cmd = minishell->cmd_lst;
	while (cur_token)
	{
		handle_token_type(&cur_token, &cur_cmd, minishell);
		cur_token = cur_token->next;
	}
	return (EXIT_SUCCESS);
}