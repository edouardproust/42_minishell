/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:39:21 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:39:27 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Add a new var to the environment vars list.
 *
 * @param var Definition of the env. variable: VAR_NAME=var_value
 * @return Pointer to the created node
 * @note This function does not check the identifier validity. Use
 * utils function `is_valid_envp_var` to perform a check.
 * @note Caller must free var.
 */
t_envvar	*envvar_new(char *var)
{
	t_envvar	*node;

	if (!var)
		return (NULL);
	node = malloc(sizeof(t_envvar));
	if (!node)
		return (NULL);
	node->prev = NULL;
	node->next = NULL;
	node->name = get_envp_var_identifier(var);
	if (!node->name)
		return (free_envvar_node(&node), NULL);
	node->value = get_envp_var_value(var);
	if (!node->value)
	{
		ft_free(&node->name);
		free_envvar_node(&node);
		return (NULL);
	}
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
 * @return EXIT_SUCCESS or EXIT_FAILURE (on malloc error or
 * wrong node / value)
 */
int	envvar_updateone(t_envvar *node, char *new_value)
{
	if (!node || !new_value)
		return (EXIT_FAILURE);
	ft_free(&node->value);
	node->value = ft_strdup(new_value);
	if (!node->value)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
