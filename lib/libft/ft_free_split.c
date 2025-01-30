/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:31:01 by eproust           #+#    #+#             */
/*   Updated: 2025/01/30 12:48:07 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Frees a 2D array of pointers (e.g. an array of strings char**).
 * The array must be NULL-terminated.
 */
void	ft_free_split(char ***array)
{
	char	**element;

	if (!array || !*array)
		return ;
	element =  *array;
	while (*element)
	{
		free(*element);
		*element = NULL;
		element++;
	}
	free(*array);
	*array = NULL;
}
