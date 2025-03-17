/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_splitn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:41:25 by eproust           #+#    #+#             */
/*   Updated: 2025/02/14 12:41:26 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Frees a matrix (array of strings) up to n strings.
 *
 * This function is often used to free partially alocated matrix, like after
 * the allocation of a string failed while setting up the matrix.
 *
 * @param array	Dynamic allocated array of strings. It does not have to be
 * 				NULL-terminated if n < number of strings in the array
 * @param n		Number of strings to free inside the array
 */
void	ft_free_splitn(char ***matrix, int n)
{
	char	**str_ptr;
	int		i;

	if (!matrix || !*matrix)
		return ;
	str_ptr = *matrix;
	i = 0;
	while (str_ptr[i] && i < n)
		free(str_ptr[i++]);
	free(*matrix);
	*matrix = NULL;
}

/**
 * To compile: Test this function via ft_matrix_dup.c
 */
