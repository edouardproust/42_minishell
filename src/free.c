#include "minishell.h"

/*
 * Frees one command (t_cmd).
 * Return: pointer to the next cmd in the list
 */
t_cmd	*free_cmd(t_cmd **cmd)
{
	t_cmd	*cur_cmd;
	t_cmd	*nxt_cmd;

	cur_cmd = *cmd;
	ft_free_split(&cur_cmd->args);
	ft_free_ptrs(3, &cur_cmd->infile, &cur_cmd->outfile,
		&cur_cmd->pipe);
	nxt_cmd = cur_cmd->next;
	ft_free_ptrs(1, &cur_cmd);
	return (nxt_cmd);
}

/*
 * Frees all the commands in the list (starting by 'cmd_list' node).
 */
void	free_cmd_lst(t_cmd **cmd_lst)
{
	t_cmd	*cur_cmd;
	t_cmd	*nxt_cmd;

	cur_cmd = *cmd_lst;
	while (cur_cmd)
	{
		nxt_cmd = free_cmd(&cur_cmd);
		cur_cmd = nxt_cmd;
	}
}
