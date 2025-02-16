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
	t_parse	parse;
	t_cmd	*cmd_list;

	cmd_list = NULL;
	parse = (t_parse){&cmd_list, NULL, tokens_head, tokens_head};
	if (!parse.current_token)
		exit_parsing(&parse, "syntax error: empty command");
	*parse.cmd_list_head = cmd_new(NULL);
	parse.current_cmd = *parse.cmd_list_head;
	if (!parse.current_cmd)
		exit_parsing(&parse, "malloc error");
	 handle_token_type(&parse);
	 return (cmd_list);
}
