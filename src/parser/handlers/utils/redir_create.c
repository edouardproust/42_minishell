/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:41:32 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:43:14 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Allocate a new infile, based on a heredoc entry.
 * This is just an initialization. The heredoc fd is created later in the
 * code.
 *
 * @param delimiter The string of the heredoc delimiter
 * @param start The number of the currently parsed input in the minishell
 * readline history
 * @return The infile struct created or NULL in case of malloc failure.
 */
t_infile	*create_infile_from_heredoc(char *delimiter, int start)
{
    t_infile	*new_infile;

	if (!delimiter)
		return (NULL);
	new_infile = malloc(sizeof(t_infile));
	if (!new_infile)
		return (NULL);
	new_infile->filepath = NULL;
	new_infile->is_heredoc = TRUE;
	new_infile->hdoc_delimiter = ft_strdup(delimiter);
	if (!new_infile->hdoc_delimiter)
		return (free(new_infile), NULL);
	new_infile->hdoc_fd = -1;
	new_infile->hdoc_start = start;
	return (new_infile);
}

/**
 * Allocate a new infile based on a file path.
 *
 * @param path The path of the infile
 * @return The infile struct created or NULL in case of malloc failure.
 */
t_infile	*create_infile_from_path(char *path)
{
    t_infile	*new_infile;

	if (!path)
		return (NULL);
	new_infile = malloc(sizeof(t_infile));
	if (!new_infile)
		return (NULL);
	new_infile->filepath = ft_strdup(path);
	if (!new_infile->filepath)
		return (free(new_infile), NULL);
	new_infile->is_heredoc = FALSE;
	new_infile->hdoc_delimiter = NULL;
	new_infile->hdoc_fd = -1;
	new_infile->hdoc_start = -1;
	return (new_infile);
}

/**
 * Allocate a new outfile.
 *
 * @return The infile struct created or NULL in case of malloc failure.
 */
t_outfile	*create_outfile(char *path, t_bool append)
{
    t_outfile	*new_outfile;

	new_outfile = malloc(sizeof(t_outfile));
    if (!new_outfile)
        return (NULL);
    new_outfile->filepath = ft_strdup(path);
	if (!new_outfile->filepath)
		return (free(new_outfile), NULL);
    new_outfile->append = append;
    return (new_outfile);
}
