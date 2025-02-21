#include "minishell.h"

/**
 * Free one t_envvar node
 * 
 * @param var Pointer to the node to delete (by reference)
 * @return Pointer to the next node in the list
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

/**
 * Free all the nodes in the list of t_envvar (starting by the 
 * 'envvar_list' node).
 * 
 * @param var_lst Pointer to the head of the list (by reference)
 * @return void
 */
void	free_envvar_lst(t_envvar **var_lst)
{
	if (!var_lst || !*var_lst)
		return ;
	while (*var_lst)
		*var_lst = free_envvar_node(var_lst);
	*var_lst = NULL;
}

/**
 * Free all the node in the list of t_cmd (starting by the 'cmd_lst' node).
 * 
 * @param cmd_lst Pointer to the head of the list (by reference)
 * @return void
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

/**
 * Free minishell at any point during the program execution.
 * 
 * @param minishell Struct containing global data on the program,
 * 	including lists of t_cmd, t_envvar, etc.
 * @return void
 */
void	free_minishell(t_minishell *minishell)
{
	if (!minishell)
		return ;
	if (minishell->envvar_lst)
		free_envvar_lst(&minishell->envvar_lst);
	if (minishell->cmd_lst)
		free_cmd_lst(&minishell->cmd_lst);
	ft_free_split(&minishell->envp);
	ft_free_ptrs(1, &minishell);
}