#include "minishell.h"

/*
 * Free one t_envvar node
 */
t_envvar	*free_envvar_node(t_envvar **var)
{
	t_envvar	*nxt_var;

	if (!var || !*var)
		return (NULL);
	nxt_var = (*var)->next;
	ft_free_ptrs(3,
		&(*var)->name,
		&(*var)->value,
		var);
	return (nxt_var);
}

/*
 * Free all the nodes in the list of t_envvar (starting by the 'envvar_list' node).
 */
void	free_envvar_lst(t_envvar **var_lst)
{
	if (!var_lst || !*var_lst)
		return ;
	while (*var_lst)
		*var_lst = free_envvar_node(var_lst);
	*var_lst = NULL;
}

/*
 * Free all the node in the list of t_cmd (starting by the 'cmd_lst' node).
 */
void	free_cmd_lst(t_cmd **cmd_lst)
{
	t_cmd	*cur_cmd;
	t_cmd	*nxt_cmd;

	if (!cmd_lst || !*cmd_lst)
		return ;
	cur_cmd = *cmd_lst;
	while (cur_cmd)
	{
		ft_free_split(&cur_cmd->args);
		nxt_cmd = cur_cmd->next;
		ft_free_ptrs(4, 
			&cur_cmd->infile,
			&cur_cmd->outfile,
			&cur_cmd->pipe,
			&cur_cmd);
		cur_cmd = nxt_cmd;
	}
	*cmd_lst = NULL;
}

/*
 * Close any fd up to FD_LIMIT, except standard ones.
 */
void	flush_fds(void)
{
	int	fd;

	fd = STDERR_FILENO + 1;
	while (fd < FD_LIMIT)
		close(fd++);
}
