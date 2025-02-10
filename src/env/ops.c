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

/*
void	envvar_removeone(t_envvar **lst, t_envvar *node)
{

}

void	envvar_updateone(t_envvar **lst, t_envvar *node)
{

}
*/