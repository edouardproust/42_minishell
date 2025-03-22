/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:39:21 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:39:27 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_infile	*get_last_infile(t_infile **infiles)
{
	t_infile	*last;
	int			i;

	last = NULL;
	if (infiles)
	{
		i = 0;
		while (infiles[i])
		{
			last = infiles[i];
			i++;
		}
	}
	return (last);
}

int	open_outfile(t_outfile *outfile)
{
	int	flags;
	int	fdout;

	flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (outfile->append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fdout = open(outfile->filepath, flags, 0644);
	return (fdout);
}
