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
 * Free the t_cmd infiles array.
 *
 * @param cmd The command struct holding the infiles array.
 * @return void
 */
static void	free_infiles(t_cmd *cmd)
{
	int	i;

	if (!cmd->infiles)
		return ;
	i = 0;
	while (cmd->infiles[i])
	{
		ft_free(&cmd->infiles[i]->filepath);
		ft_free(&cmd->infiles[i]->hdoc_delimiter);
		free(cmd->infiles[i]);
		i++;
	}
	free(cmd->infiles);
	cmd->infiles = NULL;
}

/**
 * Free the t_cmd outfiles array.
 *
 * @param cmd The command struct holding the outfiles array.
 * @return void
 */
static void	free_outfiles(t_cmd *cmd)
{
	int	i;

	if (!cmd->outfiles)
		return ;
	i = 0;
	while (cmd->outfiles[i])
	{
		ft_free(&cmd->outfiles[i]->filepath);
		free(cmd->outfiles[i]);
		i++;
	}
	free(cmd->outfiles);
	cmd->outfiles = NULL;
}

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
	ft_free_ptr((void **)&(*cmd)->pipe);
	if ((*cmd)->infiles)
		free_infiles(*cmd);
	if ((*cmd)->outfiles)
		free_outfiles(*cmd);
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
