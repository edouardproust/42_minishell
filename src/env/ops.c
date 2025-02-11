#include "minishell.h"

void	envvar_addone(t_envvar **lst, t_envvar *new)
{
	t_envvar	*tail;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tail = *lst;
	while (tail->next)
		tail = tail->next;
	tail->next = new;
	new->prev = tail;
}

void	envvar_removeone(t_envvar **lst, t_envvar *node)
{
	size_t	len = ft_strlen(node->name) + 1;
	while (*lst)
	{
		if (ft_strncmp((*lst)->name, node->name, len) == 0)
		{
			// remove logic here
		}
		lst = lst->next;
	}
}

/*
void	envvar_updateone(t_envvar **lst, t_envvar *node)
{

}
*/
