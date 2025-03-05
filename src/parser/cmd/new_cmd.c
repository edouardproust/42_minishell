#include "minishell.h"

static int	init_cmd_process(t_cmd *cmd)
{
	cmd->pid = -1;
	cmd->pipe = malloc(sizeof(int) *2);
	if (!cmd->pipe)
		return (EXIT_FAILURE);
	cmd->pipe[0] = -1;
	cmd->pipe[1] = -1;
	cmd->saved_stdin = -1;
	cmd->saved_stdout = -1;
	return (EXIT_SUCCESS);
}

static int	init_cmd_heredoc(t_cmd *cmd)
{
	cmd->heredoc = malloc(sizeof(t_heredoc));
	if (!cmd->heredoc)
		return (EXIT_FAILURE);
	cmd->heredoc->delimiter = NULL;
	cmd->heredoc->fd = -1;
	return (EXIT_SUCCESS);
}

/*
* Initializes redirection-related fields in the t_cmd structure.
*/
static int	init_cmd_redirections(t_cmd *cmd)
{
	cmd->fdin = STDIN_FILENO;
	cmd->fdout = STDOUT_FILENO;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = FALSE;
	if (init_cmd_heredoc(cmd) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
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
	if (init_cmd_process(cmd) != EXIT_SUCCESS)
		return (free_cmd_node(&cmd), NULL);
	if (init_cmd_redirections(cmd) != EXIT_SUCCESS)
		return (free_cmd_node(&cmd), NULL);
	cmd->prev = prev_cmd;
	if (cmd->prev)
		cmd->prev->next = cmd;
	cmd->next = NULL;
	return (cmd);
}