#include "minishell.h"

/**
 * Frees a single t_cmd node and its associated resources.
 * 
 * @param cmd Pointer to the command node to free (by reference).
 * @return Pointer to the next command node in the list.
 */
t_cmd	*free_cmd_node(t_cmd **cmd)
{
	t_cmd	*nxt_cmd;

	ft_free_split(&(*cmd)->args);
	if ((*cmd)->pipe)
		ft_free(1, &(*cmd)->pipe);
	if ((*cmd)->infile)
		ft_free(1, &(*cmd)->infile);
	if ((*cmd)->outfile)
		ft_free(1, &(*cmd)->outfile);
	if ((*cmd)->heredoc)
	{
		if ((*cmd)->heredoc->delimiter)
			ft_free(1, &(*cmd)->heredoc->delimiter);
		ft_free(1, &(*cmd)->heredoc);
	}
	nxt_cmd = (*cmd)->next;
	ft_free(1, cmd);
	return (nxt_cmd);
}

/**
 * Free all the node in the list of t_cmd (starting by the 'cmd_lst' node).
 * 
 * @param cmd_lst Pointer to the head of the list (by reference)
 * @return void
 */
void	free_cmd_lst(t_cmd **cmd_lst)
{
	if (!cmd_lst || !*cmd_lst)
		return ;
	while (*cmd_lst)
		*cmd_lst = free_cmd_node(cmd_lst);
	*cmd_lst = NULL;
}
