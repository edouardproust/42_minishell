/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:07:30 by eproust           #+#    #+#             */
/*   Updated: 2025/02/16 20:07:31 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Calculate the size of a null-terminated array of strings.
 *
 * @param matrix A null-temrinated array of strings
 */
size_t	ft_matrix_size(char **matrix)
{
	size_t	count;

	if (!matrix)
		return (0);
	count = 0;
	while (matrix[count] != NULL)
		count++;
	return (count);
}

/*
#include <stdio.h>

int	main(void)
{
	char *matrix[5] = {
		"string 1",
		"string 2",
		"string 3",
		"string 4",
		NULL
	};
	printf("result: %d\n", ft_matrix_size(matrix));
}
*/