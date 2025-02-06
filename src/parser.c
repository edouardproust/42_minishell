#include "minishell.h"

t_cmd	*cmd_new()
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->next = NULL;
	return (cmd);
}
//adds an argument to the args list
void	add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	int	i;
	int	count;
	char	**new_args;
	
	count = 0;
	while (cmd->args && cmd->args[count]) //we count existing args
		count++;
	new_args = malloc(sizeof(char *) * (count + 2)); // 1 for existing args, 1 for NULL
	if (!new_args)
		return ;
	i = 0;
	while (i < count) //copy the old arguments
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = arg; // add new arg
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}
//Parse tokens into commands
t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;

	cmd_list = cmd_new();
	current_cmd = cmd_list;
	while (tokens)
	{
		if (tokens->type == TOKEN_REDIR_IN)
			handle_input_redirection(current_cmd, &tokens);
		else if (tokens->type == TOKEN_REDIR_OUT)
			handle_output_redirection(current_cmd, &tokens);
		else if (tokens->type == TOKEN_WORD)
			handle_word(current_cmd, tokens);
		else if (tokens->type == TOKEN_PIPE)
			handle_pipe(&current_cmd);
		tokens = tokens->next;
	}
	return (cmd_list);
}
