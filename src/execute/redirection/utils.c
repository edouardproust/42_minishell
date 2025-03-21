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

t_outfile	*get_last_outfile(t_outfile **outfiles)
{
	t_outfile	*last;
	int			i;

	last = NULL;
	if (outfiles)
	{
		i = 0;
		while (outfiles[i])
		{
			last = outfiles[i];
			i++;
		}
	}
	return (last);
}