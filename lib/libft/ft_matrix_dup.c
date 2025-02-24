/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 01:28:33 by eproust           #+#    #+#             */
/*   Updated: 2025/02/14 01:28:37 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_matrix_dup(char **matrix)
{
	char	**dup;
	int		count;
	int		i;

	count = ft_matrix_size(matrix);
	dup = malloc(sizeof(char *) * (count + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < count)
	{
		dup[i] = ft_strdup(matrix[i]);
		if (!dup[i])
			return (ft_free_splitn(&dup, i), NULL);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

/**
 * To compile: 
 * `cc -Werror -Wextra -Wall ft_memcpy.c ft_free_splitn.c ft_strlen.c
 * ft_strdup.c ft_free_ptrs.c ft_free_splitn.c ft_matrix_dup.c && valgrind
 * ./a.out`
 */
/*
#include <stdio.h>

int	main(void)
{
	char *matrix[5] = {
		"this is a test",
		"hello world",
		"1,2,3,4,5",
		"abcdefghijklmnopqrstuvwxyz",
		NULL
	};
	char **dup = ft_matrix_dup(matrix);
	if (!dup)
		return (EXIT_FAILURE);
	int	i = 0;
	while (dup[i])
		printf("%s\n", dup[i++]);
	ft_free_splitn(&dup, i);
	return (EXIT_SUCCESS);
}
*/
