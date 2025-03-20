/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:39:21 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:39:27 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Frees a single t_cmd node and its associated resources.
 *
 * @param cmd Pointer to the command node to free (by reference).
 * @return Pointer to the next command node in the list.
 */
t_cmd	*free_cmd_node(t_cmd **cmd)
{
	t_cmd	*nxt_cmd;

	ft_free_split(&(*cmd)->args);
	if ((*cmd)->pipe)
		ft_free_ptr((void **)&(*cmd)->pipe);
	if ((*cmd)->infiles)
		ft_free_split(&(*cmd)->infiles);
	if ((*cmd)->outfiles)
		ft_free_split(&(*cmd)->outfiles);
	if ((*cmd)->heredoc)
	{
		if ((*cmd)->heredoc->delimiter)
			ft_free(&(*cmd)->heredoc->delimiter);
		ft_free_ptr((void **)&(*cmd)->heredoc);
	}
	nxt_cmd = (*cmd)->next;
	ft_free_ptr((void **)cmd);
	return (nxt_cmd);
}

/**
 * Free all the node in the list of t_cmd (starting by the 'cmd_lst' node).
 *
 * @param cmd_lst Pointer to the head of the list (by reference)
 * @return void
 */
void	free_cmd_lst(t_cmd **cmd_lst)
{
	if (!cmd_lst || !*cmd_lst)
		return ;
	while (*cmd_lst)
		*cmd_lst = free_cmd_node(cmd_lst);
	*cmd_lst = NULL;
}
