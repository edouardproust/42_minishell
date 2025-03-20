/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:38:25 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:38:27 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
 * Initializes the `t_expansion` struct.
 * - Allocates `cleaned` buffer with size `2 * strlen(str) + 1`.
 * - Initializes buffer size, positions and `in_quote` state.
 */
void	init_expansion(t_expansion *exp, char *str)
{
	size_t	initial_size;

	initial_size = ft_strlen(str) * 2 + 1;
	exp->cleaned = malloc(initial_size);
	exp->buf_size = initial_size;
	exp->input_pos = 0;
	exp->output_pos = 0;
	exp->in_quote = 0;
}

/*
 * Ensures the output buffer has space for `space_needed` additional bytes.
 * - Doubles buffer size repeatedly until sufficient.
 * - Uses `ft_realloc` to preserve existing content.
 */
void	ensure_buffer_space(t_expansion *exp, int space_needed)
{
	char	*new;
	int		new_size;

	if (exp->output_pos + space_needed + 1 < exp->buf_size)
		return ;
	new_size = exp->buf_size * 2;
	while (exp->output_pos + space_needed + 1 >= new_size)
		new_size = new_size * 2;
	new = ft_realloc(exp->cleaned, exp->buf_size, new_size);
	if (new)
	{
		exp->cleaned = new;
		exp->buf_size = new_size;
	}
}
