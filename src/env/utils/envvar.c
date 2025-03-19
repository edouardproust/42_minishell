/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:39:21 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:39:27 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/**
 * Count the number of nodes in a t_envvar list.
 *
 * @param head Head node of the list
 * @return Count of nodes in the list.
 */
int	envvar_lstsize(t_envvar *head)
{
	int			count;
	t_envvar	*current;

	if (!head)
		return (0);
	current = head;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/**
 * Get the value of an environment variable from its name.
 *
 * This function is searching through the member  * t_envvar_lst of
 * t_minishell.
 *
 * @param var_name Name of the searched environment variable
 * @param minishell Struct containing global Minishell data, including
 * the environment variables list (`envvar_lst`).
 * @return The value if node t_envvar node found. NULL otherwise.
 */
char	*get_env_value(char *var_name, t_minishell *minishell)
{
	t_envvar	*var;

	var = envvar_findbyname(minishell->envvar_lst, var_name);
	if (!var)
		return (NULL);
	return (var->value);
}
