#include "minishell.h"

t_cmd	*cmd_new(t_cmd *prev_cmd)
{
	t_cmd *cmd;

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
	cmd->prev = prev_cmd;
	cmd->next = NULL;
	if (cmd->prev)
		cmd->prev->next = cmd;
	return (cmd);
}
//adds an argument to the args list
void	add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	int	i;
	int	count;
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
//Parse tokens into commands. TODO (A) Implement append and heredoc logic
t_cmd	*parse_tokens(t_token *tokens_head)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;
	t_token	*current_token;

	cmd_list = NULL;
	current_token = tokens_head;
	if (!current_token)
		exit_parsing(&cmd_list, &tokens_head, "syntax error: empty command");
	cmd_list = cmd_new(NULL);
	if (!cmd_list)
		exit_parsing(&cmd_list, &tokens_head, "malloc error");
	current_cmd = cmd_list;
	handle_token_type(&cmd_list, &current_cmd, &tokens_head, &current_token);
	return (cmd_list);
}
