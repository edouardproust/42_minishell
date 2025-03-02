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
 * Frees all the tokens' value and structure in the token list.
 * 
 * @param token_lst Pointer to the head of the list (by reference)
 * @return void
 */
void	free_token_lst(t_token **token_lst)
{
	t_token	*cur_token;
	t_token	*nxt_token;

	if (!token_lst || !*token_lst)
		return ;
	cur_token = *token_lst;
	while (cur_token)
	{
		nxt_token = cur_token->next;
		ft_free_ptrs(2, &cur_token->value, &cur_token);
		cur_token = nxt_token;
	}
	*token_lst = NULL;
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
void	free_minishell(t_minishell **ms)
{
	flush_fds();
	if (!ms || !*ms)
		return ;
	if ((*ms)->envvar_lst)
		free_envvar_lst(&(*ms)->envvar_lst);
	if ((*ms)->input)
		ft_free_ptrs(1, &(*ms)->input);
	if ((*ms)->token_lst)
		free_token_lst(&(*ms)->token_lst);
	if ((*ms)->cmd_lst)
		free_cmd_lst(&(*ms)->cmd_lst);
	ft_free_split(&(*ms)->envp);
	ft_free_ptrs(1, ms);
}
