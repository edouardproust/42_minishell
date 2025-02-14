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
		return(free(cmd), NULL);
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
	i = 0;
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = ft_strdup(arg);
	if (!new_args[i])
	{
		free(cmd->args); 
		free(new_args);
		return ;
	}
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}
//Parse tokens into commands. TODO (A) Implement append and heredoc logic
t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;

	if (!tokens)
		exit_parsing(NULL, &tokens,"syntax error: empty command");
	cmd_list = cmd_new(NULL);
	if (!cmd_list)
		return(free_token_lst(&tokens), NULL);
	current_cmd = cmd_list;
	handle_token_type(current_cmd, &tokens);
	return (cmd_list);
}
