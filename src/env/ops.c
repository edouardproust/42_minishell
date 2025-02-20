#include "minishell.h"

/**
 * Add a new var to the environment vars list.
 *
 * @param var Definition of the env. variable: VAR_NAME=var_value
 * @return Pointer to the created node
 * 
 * @todo: check input invalid syntaxes during tokenization phase:
 * - `export NAME = value` and `export =value` are incorrect
 * - `export NAME` and `export NAME=` are correct
 */
t_envvar	*envvar_new(char *var)
{
	t_envvar	*node;
	int			equal_sign_index;

	if (!var)
		return (NULL);
	node = malloc(sizeof(t_envvar));
	if (!node)
		return (NULL);
	node->prev = NULL;
	node->next = NULL;
	equal_sign_index = ft_strchri(var, '=');
	if (equal_sign_index < 0)
		node->name = ft_strdup(var);
	else
		node->name = ft_substr(var, 0, equal_sign_index);
	if (!node->name)
		return (ft_free_ptrs(1, &node), NULL);
	if (equal_sign_index < 0)
		node->value = ft_strdup("");
	else
		node->value = ft_substr(var, equal_sign_index + 1, ft_strlen(var));
	if (!node->value)
		return (ft_free_ptrs(2, &node->name, &node), NULL);
	return (node);
}

/**
 * Add a node at the end of the list.
 * 
 * @param lst Pointer to the list's head node
 * @param new New node to add
 * @return EXIT_SUCCESS if node added successfully, 
 * EXIT_FAILURE otherwise
 */
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

/**
 * Delete a t_envvar node if it exists.
 * 
 * @param lst Pointer to the head of the list of t_envvar nodes
 * @param to_remove Pointer to the t_envvar node to remove
 * @return EXIT_FAILURE if incorrect params, EXIT_SUCCESS otherwise
 * (even if node does not exist in the list)
 */
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

/**
 * Update the 'value' member of the given t_envvar node.
 * 
 * This function does not check if the node exists in the list. 
 * You may want to use envvar_findbyname() before this function to 
 * prevent to make sure it exists and prevent any undefined behaviour.
 * 
 * @param lst Pointer to the head of the list of t_envvar nodes
 * @param name Name of the var to be found
 * @return The found node. NULL if not found
 */
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

/**
 * Find the t_envvar based on the var name.
 * 
 * @param lst Head of the list of t_envvar nodes
 * @param name Name of the var to be found
 * @return The found t_envvar or NULL if not found
 */
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
