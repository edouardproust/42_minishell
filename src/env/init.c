/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:39:21 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:39:27 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Initialize environment variables list from envp.
 * 
 * @param envp Array of environment variable strings.
 * @return Pointer to the head of the initialized list.
 * 
 * @note Exit program on memory allocation failure.
 */
t_envvar	*init_envvars(t_minishell *minishell)
{
	char		**envp;
	t_envvar	*lst;
	t_envvar	*node;

	envp = minishell->envp;
	lst = NULL;
	node = NULL;
	while (*envp)
	{
		node = envvar_new(*envp++);
		if (!node)
			return (free_envvar_lst(&lst), NULL);
		envvar_addoneback(&lst, node);
	}
	return (lst);
}
