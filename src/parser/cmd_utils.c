#include "minishell.h"


static int	init_cmd_pipe(t_cmd *cmd)
{
	cmd->pipe = malloc(sizeof(int) * 2);
	if (!cmd->pipe)
		return (ft_free(1, &cmd), EXIT_FAILURE);
	cmd->pipe[0] = -1;
	cmd->pipe[1] = -1;
	return (EXIT_SUCCESS);
}

/*
* Initializes redirection-related fields in the t_cmd structure.
*/
static void	init_cmd_redir(t_cmd *cmd)
{
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->heredoc_del = NULL;
	cmd->heredoc_fd = -1;
	cmd->append = 0;
	cmd->saved_stdin = -1;
	cmd->fdin = STDIN_FILENO;
	cmd->saved_stdout = -1;
	cmd->fdout = STDOUT_FILENO;
}

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
	cmd->pid = -1;
	cmd->prev = prev_cmd;
	cmd->next = NULL;
	if (cmd->prev)
		cmd->prev->next = cmd;
	init_cmd_redir(cmd);
	if (init_cmd_pipe(cmd) != EXIT_SUCCESS)
		return (NULL);
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
	ft_free(1, &cmd->args);
	cmd->args = new_args;
}
