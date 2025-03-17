#include "minishell.h"

/**
 * Free one t_envvar node.
 *
 * @param var Pointer to the node to delete (by reference)
 * @return Pointer to the next node in the list
 */
t_envvar	*free_envvar_node(t_envvar **var)
{
	t_envvar	*nxt_var;

	if (!var || !*var)
		return (NULL);
	ft_free(&(*var)->name);
	ft_free(&(*var)->value);
	nxt_var = (*var)->next;
	ft_free_ptr((void **)var);
	*var = NULL;
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
