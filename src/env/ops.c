#include "minishell.h"

/**
 * Add a new var to the environment vars list.
 *
 * @param var Definition of the env. variable: VAR_NAME=var_value
 * @return Pointer to the created node 
 */
t_envvar	*envvar_new(char *var)
{
	t_envvar	*node;
    int			equal_sign_index;

	node = malloc(sizeof(t_envvar));
    if (!node)
		return (NULL);
	equal_sign_index = ft_strchri(var, '=');
	if (equal_sign_index < 0)
	{
		set_errno(EINVAL);
		return (ft_free_ptrs(1, &node), NULL);
	}
	node->name = ft_substr(var, 0, equal_sign_index);
	if (!node->name)
		return (ft_free_ptrs(1, &node), NULL);
	node->value = ft_substr(var, equal_sign_index + 1, ft_strlen(var));
	if (!node->value)
		return (ft_free_ptrs(2, &node->name, &node), NULL);
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

int	envvar_addoneback(t_envvar **lst, t_envvar *new)
{
	t_envvar	*tail;

	if (!lst || !new)
		return (EXIT_FAILURE);
	if (!*lst)
	{
		*lst = new;
		return (EXIT_SUCCESS);
	}
	tail = *lst;
	while (tail->next)
		tail = tail->next;
	tail->next = new;
	new->prev = tail;
	return (EXIT_SUCCESS);
}

int	envvar_deleteone(t_envvar **lst, t_envvar *to_remove)
{
	t_envvar	*cur_var;
	
	if (!lst || !*lst || !to_remove)
        return (EXIT_FAILURE);
	cur_var = *lst;
	while (cur_var)
	{
		if (cur_var == to_remove)
		{
			if (to_remove->prev)
				to_remove->prev->next = to_remove->next;
			else
				*lst = to_remove->next;
			if (to_remove->next)
				to_remove->next->prev = to_remove->prev;
			free_envvar_node(&to_remove);
			return (EXIT_SUCCESS);
		}
		cur_var = cur_var->next;
	}
	return (EXIT_FAILURE);
}

int	envvar_updateone(t_envvar *node, char *new_value)
{
	if (!node || !new_value)
		return (EXIT_FAILURE);
	ft_free_ptrs(1, &node->value);
	node->value = ft_strdup(new_value);
	if (!node->value)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_envvar	*envvar_findbyname(t_envvar *lst, char *name)
{
	size_t	name_len;

	if (!lst || !name)
		return (NULL);
	name_len = ft_strlen(name);
	while (lst)
	{
		if (strncmp(lst->name, name, name_len + 1) == 0)
			return (lst);
		lst = lst->next;	
	}
	return (NULL);
}
