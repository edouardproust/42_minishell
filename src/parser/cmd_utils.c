#include "minishell.h"
/*
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
	cmd->heredoc_del = NULL;
	cmd->append = 0;
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

/*
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
